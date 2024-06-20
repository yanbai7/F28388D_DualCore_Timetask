################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.cla $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -O4 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/led_blinky_driverlib_cla_sysconfig_multi/led_ex2_blinky_sysconfig_cpu1" --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/led_blinky_driverlib_cla_sysconfig_multi/led_ex2_blinky_sysconfig_cpu1/device" --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/led_blinky_driverlib_cla_sysconfig_multi/led_ex2_blinky_sysconfig_cpu1/device/driverlib" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=_FLASH --define=DEBUG --define=CPU1 --c99 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/led_blinky_driverlib_cla_sysconfig_multi/led_ex2_blinky_sysconfig_cpu1/FLASH/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -O4 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/led_blinky_driverlib_cla_sysconfig_multi/led_ex2_blinky_sysconfig_cpu1" --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/led_blinky_driverlib_cla_sysconfig_multi/led_ex2_blinky_sysconfig_cpu1/device" --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/led_blinky_driverlib_cla_sysconfig_multi/led_ex2_blinky_sysconfig_cpu1/device/driverlib" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=_FLASH --define=DEBUG --define=CPU1 --c99 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/led_blinky_driverlib_cla_sysconfig_multi/led_ex2_blinky_sysconfig_cpu1/FLASH/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1879382687: ../pinmux.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1.20.0/sysconfig_cli.bat" -s "C:/ti/c2000/C2000Ware_5_02_00_00/.metadata/sdk.json" -d "F2838x" --script "C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/led_blinky_driverlib_cla_sysconfig_multi/led_ex2_blinky_sysconfig_cpu2/pinmux.syscfg" --context "CPU2" --script "C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/led_blinky_driverlib_cla_sysconfig_multi/led_ex2_blinky_sysconfig_cpu1/pinmux.syscfg" --context "CPU1" -o "syscfg" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-1879382687 ../pinmux.syscfg
syscfg/board.h: build-1879382687
syscfg/board.cmd.genlibs: build-1879382687
syscfg/board.opt: build-1879382687
syscfg/board.json: build-1879382687
syscfg/pinmux.csv: build-1879382687
syscfg/adc.dot: build-1879382687
syscfg/c2000ware_libraries.cmd.genlibs: build-1879382687
syscfg/c2000ware_libraries.opt: build-1879382687
syscfg/c2000ware_libraries.c: build-1879382687
syscfg/c2000ware_libraries.h: build-1879382687
syscfg/clocktree.h: build-1879382687
syscfg/: build-1879382687

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -O4 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/led_blinky_driverlib_cla_sysconfig_multi/led_ex2_blinky_sysconfig_cpu1" --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/led_blinky_driverlib_cla_sysconfig_multi/led_ex2_blinky_sysconfig_cpu1/device" --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/led_blinky_driverlib_cla_sysconfig_multi/led_ex2_blinky_sysconfig_cpu1/device/driverlib" --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=_FLASH --define=DEBUG --define=CPU1 --c99 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/led_blinky_driverlib_cla_sysconfig_multi/led_ex2_blinky_sysconfig_cpu1/FLASH/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


