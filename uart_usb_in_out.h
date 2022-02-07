
#ifndef UART_USB_IN_OUT_H_
#define UART_USB_IN_OUT_H_

#include <stdint.h>
#include <stdbool.h>
#include "board_define.h"

#ifdef CC1312R1

#include <ti/drivers/I2C.h>
#include <ti/drivers/UART2.h>
#include <ti/drivers/PIN.h>
#include "ti_drivers_config.h"

#endif

#ifdef CC1312R1

void set_uart_usb_in_out_uart2_instance(UART2_Handle uart);

#endif

void set_uart_usb_in_out_write_string(char *data);

void set_uart_usb_in_out_mac_address(uint8_t *mac_address);

void set_uart_usb_in_out_find_i2c_address(uint8_t address);

void set_uart_usb_in_out_temperature(int16_t temperature);

void set_uart_usb_in_out_pressure(uint32_t pressure);

void set_uart_usb_in_out_humidity(uint8_t humidity);

void set_uart_usb_in_out_lux(uint16_t lux);

void set_uart_usb_in_out_battery(uint8_t battery);

#endif /* UART_USB_IN_OUT_H_ */
