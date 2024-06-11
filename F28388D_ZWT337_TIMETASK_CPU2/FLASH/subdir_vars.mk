################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../2838x_FLASH_lnk_cpu2.cmd 

SYSCFG_SRCS += \
../pinmux.syscfg 

LIB_SRCS += \
../F2838x_C28x_FlashAPI.lib \
../SFO_v8_fpu_lib_build_c28_driverlib_eabi.lib \
../driverlib.lib 

C_SRCS += \
../isr.c \
../main.c \
./syscfg/board.c \
./syscfg/c2000ware_libraries.c \
../timetask.c 

GEN_FILES += \
./syscfg/board.c \
./syscfg/board.opt \
./syscfg/c2000ware_libraries.opt \
./syscfg/c2000ware_libraries.c 

GEN_MISC_DIRS += \
./syscfg/ 

C_DEPS += \
./isr.d \
./main.d \
./syscfg/board.d \
./syscfg/c2000ware_libraries.d \
./timetask.d 

GEN_OPTS += \
./syscfg/board.opt \
./syscfg/c2000ware_libraries.opt 

OBJS += \
./isr.obj \
./main.obj \
./syscfg/board.obj \
./syscfg/c2000ware_libraries.obj \
./timetask.obj 

GEN_MISC_FILES += \
./syscfg/board.h \
./syscfg/board.cmd.genlibs \
./syscfg/board.json \
./syscfg/pinmux.csv \
./syscfg/epwm.dot \
./syscfg/adc.dot \
./syscfg/c2000ware_libraries.cmd.genlibs \
./syscfg/c2000ware_libraries.h \
./syscfg/clocktree.h 

GEN_MISC_DIRS__QUOTED += \
"syscfg\" 

OBJS__QUOTED += \
"isr.obj" \
"main.obj" \
"syscfg\board.obj" \
"syscfg\c2000ware_libraries.obj" \
"timetask.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\board.h" \
"syscfg\board.cmd.genlibs" \
"syscfg\board.json" \
"syscfg\pinmux.csv" \
"syscfg\epwm.dot" \
"syscfg\adc.dot" \
"syscfg\c2000ware_libraries.cmd.genlibs" \
"syscfg\c2000ware_libraries.h" \
"syscfg\clocktree.h" 

C_DEPS__QUOTED += \
"isr.d" \
"main.d" \
"syscfg\board.d" \
"syscfg\c2000ware_libraries.d" \
"timetask.d" 

GEN_FILES__QUOTED += \
"syscfg\board.c" \
"syscfg\board.opt" \
"syscfg\c2000ware_libraries.opt" \
"syscfg\c2000ware_libraries.c" 

C_SRCS__QUOTED += \
"../isr.c" \
"../main.c" \
"./syscfg/board.c" \
"./syscfg/c2000ware_libraries.c" \
"../timetask.c" 

SYSCFG_SRCS__QUOTED += \
"../pinmux.syscfg" 


