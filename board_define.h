#ifndef BOARD_DEFINE_H_
#define BOARD_DEFINE_H_

#define CC1312R1

#include <ti/devices/cc13x2_cc26x2/driverlib/ioc.h>

#define SPI_MOSI_GPIO IOID_21 //PinNumber 31
#define SPI_MISO_GPIO IOID_20 //PinNumber 30
#define SPI_SCK_GPIO IOID_19 //PinNumber 29
#define SPI_CS_GPIO IOID_18 //PinNumber 28

#define UART_2_TX_GPIO IOID_17 //PinNumber 27
#define UART_2_RX_GPIO IOID_16 //PinNumber 26

#define ADC_0_GPIO IOID_24 //PinNumber 37
#define ADC_1_GPIO IOID_25 //PinNumber 38

#define UART_1_RX_GPIO IOID_10 //PinNumber 16
#define UART_1_TX_GPIO IOID_9 //PinNumber 15

#define GPIO_0_GPIO IOID_8 //PinNumber 14
#define GPIO_1_GPIO IOID_7 //PinNumber 12
#define GPIO_2_GPIO IOID_6 //PinNumber 11
#define GPIO_3_GPIO IOID_5 //PinNumber 10

#define I2C_SDA_GPIO IOID_4 //PinNumber 9
#define I2C_SCL_GPIO IOID_3 //PinNumber 8

#define GPIO_WKUP_GPIO IOID_2 //PinNumber 7

//Application Board PinMap

#define GPIO_LED_0 SPI_MISO_GPIO
#define GPIO_LED_1 SPI_MOSI_GPIO

#define GPIO_BTN SPI_SCK_GPIO

#define GPIO_BAT_LEVEL ADC_0_GPIO
#define GPIO_MOISTURE_LEVEL ADC_1_GPIO

#define GPIO_SENSOR_POWER_EN GPIO_0_GPIO
#define GPIO_BAT_EN GPIO_1_GPIO

#define GPIO_USB_UART_TX UART_2_RX_GPIO
#define GPIO_USB_UART_RX UART_2_TX_GPIO

#endif /* BOARD_DEFINE_H_ */
