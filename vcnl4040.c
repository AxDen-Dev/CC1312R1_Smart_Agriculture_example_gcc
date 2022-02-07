#include "vcnl4040.h"
#include "string.h"

#ifdef CC1312R1

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>

#endif

#define VCNL4040_ADDRESS 0x60
#define ALS_CONF 0x00
#define PS_CONF1_2 0x03
#define PS_CONF3_PS_MS 0x04
#define PS_Data 0x08
#define ALS_Data 0x09
#define White_Data 0x0A
#define ID 0x0C

typedef union
{

    struct
    {

        uint16_t ALS_SD :1;
        uint16_t ALS_INT_EN :1;
        uint16_t ALS_PERS :2;
        uint16_t Reserved0 :2;
        uint16_t ALS_IT :2;
        uint16_t Reserved1 :8;

    } bits;

    uint16_t value;

} als_conf_t;

typedef union
{

    struct
    {

        uint16_t PS_SD :1;
        uint16_t PS_IT :3;
        uint16_t PS_PERS :2;
        uint16_t PS_Duty :2;

        uint16_t PS_INT :2;
        uint16_t Reserved0 :1;
        uint16_t PS_HD :1;
        uint16_t Reserved1 :4;

    } bits;

    uint16_t value;

} ps_conf1_2;

typedef union
{

    struct
    {

        uint16_t PS_SC_EN :1;
        uint16_t Reserved0 :1;
        uint16_t PS_TRIG :1;
        uint16_t PS_AF :1;
        uint16_t PS_SMART_PERS :1;
        uint16_t PS_MPS :2;
        uint16_t Reserved1 :1;

        uint16_t LED_I :3;
        uint16_t Reserved2 :3;
        uint16_t PS_MS :1;
        uint16_t White_EN :1;

    } bits;

    uint16_t value;

} ps_conf3_ps_ms;

#ifdef CC1312R1

static I2C_Handle i2c;
static I2C_Transaction i2cTransaction;

#endif

#ifdef CC1312R1

void set_vcnl4040_i2c_instance(I2C_Handle i2cInstance)
{

    i2c = i2cInstance;

}

#endif

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

static uint8_t i2c_read_buffer(uint8_t address, uint8_t reg,
                               uint8_t *read_value, const uint8_t buffer_size)
{

    uint8_t i2c_state = 0x00;
    uint8_t txValue = reg;
    uint8_t rxBuffer[buffer_size];

#ifdef CC1312R1

    if (i2c != NULL)
    {

        i2cTransaction.writeBuf = &txValue;
        i2cTransaction.readBuf = rxBuffer;
        i2cTransaction.slaveAddress = address;

        i2cTransaction.writeCount = 1;
        i2cTransaction.readCount = buffer_size;
        i2c_state = I2C_transfer(i2c, &i2cTransaction);

        memcpy(read_value, rxBuffer, buffer_size);

    }

#endif

    return i2c_state;

}

uint8_t init_vcnl4040()
{

    uint8_t i2c_state = 0x00;
    uint8_t init_value[2] = { 0x00 };

    als_conf_t als_conf;
    als_conf.value = 0x00;

    init_value[0] = (als_conf.value & 0xFF);
    init_value[1] = (als_conf.value >> 8);
    i2c_state = i2c_write_buffer(VCNL4040_ADDRESS, ALS_CONF, init_value, 2);

    return i2c_state;

}

uint8_t get_vcnl4040_ambient_light(uint16_t *ambient_light)
{

    uint8_t i2c_state = 0x00;
    uint8_t read_value[2] = { 0x00 };

    i2c_state = i2c_read_buffer(VCNL4040_ADDRESS, ALS_Data, read_value, 2);

    uint16_t value = ((uint16_t) read_value[1] << 8 | read_value[0]);
    *ambient_light = value * 0.1;

    return i2c_state;

}
