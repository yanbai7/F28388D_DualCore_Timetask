################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../2838x_FLASH_CLA_lnk_cpu1.cmd 

SYSCFG_SRCS += \
../led_ex2_blinky_sysconfig_cpu1.syscfg 

CLA_SRCS += \
../cla_ex4_pwm_control_cla.cla 

LIB_SRCS += \
../driverlib.lib 

C_SRCS += \
../led_ex2_blinky_sysconfig_cpu1.c \
./syscfg/board.c \
./syscfg/c2000ware_libraries.c 

GEN_FILES += \
./syscfg/board.c \
./syscfg/board.opt \
./syscfg/c2000ware_libraries.opt \
./syscfg/c2000ware_libraries.c 

CLA_DEPS += \
./cla_ex4_pwm_control_cla.d 

GEN_MISC_DIRS += \
./syscfg/ 

C_DEPS += \
./led_ex2_blinky_sysconfig_cpu1.d \
./syscfg/board.d \
./syscfg/c2000ware_libraries.d 

GEN_OPTS += \
./syscfg/board.opt \
./syscfg/c2000ware_libraries.opt 

OBJS += \
./cla_ex4_pwm_control_cla.obj \
./led_ex2_blinky_sysconfig_cpu1.obj \
./syscfg/board.obj \
./syscfg/c2000ware_libraries.obj 

GEN_MISC_FILES += \
./syscfg/board.h \
./syscfg/board.cmd.genlibs \
./syscfg/board.json \
./syscfg/pinmux.csv \
./syscfg/adc.dot \
./syscfg/c2000ware_libraries.cmd.genlibs \
./syscfg/c2000ware_libraries.h \
./syscfg/clocktree.h 

GEN_MISC_DIRS__QUOTED += \
"syscfg\" 

OBJS__QUOTED += \
"cla_ex4_pwm_control_cla.obj" \
"led_ex2_blinky_sysconfig_cpu1.obj" \
"syscfg\board.obj" \
"syscfg\c2000ware_libraries.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\board.h" \
"syscfg\board.cmd.genlibs" \
"syscfg\board.json" \
"syscfg\pinmux.csv" \
"syscfg\adc.dot" \
"syscfg\c2000ware_libraries.cmd.genlibs" \
"syscfg\c2000ware_libraries.h" \
"syscfg\clocktree.h" 

C_DEPS__QUOTED += \
"led_ex2_blinky_sysconfig_cpu1.d" \
"syscfg\board.d" \
"syscfg\c2000ware_libraries.d" 

GEN_FILES__QUOTED += \
"syscfg\board.c" \
"syscfg\board.opt" \
"syscfg\c2000ware_libraries.opt" \
"syscfg\c2000ware_libraries.c" 

CLA_DEPS__QUOTED += \
"cla_ex4_pwm_control_cla.d" 

C_SRCS__QUOTED += \
"../led_ex2_blinky_sysconfig_cpu1.c" \
"./syscfg/board.c" \
"./syscfg/c2000ware_libraries.c" 

SYSCFG_SRCS__QUOTED += \
"../led_ex2_blinky_sysconfig_cpu1.syscfg" 


