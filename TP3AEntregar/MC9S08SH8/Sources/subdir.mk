################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Buffer.c" \
"../Sources/MCUinit.c" \
"../Sources/main.c" \

C_SRCS += \
../Sources/Buffer.c \
../Sources/MCUinit.c \
../Sources/main.c \

OBJS += \
./Sources/Buffer_c.obj \
./Sources/MCUinit_c.obj \
./Sources/main_c.obj \

OBJS_QUOTED += \
"./Sources/Buffer_c.obj" \
"./Sources/MCUinit_c.obj" \
"./Sources/main_c.obj" \

C_DEPS += \
./Sources/Buffer_c.d \
./Sources/MCUinit_c.d \
./Sources/main_c.d \

OBJS_OS_FORMAT += \
./Sources/Buffer_c.obj \
./Sources/MCUinit_c.obj \
./Sources/main_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/Buffer_c.obj: ../Sources/Buffer.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/Buffer.args" -ObjN="Sources/Buffer_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/MCUinit_c.obj: ../Sources/MCUinit.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/MCUinit.args" -ObjN="Sources/MCUinit_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


