#ifndef VCNL4040_H_
#define VCNL4040_H_

#include <stdint.h>
#include "board_define.h"

#ifdef CC1312R1

#include <ti/drivers/I2C.h>
#include "ti_drivers_config.h"

#endif

#ifdef CC1312R1

void set_vcnl4040_i2c_instance(I2C_Handle i2cInstance);

#endif

uint8_t init_vcnl4040();

uint8_t get_vcnl4040_ambient_light(uint16_t *ambient_light);

#endif /* VCNL4040_H_ */
