
#include "bme280.h"
#include "string.h"

#ifdef CC1312R1

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>

#endif

#define BME280_ADDRESS 0x76

#ifdef CC1312R1

static I2C_Handle i2c;
static I2C_Transaction i2cTransaction;

#endif

enum
{
    BMP280_REGISTER_DIG_T1 = 0x88,
    BMP280_REGISTER_DIG_T2 = 0x8A,
    BMP280_REGISTER_DIG_T3 = 0x8C,

    BMP280_REGISTER_DIG_P1 = 0x8E,
    BMP280_REGISTER_DIG_P2 = 0x90,
    BMP280_REGISTER_DIG_P3 = 0x92,
    BMP280_REGISTER_DIG_P4 = 0x94,
    BMP280_REGISTER_DIG_P5 = 0x96,
    BMP280_REGISTER_DIG_P6 = 0x98,
    BMP280_REGISTER_DIG_P7 = 0x9A,
    BMP280_REGISTER_DIG_P8 = 0x9C,
    BMP280_REGISTER_DIG_P9 = 0x9E,

    BMP280_REGISTER_CHIPID = 0xD0,
    BMP280_REGISTER_VERSION = 0xD1,
    BMP280_REGISTER_SOFTRESET = 0xE0,

    BMP280_REGISTER_CAL26 = 0xE1,  // R calibration stored in 0xE1-0xF0

    BMP280_REGISTER_CONTROL = 0xF4,
    BMP280_REGISTER_CONFIG = 0xF5,
    BMP280_REGISTER_PRESSUREDATA = 0xF7,
    BMP280_REGISTER_TEMPDATA = 0xFA,

};

typedef enum
{
    BMP280_MODE_SLEEP = 0, BMP280_MODE_FORCED = 1, BMP280_MODE_NORMAL = 3
} BMP280_Mode;

typedef enum
{
    BMP280_FILTER_OFF = 0,
    BMP280_FILTER_2 = 1,
    BMP280_FILTER_4 = 2,
    BMP280_FILTER_8 = 3,
    BMP280_FILTER_16 = 4
} BMP280_Filter;

/**
 * Pressure oversampling settings
 */
typedef enum
{
    BMP280_SKIPPED = 0, /* no measurement  */
    BMP280_ULTRA_LOW_POWER = 1, /* oversampling x1 */
    BMP280_LOW_POWER = 2, /* oversampling x2 */
    BMP280_STANDARD = 3, /* oversampling x4 */
    BMP280_HIGH_RES = 4, /* oversampling x8 */
    BMP280_ULTRA_HIGH_RES = 5 /* oversampling x16 */
} BMP280_Oversampling;

typedef enum
{
    BMP280_STANDBY_05 = 0, /* stand by time 0.5ms */
    BMP280_STANDBY_62 = 1, /* stand by time 62.5ms */
    BMP280_STANDBY_125 = 2, /* stand by time 125ms */
    BMP280_STANDBY_250 = 3, /* stand by time 250ms */
    BMP280_STANDBY_500 = 4, /* stand by time 500ms */
    BMP280_STANDBY_1000 = 5, /* stand by time 1s */
    BMP280_STANDBY_2000 = 6, /* stand by time 2s BMP280, 10ms BME280 */
    BMP280_STANDBY_4000 = 7, /* stand by time 4s BMP280, 20ms BME280 */
} BMP280_StandbyTime;

static uint16_t t1 = 0x00;
static int16_t t2 = 0x00;
static int16_t t3 = 0x00;
static uint16_t p1 = 0x00;
static int16_t p2 = 0x00;
static int16_t p3 = 0x00;
static int16_t p4 = 0x00;
static int16_t p5 = 0x00;
static int16_t p6 = 0x00;
static int16_t p7 = 0x00;
static int16_t p8 = 0x00;
static int16_t p9 = 0x00;
static int32_t t_fine = 0x00;

static void wait_100_ms()
{

#ifdef CC1312R1

    Task_sleep(100 * 1000 / Clock_tickPeriod);

#endif

}

#ifdef CC1312R1

void set_bme280_i2c_instance(I2C_Handle i2cInstance)
{

    i2c = i2cInstance;

}

#endif

static uint8_t i2c_write8(uint8_t address, uint8_t reg)
{

    uint8_t i2c_state = 0x00;
    uint8_t txBuffer = reg;

#ifdef CC1312R1

    if (i2c != NULL)
    {

        i2cTransaction.writeBuf = &txBuffer;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.slaveAddress = address;

        i2cTransaction.writeCount = 1;
        i2cTransaction.readCount = 0;
        i2c_state = I2C_transfer(i2c, &i2cTransaction);

    }

#endif

    return i2c_state;

}

static uint8_t i2c_write16(uint8_t address, uint8_t reg, uint8_t value)
{

    uint8_t i2c_state = 0x00;
    uint8_t txBuffer[2] = { 0x00 };
    txBuffer[0] = reg;
    txBuffer[1] = value;

#ifdef CC1312R1

    if (i2c != NULL)
    {

        i2cTransaction.writeBuf = &txBuffer;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.slaveAddress = address;

        i2cTransaction.writeCount = 2;
        i2cTransaction.readCount = 0;
        i2c_state = I2C_transfer(i2c, &i2cTransaction);

    }

#endif

    return i2c_state;

}

static uint8_t i2c_read_buffer(uint8_t address, uint8_t *read_value,
                               const uint8_t buffer_size)
{

    uint8_t i2c_state = 0x00;
    uint8_t rxBuffer[buffer_size];

#ifdef CC1312R1

    if (i2c != NULL)
    {

        i2cTransaction.writeBuf = NULL;
        i2cTransaction.readBuf = rxBuffer;
        i2cTransaction.slaveAddress = address;

        i2cTransaction.writeCount = 0;
        i2cTransaction.readCount = buffer_size;
        i2c_state = I2C_transfer(i2c, &i2cTransaction);

        memcpy(read_value, rxBuffer, buffer_size);

    }

#endif

    return i2c_state;

}

uint8_t init_bme280()
{

    uint8_t i2c_state = 0x00;
    uint8_t calibration_value_buffer[24];

    //Reset
    i2c_state = i2c_write16(BME280_ADDRESS, BMP280_REGISTER_SOFTRESET, 0xB6);

    wait_100_ms(2);

    i2c_state = i2c_state & i2c_write8(BME280_ADDRESS, 0x88);

    i2c_state = i2c_state
            & i2c_read_buffer(BME280_ADDRESS, calibration_value_buffer, 24);

    t1 = calibration_value_buffer[1] << 8 | calibration_value_buffer[0];
    t2 = calibration_value_buffer[3] << 8 | calibration_value_buffer[2];
    t3 = calibration_value_buffer[5] << 8 | calibration_value_buffer[4];

    p1 = calibration_value_buffer[7] << 8 | calibration_value_buffer[6];
    p2 = calibration_value_buffer[9] << 8 | calibration_value_buffer[9];
    p3 = calibration_value_buffer[11] << 8 | calibration_value_buffer[10];
    p4 = calibration_value_buffer[13] << 8 | calibration_value_buffer[12];
    p5 = calibration_value_buffer[15] << 8 | calibration_value_buffer[14];
    p6 = calibration_value_buffer[17] << 8 | calibration_value_buffer[16];
    p7 = calibration_value_buffer[19] << 8 | calibration_value_buffer[18];
    p8 = calibration_value_buffer[21] << 8 | calibration_value_buffer[20];
    p9 = calibration_value_buffer[23] << 8 | calibration_value_buffer[22];

    wait_100_ms(2);

    uint8_t filter_odr = (BMP280_STANDBY_250 << 5) | (BMP280_FILTER_OFF << 2);
    i2c_state = i2c_state
            & i2c_write16(BME280_ADDRESS, BMP280_REGISTER_CONFIG, filter_odr);

    wait_100_ms(2);

    i2c_state = i2c_state
            & i2c_write16(BME280_ADDRESS, BMP280_REGISTER_CONTROL, 0x3F);

    wait_100_ms(2);

    i2c_state = i2c_state
            & i2c_write16(BME280_ADDRESS, BMP280_REGISTER_CONTROL, 0x3C);

    return i2c_state;

}

uint8_t get_bme280_temperature(int16_t *temperature_output)
{

    uint8_t i2c_state = 0x00;

    int32_t value = 0x00;
    uint8_t read_buffer[3];

    i2c_state = i2c_write8(BME280_ADDRESS, 0xFA);

    i2c_state = i2c_state & i2c_read_buffer(BME280_ADDRESS, read_buffer, 3);

    value = (uint32_t) read_buffer[0] << 16 | (uint32_t) read_buffer[1] << 8
            | (uint32_t) read_buffer[2];
    value >>= 4;

    int32_t value1 = ((((value >> 3) - ((int32_t) t1 << 1))) * ((int32_t) t2))
            >> 11;

    int32_t value2 = (((((value >> 4) - ((int32_t) t1))
            * ((value >> 4) - ((int32_t) t1))) >> 12) * ((int32_t) t3)) >> 14;

    t_fine = value1 + value2;

    float temperature = (t_fine * 5 + 128) >> 8;
    temperature /= 10;

    *temperature_output = (int16_t) temperature;

    return i2c_state;

}

uint8_t get_bme280_pressure(uint32_t *pressure_output)
{

    uint8_t i2c_state = 0x00;

    int32_t value = 0x00;
    uint8_t read_buffer[3];

    i2c_state = i2c_write8(BME280_ADDRESS, 0xF7);

    i2c_state = i2c_state & i2c_read_buffer(BME280_ADDRESS, read_buffer, 3);

    value = (uint32_t) read_buffer[0] << 16 | (uint32_t) read_buffer[1] << 8
            | (uint32_t) read_buffer[2];
    value >>= 4;

    int32_t value1 = ((int64_t) t_fine) - 128000;
    int32_t value2 = value1 * value1 * (int64_t) p6;
    value2 = value2 + ((value1 * (int64_t) p5) << 17);
    value2 = value2 + (((int64_t) p4) << 35);
    value1 = ((value1 * value1 * (int64_t) p3) >> 8)
            + ((value1 * (int64_t) p3) << 12);
    value1 = (((((int64_t) 1) << 47) + value1)) * ((int64_t) p1) >> 33;

    if (value1 == 0)
    {

        return 0x00;

    }

    int64_t pressure = 1048576 - value;
    pressure = (((pressure << 31) - value2) * 3125) / value1;
    value1 = (((int64_t) p9) * (pressure >> 13) * (pressure >> 13)) >> 25;
    value2 = (((int64_t) p8) * pressure) >> 19;

    pressure = ((pressure + value1 + value2) >> 8) + (((int64_t) p7) << 4);
    pressure = pressure / 256;

    if (pressure < 0)
    {

        pressure = 0;

    }

    *pressure_output = (uint32_t) pressure;

    return i2c_state;

}
