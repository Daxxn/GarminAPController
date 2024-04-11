################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/ButtonManager.cpp \
../Core/Src/EncoderManager.cpp \
../Core/Src/IndicatorManager.cpp \
../Core/Src/MCP4023Driver.cpp \
../Core/Src/MainWrapper.cpp \
../Core/Src/Options.cpp \
../Core/Src/RotaryEncoder.cpp \
../Core/Src/STPLEDDriver.cpp \
../Core/Src/UsbManager.cpp 

C_SRCS += \
../Core/Src/main.c \
../Core/Src/stm32f0xx_hal_msp.c \
../Core/Src/stm32f0xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f0xx.c 

C_DEPS += \
./Core/Src/main.d \
./Core/Src/stm32f0xx_hal_msp.d \
./Core/Src/stm32f0xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f0xx.d 

OBJS += \
./Core/Src/ButtonManager.o \
./Core/Src/EncoderManager.o \
./Core/Src/IndicatorManager.o \
./Core/Src/MCP4023Driver.o \
./Core/Src/MainWrapper.o \
./Core/Src/Options.o \
./Core/Src/RotaryEncoder.o \
./Core/Src/STPLEDDriver.o \
./Core/Src/UsbManager.o \
./Core/Src/main.o \
./Core/Src/stm32f0xx_hal_msp.o \
./Core/Src/stm32f0xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f0xx.o 

CPP_DEPS += \
./Core/Src/ButtonManager.d \
./Core/Src/EncoderManager.d \
./Core/Src/IndicatorManager.d \
./Core/Src/MCP4023Driver.d \
./Core/Src/MainWrapper.d \
./Core/Src/Options.d \
./Core/Src/RotaryEncoder.d \
./Core/Src/STPLEDDriver.d \
./Core/Src/UsbManager.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.cpp Core/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F070xB -DSTP_CHANNEL_COUNT=16 -c -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F070xB -c -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/ButtonManager.cyclo ./Core/Src/ButtonManager.d ./Core/Src/ButtonManager.o ./Core/Src/ButtonManager.su ./Core/Src/EncoderManager.cyclo ./Core/Src/EncoderManager.d ./Core/Src/EncoderManager.o ./Core/Src/EncoderManager.su ./Core/Src/IndicatorManager.cyclo ./Core/Src/IndicatorManager.d ./Core/Src/IndicatorManager.o ./Core/Src/IndicatorManager.su ./Core/Src/MCP4023Driver.cyclo ./Core/Src/MCP4023Driver.d ./Core/Src/MCP4023Driver.o ./Core/Src/MCP4023Driver.su ./Core/Src/MainWrapper.cyclo ./Core/Src/MainWrapper.d ./Core/Src/MainWrapper.o ./Core/Src/MainWrapper.su ./Core/Src/Options.cyclo ./Core/Src/Options.d ./Core/Src/Options.o ./Core/Src/Options.su ./Core/Src/RotaryEncoder.cyclo ./Core/Src/RotaryEncoder.d ./Core/Src/RotaryEncoder.o ./Core/Src/RotaryEncoder.su ./Core/Src/STPLEDDriver.cyclo ./Core/Src/STPLEDDriver.d ./Core/Src/STPLEDDriver.o ./Core/Src/STPLEDDriver.su ./Core/Src/UsbManager.cyclo ./Core/Src/UsbManager.d ./Core/Src/UsbManager.o ./Core/Src/UsbManager.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f0xx_hal_msp.cyclo ./Core/Src/stm32f0xx_hal_msp.d ./Core/Src/stm32f0xx_hal_msp.o ./Core/Src/stm32f0xx_hal_msp.su ./Core/Src/stm32f0xx_it.cyclo ./Core/Src/stm32f0xx_it.d ./Core/Src/stm32f0xx_it.o ./Core/Src/stm32f0xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f0xx.cyclo ./Core/Src/system_stm32f0xx.d ./Core/Src/system_stm32f0xx.o ./Core/Src/system_stm32f0xx.su

.PHONY: clean-Core-2f-Src

