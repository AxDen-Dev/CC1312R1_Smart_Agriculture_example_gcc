
#ifndef BME280_H_
#define BME280_H_

#include <stdint.h>
#include "board_define.h"

#ifdef CC1312R1

#include <ti/drivers/I2C.h>
#include "ti_drivers_config.h"

#endif

#ifdef CC1312R1

void set_bme280_i2c_instance(I2C_Handle i2cInstance);

#endif

uint8_t init_bme280();

uint8_t get_bme280_temperature(int16_t *temperature_output);

uint8_t get_bme280_pressure(uint32_t *pressure_output);

#endif /* BME280_H_ */
