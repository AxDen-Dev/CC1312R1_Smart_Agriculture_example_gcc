
#include "hdc1080.h"
#include "string.h"

#ifdef CC1312R1

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>

#endif

#define HDC1080_ADDRESS 0x40

#ifdef CC1312R1

static I2C_Handle i2c;
static I2C_Transaction i2cTransaction;

#endif

static void wait_100_ms()
{

#ifdef CC1312R1

    Task_sleep(100 * 1000 / Clock_tickPeriod);

#endif

}

#ifdef CC1312R1

void set_hdc1080_i2c_instance(I2C_Handle i2cInstance)
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

static uint8_t i2c_write_buffer(uint8_t address, uint8_t reg, uint8_t *value,
                                const uint8_t buffer_size)
{

    uint8_t i2c_state = 0x00;
    uint8_t txBuffer[buffer_size + 1];
    txBuffer[0] = reg;
    memcpy(txBuffer + 1, value, buffer_size);

#ifdef CC1312R1

    if (i2c != NULL)
    {

        i2cTransaction.writeBuf = txBuffer;
        i2cTransaction.readBuf = NULL;
        i2cTransaction.slaveAddress = address;

        i2cTransaction.writeCount = buffer_size + 1;
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

uint8_t init_hdc1080()
{

    uint8_t i2c_state = 0x00;
    uint8_t init_value[2] = { 0x00 };

    //Reset
    init_value[0] = 0b10000000;
    init_value[1] = 0b00000000;

    i2c_state = i2c_write_buffer(HDC1080_ADDRESS, 0x02, init_value, 2);

    for (uint8_t i = 0; i < 2; i++)
    {

        wait_100_ms();

    }

    init_value[0] = 0b00010010;
    init_value[1] = 0b00000000;

    i2c_state = i2c_state
            & i2c_write_buffer(HDC1080_ADDRESS, 0x02, init_value, 2);

    return i2c_state;

}

uint8_t get_hdc1080_temperature_humidity(int16_t *temperature_output,
                                         uint8_t *humidity_output)
{

    uint8_t i2c_state = 0x00;
    uint8_t read_buffer[4] = { 0x00 };

    i2c_state = i2c_write8(HDC1080_ADDRESS, 0x00);

    for (uint8_t i = 0; i < 2; i++)
    {

        wait_100_ms();

    }

    i2c_state = i2c_state & i2c_read_buffer(HDC1080_ADDRESS, read_buffer, 4);

    uint16_t value = read_buffer[0] << 8 | read_buffer[1];
    float temperature = ((float) value / 65536.0f) * 165.0f - 40.0f;
    temperature *= 10;

    value = read_buffer[2] << 8 | read_buffer[3];
    float humidity = ((float) value / 65536.0f) * 100.0f;

    if (humidity > 100)
    {

        humidity = 100;

    }
    else if (humidity < 0)
    {

        humidity = 0;

    }

    *temperature_output = (int16_t) temperature;
    *humidity_output = (uint8_t) humidity;

    return i2c_state;

}

