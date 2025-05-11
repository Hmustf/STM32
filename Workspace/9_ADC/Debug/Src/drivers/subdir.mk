################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/drivers/adc.c \
../Src/drivers/drv.c \
../Src/drivers/gpio.c \
../Src/drivers/uart.c 

OBJS += \
./Src/drivers/adc.o \
./Src/drivers/drv.o \
./Src/drivers/gpio.o \
./Src/drivers/uart.o 

C_DEPS += \
./Src/drivers/adc.d \
./Src/drivers/drv.d \
./Src/drivers/gpio.d \
./Src/drivers/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/drivers/%.o Src/drivers/%.su Src/drivers/%.cyclo: ../Src/drivers/%.c Src/drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -DSTM32F401xE -c -I../Inc -I/Users/hmustf/Documents/STM32/Workspace/Driver_lib/CMSIS/Include -I/Users/hmustf/Documents/STM32/Workspace/Driver_lib/CMSIS/Device/ST/STM32F4xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-drivers

clean-Src-2f-drivers:
	-$(RM) ./Src/drivers/adc.cyclo ./Src/drivers/adc.d ./Src/drivers/adc.o ./Src/drivers/adc.su ./Src/drivers/drv.cyclo ./Src/drivers/drv.d ./Src/drivers/drv.o ./Src/drivers/drv.su ./Src/drivers/gpio.cyclo ./Src/drivers/gpio.d ./Src/drivers/gpio.o ./Src/drivers/gpio.su ./Src/drivers/uart.cyclo ./Src/drivers/uart.d ./Src/drivers/uart.o ./Src/drivers/uart.su

.PHONY: clean-Src-2f-drivers

