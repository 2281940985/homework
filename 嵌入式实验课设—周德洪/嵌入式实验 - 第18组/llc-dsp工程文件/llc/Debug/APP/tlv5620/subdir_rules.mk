################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
APP/tlv5620/tlv5620.obj: ../APP/tlv5620/tlv5620.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/adc" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/key" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/iic" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/leds" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/APP/epwm" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_common/include" --include_path="C:/Users/MyPC/Desktop/dsp28335/llc/DSP2833x_Libraries/DSP2833x_headers/include" --include_path="D:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.2/include" -g --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="APP/tlv5620/tlv5620.pp" --obj_directory="APP/tlv5620" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


