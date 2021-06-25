################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../pwm_module/pca9685.c \
../pwm_module/pwm_module.c 

OBJS += \
./pwm_module/pca9685.o \
./pwm_module/pwm_module.o 

C_DEPS += \
./pwm_module/pca9685.d \
./pwm_module/pwm_module.d 


# Each subdirectory must supply rules for building sources it contributes
pwm_module/%.o: ../pwm_module/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DLV_EX_CONF_INCLUDE_SIMPLE=1 -DLV_CONF_INCLUDE_SIMPLE=1 -DCPU_MIMXRT1021DAG5A -DCPU_MIMXRT1021DAG5A_cm7 -DFSL_SDK_ENABLE_DRIVER_CACHE_CONTROL=1 -D_POSIX_SOURCE -DXIP_BOOT_HEADER_DCD_ENABLE=1 -DDATA_SECTION_IS_CACHEABLE=1 -DSDK_DEBUGCONSOLE=1 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DUSE_RTOS=1 -DPRINTF_ADVANCED_ENABLE=1 -DSERIAL_PORT_TYPE_UART=1 -DFSL_RTOS_FREE_RTOS -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSKIP_SYSCLK_INIT -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\board" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\littlevgl\lvgl\src\lv_core" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\CMSIS_driver" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\evkmimxrt1020\littlevgl_examples\littlevgl_guider" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\generated" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\generated\guider_fonts" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\generated\guider_customer_fonts" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\generated\images" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\littlevgl" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\littlevgl\lvgl" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\littlevgl\lvgl\src" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\custom" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\lcd" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\touchpanel" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\source" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\mdio" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\phy" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\drivers" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\lwip\src\include\lwip\apps" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\lwip\port" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\lwip\src" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\lwip\src\include" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\utilities" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\device" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\component\uart" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\component\serial_manager" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\component\lists" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\xip" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\CMSIS" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\freertos\freertos_kernel\include" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_lwip_mqtt_freertos\pwm_module" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


