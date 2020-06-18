################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Hardware/LED/%.obj: ../Hardware/LED/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs920/ccs/tools/compiler/ti-cgt-c2000_18.12.3.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="D:/workspace_v9_2/PEC_GGber" --include_path="D:/workspace_v9_2/PEC_GGber/Hardware/SCI" --include_path="D:/workspace_v9_2/PEC_GGber/Hardware/DSP_ADC" --include_path="D:/workspace_v9_2/PEC_GGber/Hardware/FAN" --include_path="D:/workspace_v9_2/PEC_GGber/Hardware/EPWM" --include_path="D:/workspace_v9_2/PEC_GGber/Hardware/Mcbsp" --include_path="D:/workspace_v9_2/PEC_GGber/Hardware/LED" --include_path="D:/workspace_v9_2/PEC_GGber/Hardware/System" --include_path="D:/workspace_v9_2/PEC_GGber/Lib/include" --include_path="D:/ti/ccs920/ccs/tools/compiler/ti-cgt-c2000_18.12.3.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="Hardware/LED/$(basename $(<F)).d_raw" --obj_directory="Hardware/LED" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


