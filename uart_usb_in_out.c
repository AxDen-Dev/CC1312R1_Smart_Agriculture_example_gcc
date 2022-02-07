
#include "uart_usb_in_out.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifdef CC1312R1

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>

#endif

#define UART_BUFFER_SIZE 255

static uint16_t uart_tx_buffer_length = 0x00;
static uint8_t uart_tx_buffer[UART_BUFFER_SIZE] = { 0x00 };

#ifdef CC1312R1

static UART2_Handle uart2;

#endif

#ifdef CC1312R1

void set_uart_usb_in_out_uart2_instance(UART2_Handle uart)
{

    uart2 = uart;

}

#endif

static void uart_usb_in_out_data_send(uint8_t *data, uint16_t size)
{

#ifdef CC1312R1

    if (uart2 != NULL)
    {

        UART2_write(uart2, data, size, NULL);

    }

#endif

}

void set_uart_usb_in_out_write_string(char *data)
{

    uart_tx_buffer_length = 0;
    memset(uart_tx_buffer, 0x00, sizeof(uart_tx_buffer));

    uart_tx_buffer_length = sprintf((char*) uart_tx_buffer, "%s\r\n", data);

    uart_usb_in_out_data_send(uart_tx_buffer, uart_tx_buffer_length);

}

void set_uart_usb_in_out_mac_address(uint8_t *mac_address)
{

    uart_tx_buffer_length = 0;
    memset(uart_tx_buffer, 0x00, sizeof(uart_tx_buffer));

    uart_tx_buffer_length = sprintf((char*) uart_tx_buffer, "MAC Address : ");

    for (uint8_t i = 0; i < 8; i++)
    {

        uart_tx_buffer_length += sprintf(
                (char*) uart_tx_buffer + uart_tx_buffer_length, "%02X",
                mac_address[i]);

    }

    uart_tx_buffer_length += sprintf(
            (char*) uart_tx_buffer + uart_tx_buffer_length, "\r\n");

    uart_usb_in_out_data_send(uart_tx_buffer, uart_tx_buffer_length);

}

void set_uart_usb_in_out_find_i2c_address(uint8_t address)
{

    uart_tx_buffer_length = 0;
    memset(uart_tx_buffer, 0x00, sizeof(uart_tx_buffer));

    uart_tx_buffer_length = sprintf((char*) uart_tx_buffer,
                                    "I2C Address : %02X\r\n", address);

    uart_usb_in_out_data_send(uart_tx_buffer, uart_tx_buffer_length);

}

void set_uart_usb_in_out_temperature(int16_t temperature)
{

    uart_tx_buffer_length = 0;
    memset(uart_tx_buffer, 0x00, sizeof(uart_tx_buffer));

    uart_tx_buffer_length = sprintf((char*) uart_tx_buffer,
                                    "Temperature : %d.%d\r\n", temperature / 10,
                                    temperature % 10);

    uart_usb_in_out_data_send(uart_tx_buffer, uart_tx_buffer_length);

}

void set_uart_usb_in_out_pressure(uint32_t pressure)
{

    uart_tx_buffer_length = 0;
    memset(uart_tx_buffer, 0x00, sizeof(uart_tx_buffer));

    uart_tx_buffer_length = sprintf((char*) uart_tx_buffer,
                                    "Pressure : %ld\r\n", pressure);

    uart_usb_in_out_data_send(uart_tx_buffer, uart_tx_buffer_length);

}

void set_uart_usb_in_out_humidity(uint8_t humidity)
{

    uart_tx_buffer_length = 0;
    memset(uart_tx_buffer, 0x00, sizeof(uart_tx_buffer));

    uart_tx_buffer_length = sprintf((char*) uart_tx_buffer, "Humidity : %d\r\n",
                                    humidity);

    uart_usb_in_out_data_send(uart_tx_buffer, uart_tx_buffer_length);

}

void set_uart_usb_in_out_lux(uint16_t lux)
{

    uart_tx_buffer_length = 0;
    memset(uart_tx_buffer, 0x00, sizeof(uart_tx_buffer));

    uart_tx_buffer_length = sprintf((char*) uart_tx_buffer, "Lux : %d\r\n",
                                    lux);

    uart_usb_in_out_data_send(uart_tx_buffer, uart_tx_buffer_length);

}

void set_uart_usb_in_out_battery(uint8_t battery)
{

    uart_tx_buffer_length = 0;
    memset(uart_tx_buffer, 0x00, sizeof(uart_tx_buffer));

    uart_tx_buffer_length = sprintf((char*) uart_tx_buffer,
                                    "Battery : %d.%dV\r\n", (battery / 10),
                                    (battery % 10));

    uart_usb_in_out_data_send(uart_tx_buffer, uart_tx_buffer_length);

}
