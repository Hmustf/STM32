################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/brd.c \
../Src/drv.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/uti.c 

OBJS += \
./Src/brd.o \
./Src/drv.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/uti.o 

C_DEPS += \
./Src/brd.d \
./Src/drv.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/uti.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/brd.cyclo ./Src/brd.d ./Src/brd.o ./Src/brd.su ./Src/drv.cyclo ./Src/drv.d ./Src/drv.o ./Src/drv.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/uti.cyclo ./Src/uti.d ./Src/uti.o ./Src/uti.su

.PHONY: clean-Src

