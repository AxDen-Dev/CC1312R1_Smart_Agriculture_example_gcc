
#ifndef HDC1080_H_
#define HDC1080_H_

#include <stdint.h>
#include "board_define.h"

#ifdef CC1312R1

#include <ti/drivers/I2C.h>
#include "ti_drivers_config.h"

#endif

#ifdef CC1312R1

void set_hdc1080_i2c_instance(I2C_Handle i2cInstance);

#endif

uint8_t init_hdc1080();

uint8_t get_hdc1080_temperature_humidity(int16_t *temperature_output,
                                         uint8_t *humidity_output);

#endif /* HDC1080_H_ */
