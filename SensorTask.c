#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/knl/Clock.h>

/* TI-RTOS Header files */
#include <ti/drivers/I2C.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/UART2.h>
#include <ti/drivers/NVS.h>
#include <ti/drivers/ADC.h>
#include <ti/drivers/Watchdog.h>

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/cpu.h)
#include DeviceFamily_constructPath(driverlib/sys_ctrl.h)
#include DeviceFamily_constructPath(driverlib/aon_batmon.h)

#include <ti/devices/cc13x2_cc26x2/driverlib/aux_adc.h>

/* Board Header files */
#include "ti_drivers_config.h"

/* Application Header files */
#include "SensorTask.h"
#include "Protocol.h"

#include "board_define.h"

#include "uart_usb_in_out.h"
#include "hdc1080.h"
#include "bme280.h"
#include "vcnl4040.h"

#define SENSOR_TASK_STACK_SIZE 1024
#define SENSOR_TASK_TASK_PRIORITY   3

#define SENSOR_TASK_EVENT_ALL                         0xFFFFFFFF
#define SENSOR_TASK_SENSOR_UPDATE    (uint32_t)(1 << 0)

#define TIMER_TIMEOUT 1000
#define WATCHDOG_TIMEOUT_MS 3000

#define BUTTON_PRESS_TIMER_COUNT 5
#define BUTTON_RPESS_COUNT 3

PIN_Config pinTable[] = {

GPIO_LED_0 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,

GPIO_LED_1 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL
| PIN_DRVSTR_MAX,

GPIO_BAT_EN | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL
| PIN_DRVSTR_MAX,

GPIO_SENSOR_POWER_EN | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL
| PIN_DRVSTR_MAX,

PIN_TERMINATE

};

PIN_Config buttonTable[] = {

GPIO_BTN | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_NEGEDGE,

                             PIN_TERMINATE

};

static Task_Params sensorTaskParams;
Task_Struct sensorTask; /* not static so you can see in ROV */
static uint8_t sensorTaskStack[SENSOR_TASK_STACK_SIZE];

Event_Struct sensorEvent; /* not static so you can see in ROV */
static Event_Handle sensorEventHandle;

Clock_Struct sensorTimerClock;
Watchdog_Handle watchdogHandle;

static PacketSendRequestCallback packetSendRequestCallback;

static PIN_State pinState;
static PIN_Handle pinHandle;

static PIN_State buttonState;
static PIN_Handle buttonHandle;

static I2C_Handle i2c;
static I2C_Params i2cParams;

static char uart2_read_buf = 0x00;
static UART2_Handle uart2;

static uint8_t on_off_mode = 0x01;

static uint8_t button_press_state = 0x00;
static uint8_t button_press_count = 0;
static int8_t button_press_timer_count = 0;

static uint8_t init_state = 0x00;

static int16_t temperature = 0;
static uint8_t humidity = 0;
static uint32_t pressure = 0;
static uint16_t ambient_light = 0;
static uint8_t battery_voltage = 0;

static uint8_t payload_size = 0;
static uint8_t payload[115];

static uint8_t sensor_task_release_state = 0x00;

extern uint8_t radio_init;
extern uint8_t mac_address[8];
extern uint32_t collection_cycle_timeout_count;
extern uint32_t collection_cycle_timer_count;

void uart2ReadCallback(UART2_Handle handle, void *rxBuf, size_t size,
                       void *userArg, int_fast16_t status);

void scCtrlReadyCallback(void)
{

}

void scTaskAlertCallback(void)
{

}

void watchdogCallback(uintptr_t watchdogHandle)
{

    while (1)
    {

    }

}

static void buttonCallback(PIN_Handle handle, PIN_Id pinId)
{

    if (init_state)
    {

        button_press_timer_count = BUTTON_PRESS_TIMER_COUNT;

        PIN_setOutputValue(pinHandle, GPIO_LED_1, 1);
        button_press_state = 0x01;

    }

}

static void sensorTimerClockCallBack(UArg arg0)
{

    if (init_state)
    {

        collection_cycle_timeout_count++;

        if (on_off_mode == 0x01)
        {

            if (collection_cycle_timeout_count >= collection_cycle_timer_count)
            {

                if (sensor_task_release_state == 0x00)
                {

                    sensor_task_release_state = 0x01;
                    Event_post(sensorEventHandle, SENSOR_TASK_SENSOR_UPDATE);

                }

                collection_cycle_timeout_count = 0;

            }

        }
        else
        {

            collection_cycle_timeout_count = 0;

        }

        if (button_press_state)
        {

            PIN_setOutputValue(pinHandle, GPIO_LED_1, 0);
            button_press_state = 0x00;

            button_press_count++;

        }

        button_press_timer_count -= 1;

        if (button_press_timer_count > 0)
        {

            if (button_press_count >= BUTTON_RPESS_COUNT)
            {

                if (on_off_mode == 0x01)
                {

                    on_off_mode = 0x00;

                }
                else
                {

                    on_off_mode = 0x01;

                }

                collection_cycle_timer_count = 0;

                PIN_setOutputValue(pinHandle, GPIO_LED_0, 1);

                button_press_timer_count = 0;
                button_press_count = 0;

            }

        }
        else
        {

            PIN_setOutputValue(pinHandle, GPIO_LED_0, 0);

            button_press_count = 0;

        }

    }

    Watchdog_clear(watchdogHandle);

}

static void wait_ms(uint32_t wait)
{

    Task_sleep(wait * 1000 / Clock_tickPeriod);

}

static void initErrorUpdate(void)
{

    for (uint8_t i = 0; i < 4; i++)
    {

        PIN_setOutputValue(pinHandle, GPIO_LED_0,
                           !PIN_getOutputValue(GPIO_LED_0));
        PIN_setOutputValue(pinHandle, GPIO_LED_1,
                           !PIN_getOutputValue(GPIO_LED_1));

        wait_ms(500);

    }

    PIN_setOutputValue(pinHandle, GPIO_LED_0, 1);
    PIN_setOutputValue(pinHandle, GPIO_LED_1, 1);

}

static uint8_t battery_value_read()
{

    ADC_Handle adc;
    ADC_Params ADCParams;
    ADC_Params_init(&ADCParams);

    adc = ADC_open(CONFIG_I2C_0, &ADCParams);

    if (adc != NULL)
    {

        uint16_t adc_value;

        PIN_setOutputValue(pinHandle, GPIO_BAT_EN, 1);

        wait_ms(20);

        int_fast16_t result = ADC_convert(adc, &adc_value);

        ADC_close(adc);

        PIN_setOutputValue(pinHandle, GPIO_BAT_EN, 0);

        if (result == ADC_STATUS_SUCCESS)
        {

            uint32_t microVolt = ADC_convertRawToMicroVolts(adc, adc_value);
            microVolt *= 3;
            microVolt /= 100000;

            return microVolt;

        }

    }

    return 0;

}

static uint8_t i2cScan()
{

    uint8_t scan_count = 0;
    uint8_t txBuffer[2] = { 0x00 };
    uint8_t rxBuffer[2] = { 0x00 };

    I2C_Transaction i2cTransaction;

    i2cTransaction.writeBuf = txBuffer;
    i2cTransaction.readBuf = rxBuffer;
    i2cTransaction.writeCount = 1;
    i2cTransaction.readCount = 0;

    set_uart_usb_in_out_write_string("Start I2C Scan");

    for (uint16_t i = 0; i < 128; i++)
    {

        i2cTransaction.slaveAddress = i;

        if (I2C_transfer(i2c, &i2cTransaction))
        {

            set_uart_usb_in_out_find_i2c_address(i);

            scan_count++;

            wait_ms(10);

        }

    }

    return scan_count;

}

static void initSensor(void)
{

    uint8_t i2c_state = 0x01;

    PIN_setOutputValue(pinHandle, GPIO_SENSOR_POWER_EN, 1);

    wait_ms(1000);

    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400kHz;
    i2c = I2C_open(CONFIG_I2C_0, &i2cParams);

    if (i2c == NULL)
    {

        initErrorUpdate();

        SysCtrlSystemReset();

    }

    i2cScan();

    wait_ms(100);

    set_hdc1080_i2c_instance(i2c);

    i2c_state = i2c_state & init_hdc1080();

    wait_ms(100);

    i2c_state = i2c_state
            & get_hdc1080_temperature_humidity(&temperature, &humidity);

    wait_ms(100);

    set_bme280_i2c_instance(i2c);

    i2c_state = i2c_state & init_bme280();

    wait_ms(100);

    i2c_state = i2c_state & get_bme280_temperature(&temperature);

    i2c_state = i2c_state & get_bme280_pressure(&pressure);

    if (!i2c_state)
    {

        initErrorUpdate();

    }

    set_vcnl4040_i2c_instance(i2c);

    i2c_state = i2c_state & init_vcnl4040();

    wait_ms(100);

    i2c_state = i2c_state & get_vcnl4040_ambient_light(&ambient_light);

    set_uart_usb_in_out_temperature(temperature);

    set_uart_usb_in_out_pressure(pressure);

    set_uart_usb_in_out_humidity(humidity);

    set_uart_usb_in_out_lux(ambient_light);

}

static void initUartUSB()
{

    UART2_Params uart2Params;

    UART2_Params_init(&uart2Params);
    uart2Params.readMode = UART2_Mode_CALLBACK;
    uart2Params.readCallback = uart2ReadCallback;
    uart2Params.baudRate = 9600;

    uart2 = UART2_open(CONFIG_UART2_0, &uart2Params);

    set_uart_usb_in_out_uart2_instance(uart2);

}

static void sensorTaskFunction(UArg arg0, UArg arg1)
{

    ADC_init();

    I2C_init();

    pinHandle = PIN_open(&pinState, pinTable);

    if (!pinHandle)
    {

        SysCtrlSystemReset();

    }

    PIN_setOutputValue(pinHandle, GPIO_LED_0, 1);
    PIN_setOutputValue(pinHandle, GPIO_LED_1, 1);
    PIN_setOutputValue(pinHandle, GPIO_BAT_EN, 0);
    PIN_setOutputValue(pinHandle, GPIO_SENSOR_POWER_EN, 0);

    buttonHandle = PIN_open(&buttonState, buttonTable);

    if (!buttonHandle)
    {

        SysCtrlSystemReset();

    }

    PIN_registerIntCb(buttonHandle, &buttonCallback);

    initUartUSB();

    while (radio_init == 0x00)
    {

        wait_ms(100);

    }

    set_uart_usb_in_out_write_string("\n\n");
    set_uart_usb_in_out_write_string("Start AxDen Smart Agriculture Example");

    set_uart_usb_in_out_mac_address(mac_address);

    battery_voltage = battery_value_read();

    set_uart_usb_in_out_battery(battery_voltage);

    initSensor();

    PIN_setOutputValue(pinHandle, GPIO_LED_0, 0);
    PIN_setOutputValue(pinHandle, GPIO_LED_1, 0);

    wait_ms(100);

    on_off_mode = 0x01;

    init_state = 0x01;

    while (1)
    {

        uint32_t events = Event_pend(sensorEventHandle, 0,
        SENSOR_TASK_EVENT_ALL,
                                     BIOS_WAIT_FOREVER);

        if (events == SENSOR_TASK_SENSOR_UPDATE)
        {

            battery_voltage = battery_value_read();

            get_bme280_temperature(&temperature);

            get_bme280_pressure(&pressure);

            get_hdc1080_temperature_humidity(&temperature, &humidity);

            get_vcnl4040_ambient_light(&ambient_light);

            set_uart_usb_in_out_battery(battery_voltage);

            set_uart_usb_in_out_temperature(temperature);

            set_uart_usb_in_out_pressure(pressure);

            set_uart_usb_in_out_humidity(humidity);

            set_uart_usb_in_out_lux(ambient_light);

            if (packetSendRequestCallback)
            {

                payload_size = 0;
                memset(payload, 0x00, sizeof(payload));

                payload_size = sprintf((char*) payload, "%d.%d,",
                                       (battery_voltage / 10),
                                       (battery_voltage % 10));

                payload_size += sprintf((char*) payload + payload_size,
                                        "%d.%d,", (temperature / 10),
                                        abs(temperature % 10));

                payload_size += sprintf((char*) payload + payload_size, "%ld,",
                                        pressure);

                payload_size += sprintf((char*) payload + payload_size, "%d,",
                                        humidity);

                payload_size += sprintf((char*) payload + payload_size, "%d",
                                        ambient_light);

                packetSendRequestCallback(payload, payload_size);

            }

        }

        sensor_task_release_state = 0x00;

    }

}

void SensorTask_init(void)
{

    Event_Params eventParam;
    Event_Params_init(&eventParam);
    Event_construct(&sensorEvent, &eventParam);
    sensorEventHandle = Event_handle(&sensorEvent);

    Task_Params_init(&sensorTaskParams);
    sensorTaskParams.stackSize = SENSOR_TASK_STACK_SIZE;
    sensorTaskParams.priority = SENSOR_TASK_TASK_PRIORITY;
    sensorTaskParams.stack = &sensorTaskStack;
    Task_construct(&sensorTask, sensorTaskFunction, &sensorTaskParams, NULL);

    Watchdog_init();

    Watchdog_Params watchdogParams;
    Watchdog_Params_init(&watchdogParams);
    watchdogParams.callbackFxn = (Watchdog_Callback) watchdogCallback;
    watchdogParams.debugStallMode = Watchdog_DEBUG_STALL_ON;
    watchdogParams.resetMode = Watchdog_RESET_ON;

    watchdogHandle = Watchdog_open(CONFIG_WATCHDOG_0, &watchdogParams);

    if (watchdogHandle == NULL)
    {

        SysCtrlSystemReset();

    }

    uint32_t reloadValue = Watchdog_convertMsToTicks(watchdogHandle,
    WATCHDOG_TIMEOUT_MS);

    if (reloadValue != 0)
    {

        Watchdog_setReload(watchdogHandle, reloadValue);

    }

    Clock_Params clockParams;
    Clock_Params_init(&clockParams);
    clockParams.period = TIMER_TIMEOUT * 1000 / Clock_tickPeriod;
    clockParams.startFlag = TRUE;
    Clock_construct(&sensorTimerClock, sensorTimerClockCallBack,
    TIMER_TIMEOUT * 1000 / Clock_tickPeriod,
                    &clockParams);

}

void SensorTask_registerPacketSendRequestCallback(
        PacketSendRequestCallback callback)
{

    packetSendRequestCallback = callback;

}

void uart2ReadCallback(UART2_Handle handle, void *rxBuf, size_t size,
                       void *userArg, int_fast16_t status)
{
    if (status == UART2_STATUS_SUCCESS)
    {

        UART2_read(handle, &uart2_read_buf, 1, NULL);

    }

}

