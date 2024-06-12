################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -O4 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/F28388D_ZWT337_TIMETASK_CPU1" --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/F28388D_ZWT337_TIMETASK_CPU1/device" --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/F28388D_ZWT337_TIMETASK_CPU1/device/driverlib" --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/F28388D_ZWT337_TIMETASK_CPU1/libraries/calibration/hrpwm/f2838x/include" --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/F28388D_ZWT337_TIMETASK_CPU1/libraries/flash_api/f2838x/c28x/include/FlashAPI" --define=_FLASH --define=DEBUG --define=CPU1 --c99 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/F28388D_ZWT337_TIMETASK_CPU1/FLASH/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1678708479: ../pinmux.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1.20.0/sysconfig_cli.bat" -s "C:/ti/c2000/C2000Ware_5_02_00_00/.metadata/sdk.json" -d "F2838x" --script "C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/F28388D_ZWT337_TIMETASK_CPU2/pinmux.syscfg" --context "CPU2" --script "C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/F28388D_ZWT337_TIMETASK_CPU1/pinmux.syscfg" --context "CPU1" -o "syscfg" --package 337bga --part F2838x_337bga --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-1678708479 ../pinmux.syscfg
syscfg/board.h: build-1678708479
syscfg/board.cmd.genlibs: build-1678708479
syscfg/board.opt: build-1678708479
syscfg/board.json: build-1678708479
syscfg/pinmux.csv: build-1678708479
syscfg/epwm.dot: build-1678708479
syscfg/adc.dot: build-1678708479
syscfg/c2000ware_libraries.cmd.genlibs: build-1678708479
syscfg/c2000ware_libraries.opt: build-1678708479
syscfg/c2000ware_libraries.c: build-1678708479
syscfg/c2000ware_libraries.h: build-1678708479
syscfg/clocktree.h: build-1678708479
syscfg/: build-1678708479

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -O4 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/F28388D_ZWT337_TIMETASK_CPU1" --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/F28388D_ZWT337_TIMETASK_CPU1/device" --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/F28388D_ZWT337_TIMETASK_CPU1/device/driverlib" --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/F28388D_ZWT337_TIMETASK_CPU1/libraries/calibration/hrpwm/f2838x/include" --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/F28388D_ZWT337_TIMETASK_CPU1/libraries/flash_api/f2838x/c28x/include/FlashAPI" --define=_FLASH --define=DEBUG --define=CPU1 --c99 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/User/Desktop/GitHub/GW/C2000/F28388D_DualCore_Timetask/F28388D_ZWT337_TIMETASK_CPU1/FLASH/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


