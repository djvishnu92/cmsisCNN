################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
arm_matrix_example_f32.obj: ../arm_matrix_example_f32.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/home/djvishnu92/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --opt_for_speed=0 --preinclude="/home/djvishnu92/ti/TivaWare_C_Series-2.1.3.156" --include_path="/home/djvishnu92/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="/home/djvishnu92/workspace_v6_2/CMSIS/Include/" --include_path="/home/djvishnu92/workspace_v6_2/CMSIS-master/CMSIS/Include" -g --gcc --define=ccs="ccs" --define=ARM_MATH_CM4 --define=__FPU_PRESENT=1 --define=PART_TM4C123GH6PM --diag_wrap=off --diag_warning=225 --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="arm_matrix_example_f32.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

math_helper.obj: ../math_helper.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/home/djvishnu92/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --opt_for_speed=0 --preinclude="/home/djvishnu92/ti/TivaWare_C_Series-2.1.3.156" --include_path="/home/djvishnu92/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="/home/djvishnu92/workspace_v6_2/CMSIS/Include/" --include_path="/home/djvishnu92/workspace_v6_2/CMSIS-master/CMSIS/Include" -g --gcc --define=ccs="ccs" --define=ARM_MATH_CM4 --define=__FPU_PRESENT=1 --define=PART_TM4C123GH6PM --diag_wrap=off --diag_warning=225 --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="math_helper.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

myNokiaLcd.obj: ../myNokiaLcd.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/home/djvishnu92/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --opt_for_speed=0 --preinclude="/home/djvishnu92/ti/TivaWare_C_Series-2.1.3.156" --include_path="/home/djvishnu92/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="/home/djvishnu92/workspace_v6_2/CMSIS/Include/" --include_path="/home/djvishnu92/workspace_v6_2/CMSIS-master/CMSIS/Include" -g --gcc --define=ccs="ccs" --define=ARM_MATH_CM4 --define=__FPU_PRESENT=1 --define=PART_TM4C123GH6PM --diag_wrap=off --diag_warning=225 --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="myNokiaLcd.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

tm4c123gh6pm_startup_ccs.obj: ../tm4c123gh6pm_startup_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/home/djvishnu92/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --opt_for_speed=0 --preinclude="/home/djvishnu92/ti/TivaWare_C_Series-2.1.3.156" --include_path="/home/djvishnu92/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --include_path="/home/djvishnu92/workspace_v6_2/CMSIS/Include/" --include_path="/home/djvishnu92/workspace_v6_2/CMSIS-master/CMSIS/Include" -g --gcc --define=ccs="ccs" --define=ARM_MATH_CM4 --define=__FPU_PRESENT=1 --define=PART_TM4C123GH6PM --diag_wrap=off --diag_warning=225 --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="tm4c123gh6pm_startup_ccs.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


