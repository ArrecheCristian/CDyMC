################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/MCUinit.c" \
"../Sources/funcion_delay.c" \
"../Sources/funcion_teclado.c" \
"../Sources/lcd.c" \
"../Sources/main.c" \

C_SRCS += \
../Sources/MCUinit.c \
../Sources/funcion_delay.c \
../Sources/funcion_teclado.c \
../Sources/lcd.c \
../Sources/main.c \

OBJS += \
./Sources/MCUinit_c.obj \
./Sources/funcion_delay_c.obj \
./Sources/funcion_teclado_c.obj \
./Sources/lcd_c.obj \
./Sources/main_c.obj \

OBJS_QUOTED += \
"./Sources/MCUinit_c.obj" \
"./Sources/funcion_delay_c.obj" \
"./Sources/funcion_teclado_c.obj" \
"./Sources/lcd_c.obj" \
"./Sources/main_c.obj" \

C_DEPS += \
./Sources/MCUinit_c.d \
./Sources/funcion_delay_c.d \
./Sources/funcion_teclado_c.d \
./Sources/lcd_c.d \
./Sources/main_c.d \

OBJS_OS_FORMAT += \
./Sources/MCUinit_c.obj \
./Sources/funcion_delay_c.obj \
./Sources/funcion_teclado_c.obj \
./Sources/lcd_c.obj \
./Sources/main_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/MCUinit_c.obj: ../Sources/MCUinit.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/MCUinit.args" -ObjN="Sources/MCUinit_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/funcion_delay_c.obj: ../Sources/funcion_delay.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/funcion_delay.args" -ObjN="Sources/funcion_delay_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/funcion_teclado_c.obj: ../Sources/funcion_teclado.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/funcion_teclado.args" -ObjN="Sources/funcion_teclado_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/lcd_c.obj: ../Sources/lcd.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/lcd.args" -ObjN="Sources/lcd_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


