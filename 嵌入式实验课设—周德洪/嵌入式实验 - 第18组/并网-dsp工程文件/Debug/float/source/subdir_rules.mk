################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
float/source/%.obj: ../float/source/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Application/CCS/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/Application/DSP28335_project_jsy/DSP28335_project" --include_path="C:/Application/DSP28335_project_jsy/DSP28335_project/float/include" --include_path="C:/Application/DSP28335_project_jsy/DSP28335_project/float" --include_path="C:/Application/DSP28335_project_jsy/DSP28335_project/APP/adc" --include_path="C:/Application/DSP28335_project_jsy/DSP28335_project/float/source" --include_path="C:/Application/DSP28335_project_jsy/DSP28335_project/APP/epwm" --include_path="C:/Application/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="C:/Application/DSP2833x_Libraries/DSP2833x_common/include" --include_path="C:/Application/CCS/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="float/source/$(basename $(<F)).d_raw" --obj_directory="float/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

float/source/%.obj: ../float/source/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/Application/CCS/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/Application/DSP28335_project_jsy/DSP28335_project" --include_path="C:/Application/DSP28335_project_jsy/DSP28335_project/float/include" --include_path="C:/Application/DSP28335_project_jsy/DSP28335_project/float" --include_path="C:/Application/DSP28335_project_jsy/DSP28335_project/APP/adc" --include_path="C:/Application/DSP28335_project_jsy/DSP28335_project/float/source" --include_path="C:/Application/DSP28335_project_jsy/DSP28335_project/APP/epwm" --include_path="C:/Application/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="C:/Application/DSP2833x_Libraries/DSP2833x_common/include" --include_path="C:/Application/CCS/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="float/source/$(basename $(<F)).d_raw" --obj_directory="float/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


