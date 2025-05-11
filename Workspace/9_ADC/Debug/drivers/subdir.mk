################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
OBJS += \
./drivers/drv.o \
./drivers/uart.o 

C_DEPS += \
./drivers/drv.d \
./drivers/uart.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/drv.o: /Users/hmustf/Documents/STM32/Workspace/8_GPIO_UART/Src/drivers/drv.c drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -DSTM32F401xE -c -I../Inc -I/Users/hmustf/Documents/STM32/Workspace/Driver_lib/CMSIS/Include -I/Users/hmustf/Documents/STM32/Workspace/Driver_lib/CMSIS/Device/ST/STM32F4xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
drivers/uart.o: /Users/hmustf/Documents/STM32/Workspace/8_GPIO_UART/Src/drivers/uart.c drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -DSTM32F401xE -c -I../Inc -I/Users/hmustf/Documents/STM32/Workspace/Driver_lib/CMSIS/Include -I/Users/hmustf/Documents/STM32/Workspace/Driver_lib/CMSIS/Device/ST/STM32F4xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/drv.cyclo ./drivers/drv.d ./drivers/drv.o ./drivers/drv.su ./drivers/uart.cyclo ./drivers/uart.d ./drivers/uart.o ./drivers/uart.su

.PHONY: clean-drivers

