################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../littlevgl/lvgl/src/lv_misc/lv_anim.c \
../littlevgl/lvgl/src/lv_misc/lv_area.c \
../littlevgl/lvgl/src/lv_misc/lv_async.c \
../littlevgl/lvgl/src/lv_misc/lv_bidi.c \
../littlevgl/lvgl/src/lv_misc/lv_color.c \
../littlevgl/lvgl/src/lv_misc/lv_debug.c \
../littlevgl/lvgl/src/lv_misc/lv_fs.c \
../littlevgl/lvgl/src/lv_misc/lv_gc.c \
../littlevgl/lvgl/src/lv_misc/lv_ll.c \
../littlevgl/lvgl/src/lv_misc/lv_log.c \
../littlevgl/lvgl/src/lv_misc/lv_math.c \
../littlevgl/lvgl/src/lv_misc/lv_mem.c \
../littlevgl/lvgl/src/lv_misc/lv_printf.c \
../littlevgl/lvgl/src/lv_misc/lv_task.c \
../littlevgl/lvgl/src/lv_misc/lv_templ.c \
../littlevgl/lvgl/src/lv_misc/lv_txt.c \
../littlevgl/lvgl/src/lv_misc/lv_txt_ap.c \
../littlevgl/lvgl/src/lv_misc/lv_utils.c 

OBJS += \
./littlevgl/lvgl/src/lv_misc/lv_anim.o \
./littlevgl/lvgl/src/lv_misc/lv_area.o \
./littlevgl/lvgl/src/lv_misc/lv_async.o \
./littlevgl/lvgl/src/lv_misc/lv_bidi.o \
./littlevgl/lvgl/src/lv_misc/lv_color.o \
./littlevgl/lvgl/src/lv_misc/lv_debug.o \
./littlevgl/lvgl/src/lv_misc/lv_fs.o \
./littlevgl/lvgl/src/lv_misc/lv_gc.o \
./littlevgl/lvgl/src/lv_misc/lv_ll.o \
./littlevgl/lvgl/src/lv_misc/lv_log.o \
./littlevgl/lvgl/src/lv_misc/lv_math.o \
./littlevgl/lvgl/src/lv_misc/lv_mem.o \
./littlevgl/lvgl/src/lv_misc/lv_printf.o \
./littlevgl/lvgl/src/lv_misc/lv_task.o \
./littlevgl/lvgl/src/lv_misc/lv_templ.o \
./littlevgl/lvgl/src/lv_misc/lv_txt.o \
./littlevgl/lvgl/src/lv_misc/lv_txt_ap.o \
./littlevgl/lvgl/src/lv_misc/lv_utils.o 

C_DEPS += \
./littlevgl/lvgl/src/lv_misc/lv_anim.d \
./littlevgl/lvgl/src/lv_misc/lv_area.d \
./littlevgl/lvgl/src/lv_misc/lv_async.d \
./littlevgl/lvgl/src/lv_misc/lv_bidi.d \
./littlevgl/lvgl/src/lv_misc/lv_color.d \
./littlevgl/lvgl/src/lv_misc/lv_debug.d \
./littlevgl/lvgl/src/lv_misc/lv_fs.d \
./littlevgl/lvgl/src/lv_misc/lv_gc.d \
./littlevgl/lvgl/src/lv_misc/lv_ll.d \
./littlevgl/lvgl/src/lv_misc/lv_log.d \
./littlevgl/lvgl/src/lv_misc/lv_math.d \
./littlevgl/lvgl/src/lv_misc/lv_mem.d \
./littlevgl/lvgl/src/lv_misc/lv_printf.d \
./littlevgl/lvgl/src/lv_misc/lv_task.d \
./littlevgl/lvgl/src/lv_misc/lv_templ.d \
./littlevgl/lvgl/src/lv_misc/lv_txt.d \
./littlevgl/lvgl/src/lv_misc/lv_txt_ap.d \
./littlevgl/lvgl/src/lv_misc/lv_utils.d 


# Each subdirectory must supply rules for building sources it contributes
littlevgl/lvgl/src/lv_misc/%.o: ../littlevgl/lvgl/src/lv_misc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DST7789_LCD -DLV_EX_CONF_INCLUDE_SIMPLE=1 -DLV_CONF_INCLUDE_SIMPLE=1 -DCPU_MIMXRT1021DAG5A -DCPU_MIMXRT1021DAG5A_cm7 -DFSL_SDK_ENABLE_DRIVER_CACHE_CONTROL=1 -D_POSIX_SOURCE -DXIP_BOOT_HEADER_DCD_ENABLE=1 -DDATA_SECTION_IS_CACHEABLE=1 -DSDK_DEBUGCONSOLE=1 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DUSE_RTOS=1 -DPRINTF_ADVANCED_ENABLE=1 -DSERIAL_PORT_TYPE_UART=1 -DFSL_RTOS_FREE_RTOS -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSKIP_SYSCLK_INIT -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\board" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\littlevgl\lvgl\src\lv_core" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\CMSIS_driver" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\evkmimxrt1020\littlevgl_examples\littlevgl_guider" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\generated" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\generated\guider_fonts" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\generated\guider_customer_fonts" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\generated\images" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\littlevgl" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\littlevgl\lvgl" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\littlevgl\lvgl\src" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\custom" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\lcd" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\touchpanel" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\source" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\mdio" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\phy" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\drivers" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\lwip\src\include\lwip\apps" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\lwip\port" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\lwip\src" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\lwip\src\include" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\utilities" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\device" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\component\uart" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\component\serial_manager" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\component\lists" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\xip" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\CMSIS" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\freertos\freertos_kernel\include" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\ext_modules" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


