################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Reloj/funcion_reloj.c" \

C_SRCS += \
../Sources/Reloj/funcion_reloj.c \

OBJS += \
./Sources/Reloj/funcion_reloj_c.obj \

OBJS_QUOTED += \
"./Sources/Reloj/funcion_reloj_c.obj" \

C_DEPS += \
./Sources/Reloj/funcion_reloj_c.d \

OBJS_OS_FORMAT += \
./Sources/Reloj/funcion_reloj_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/Reloj/funcion_reloj_c.obj: ../Sources/Reloj/funcion_reloj.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/Reloj/funcion_reloj.args" -ObjN="Sources/Reloj/funcion_reloj_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/Reloj/%.d: ../Sources/Reloj/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


