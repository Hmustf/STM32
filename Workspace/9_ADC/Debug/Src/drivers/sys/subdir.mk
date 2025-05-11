################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/drivers/sys/syscalls.c \
../Src/drivers/sys/sysmem.c 

OBJS += \
./Src/drivers/sys/syscalls.o \
./Src/drivers/sys/sysmem.o 

C_DEPS += \
./Src/drivers/sys/syscalls.d \
./Src/drivers/sys/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/drivers/sys/%.o Src/drivers/sys/%.su Src/drivers/sys/%.cyclo: ../Src/drivers/sys/%.c Src/drivers/sys/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -DSTM32F401xE -c -I../Inc -I/Users/hmustf/Documents/STM32/Workspace/Driver_lib/CMSIS/Include -I/Users/hmustf/Documents/STM32/Workspace/Driver_lib/CMSIS/Device/ST/STM32F4xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-drivers-2f-sys

clean-Src-2f-drivers-2f-sys:
	-$(RM) ./Src/drivers/sys/syscalls.cyclo ./Src/drivers/sys/syscalls.d ./Src/drivers/sys/syscalls.o ./Src/drivers/sys/syscalls.su ./Src/drivers/sys/sysmem.cyclo ./Src/drivers/sys/sysmem.d ./Src/drivers/sys/sysmem.o ./Src/drivers/sys/sysmem.su

.PHONY: clean-Src-2f-drivers-2f-sys

