################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -Ooff --fp_mode=relaxed --include_path="C:/Users/User/workspace_v12/led_ex2_blinky_sysconfig_cpu2" --include_path="C:/Users/User/workspace_v12/led_ex2_blinky_sysconfig_cpu2/device" --include_path="C:/ti/c2000/C2000Ware_5_02_00_00/driverlib/f2838x/driverlib" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=_FLASH --define=DEBUG --define=CPU2 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/User/workspace_v12/led_ex2_blinky_sysconfig_cpu2/FLASH/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1126554911: ../led_ex2_blinky_sysconfig_cpu2.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs1240/ccs/utils/sysconfig_1.17.0/sysconfig_cli.bat" -s "C:/ti/c2000/C2000Ware_5_02_00_00/.metadata/sdk.json" -d "F2838x" --script "C:/Users/User/workspace_v12/led_ex2_blinky_sysconfig_cpu1/led_ex2_blinky_sysconfig_cpu1.syscfg" --context "CPU1" --script "C:/Users/User/workspace_v12/led_ex2_blinky_sysconfig_cpu2/led_ex2_blinky_sysconfig_cpu2.syscfg" --context "CPU2" -o "syscfg" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-1126554911 ../led_ex2_blinky_sysconfig_cpu2.syscfg
syscfg/board.h: build-1126554911
syscfg/board.cmd.genlibs: build-1126554911
syscfg/board.opt: build-1126554911
syscfg/board.json: build-1126554911
syscfg/pinmux.csv: build-1126554911
syscfg/c2000ware_libraries.cmd.genlibs: build-1126554911
syscfg/c2000ware_libraries.opt: build-1126554911
syscfg/c2000ware_libraries.c: build-1126554911
syscfg/c2000ware_libraries.h: build-1126554911
syscfg/clocktree.h: build-1126554911
syscfg/: build-1126554911

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -Ooff --fp_mode=relaxed --include_path="C:/Users/User/workspace_v12/led_ex2_blinky_sysconfig_cpu2" --include_path="C:/Users/User/workspace_v12/led_ex2_blinky_sysconfig_cpu2/device" --include_path="C:/ti/c2000/C2000Ware_5_02_00_00/driverlib/f2838x/driverlib" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=_FLASH --define=DEBUG --define=CPU2 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/User/workspace_v12/led_ex2_blinky_sysconfig_cpu2/FLASH/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


