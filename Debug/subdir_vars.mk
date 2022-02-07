################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
SYSCFG_SRCS += \
../rfWsnNode.syscfg 

LDS_SRCS += \
../cc13x2_cc26x2_tirtos.lds 

C_SRCS += \
../RadioTask.c \
../SensorTask.c \
../bme280.c \
../hdc1080.c \
../main.c \
./syscfg/ti_easylink_config.c \
./syscfg/ti_devices_config.c \
./syscfg/ti_radio_config.c \
./syscfg/ti_drivers_config.c \
../uart_usb_in_out.c \
../vcnl4040.c 

GEN_FILES += \
./syscfg/ti_easylink_config.c \
./syscfg/device_config.opt \
./syscfg/ti_devices_config.c \
./syscfg/ti_radio_config.c \
./syscfg/ti_drivers_config.c 

GEN_MISC_DIRS += \
./syscfg/ 

C_DEPS += \
./RadioTask.d \
./SensorTask.d \
./bme280.d \
./hdc1080.d \
./main.d \
./syscfg/ti_easylink_config.d \
./syscfg/ti_devices_config.d \
./syscfg/ti_radio_config.d \
./syscfg/ti_drivers_config.d \
./uart_usb_in_out.d \
./vcnl4040.d 

GEN_OPTS += \
./syscfg/device_config.opt 

OBJS += \
./RadioTask.o \
./SensorTask.o \
./bme280.o \
./hdc1080.o \
./main.o \
./syscfg/ti_easylink_config.o \
./syscfg/ti_devices_config.o \
./syscfg/ti_radio_config.o \
./syscfg/ti_drivers_config.o \
./uart_usb_in_out.o \
./vcnl4040.o 

GEN_MISC_FILES += \
./syscfg/ti_easylink_config.h \
./syscfg/ti_radio_config.h \
./syscfg/ti_drivers_config.h \
./syscfg/ti_utils_build_linker.cmd.genlibs \
./syscfg/syscfg_c.rov.xs \
./syscfg/ti_utils_runtime_model.gv \
./syscfg/ti_utils_runtime_Makefile 

GEN_MISC_DIRS__QUOTED += \
"syscfg/" 

OBJS__QUOTED += \
"RadioTask.o" \
"SensorTask.o" \
"bme280.o" \
"hdc1080.o" \
"main.o" \
"syscfg/ti_easylink_config.o" \
"syscfg/ti_devices_config.o" \
"syscfg/ti_radio_config.o" \
"syscfg/ti_drivers_config.o" \
"uart_usb_in_out.o" \
"vcnl4040.o" 

GEN_MISC_FILES__QUOTED += \
"syscfg/ti_easylink_config.h" \
"syscfg/ti_radio_config.h" \
"syscfg/ti_drivers_config.h" \
"syscfg/ti_utils_build_linker.cmd.genlibs" \
"syscfg/syscfg_c.rov.xs" \
"syscfg/ti_utils_runtime_model.gv" \
"syscfg/ti_utils_runtime_Makefile" 

C_DEPS__QUOTED += \
"RadioTask.d" \
"SensorTask.d" \
"bme280.d" \
"hdc1080.d" \
"main.d" \
"syscfg/ti_easylink_config.d" \
"syscfg/ti_devices_config.d" \
"syscfg/ti_radio_config.d" \
"syscfg/ti_drivers_config.d" \
"uart_usb_in_out.d" \
"vcnl4040.d" 

GEN_FILES__QUOTED += \
"syscfg/ti_easylink_config.c" \
"syscfg/device_config.opt" \
"syscfg/ti_devices_config.c" \
"syscfg/ti_radio_config.c" \
"syscfg/ti_drivers_config.c" 

C_SRCS__QUOTED += \
"../RadioTask.c" \
"../SensorTask.c" \
"../bme280.c" \
"../hdc1080.c" \
"../main.c" \
"./syscfg/ti_easylink_config.c" \
"./syscfg/ti_devices_config.c" \
"./syscfg/ti_radio_config.c" \
"./syscfg/ti_drivers_config.c" \
"../uart_usb_in_out.c" \
"../vcnl4040.c" 

SYSCFG_SRCS__QUOTED += \
"../rfWsnNode.syscfg" 


