################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
cla/%.obj: ../cla/%.cla $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -O4 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --include_path="C:/Users/User/workspace_v12/F28388D_ZWT337_TIMETASK_CPU1" --include_path="C:/Users/User/workspace_v12/F28388D_ZWT337_TIMETASK_CPU1/device" --include_path="C:/Users/User/workspace_v12/F28388D_ZWT337_TIMETASK_CPU1/device/driverlib" --include_path="C:/Users/User/workspace_v12/F28388D_ZWT337_TIMETASK_CPU1/libraries/calibration/hrpwm/f2838x/include" --include_path="C:/Users/User/workspace_v12/F28388D_ZWT337_TIMETASK_CPU1/libraries/flash_api/f2838x/c28x/include/FlashAPI" --define=_FLASH --define=DEBUG --define=CPU1 --c99 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="cla/$(basename $(<F)).d_raw" --include_path="C:/Users/User/workspace_v12/F28388D_ZWT337_TIMETASK_CPU1/FLASH/syscfg" --obj_directory="cla" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

cla/%.obj: ../cla/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --idiv_support=idiv0 --tmu_support=tmu0 --vcu_support=vcrc -O4 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/ti/ccs1240/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --include_path="C:/Users/User/workspace_v12/F28388D_ZWT337_TIMETASK_CPU1" --include_path="C:/Users/User/workspace_v12/F28388D_ZWT337_TIMETASK_CPU1/device" --include_path="C:/Users/User/workspace_v12/F28388D_ZWT337_TIMETASK_CPU1/device/driverlib" --include_path="C:/Users/User/workspace_v12/F28388D_ZWT337_TIMETASK_CPU1/libraries/calibration/hrpwm/f2838x/include" --include_path="C:/Users/User/workspace_v12/F28388D_ZWT337_TIMETASK_CPU1/libraries/flash_api/f2838x/c28x/include/FlashAPI" --define=_FLASH --define=DEBUG --define=CPU1 --c99 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="cla/$(basename $(<F)).d_raw" --include_path="C:/Users/User/workspace_v12/F28388D_ZWT337_TIMETASK_CPU1/FLASH/syscfg" --obj_directory="cla" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


