################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/src/core/altcp.c \
../lwip/src/core/altcp_alloc.c \
../lwip/src/core/altcp_tcp.c \
../lwip/src/core/def.c \
../lwip/src/core/dns.c \
../lwip/src/core/inet_chksum.c \
../lwip/src/core/init.c \
../lwip/src/core/ip.c \
../lwip/src/core/mem.c \
../lwip/src/core/memp.c \
../lwip/src/core/netif.c \
../lwip/src/core/pbuf.c \
../lwip/src/core/raw.c \
../lwip/src/core/stats.c \
../lwip/src/core/sys.c \
../lwip/src/core/tcp.c \
../lwip/src/core/tcp_in.c \
../lwip/src/core/tcp_out.c \
../lwip/src/core/timeouts.c \
../lwip/src/core/udp.c 

OBJS += \
./lwip/src/core/altcp.o \
./lwip/src/core/altcp_alloc.o \
./lwip/src/core/altcp_tcp.o \
./lwip/src/core/def.o \
./lwip/src/core/dns.o \
./lwip/src/core/inet_chksum.o \
./lwip/src/core/init.o \
./lwip/src/core/ip.o \
./lwip/src/core/mem.o \
./lwip/src/core/memp.o \
./lwip/src/core/netif.o \
./lwip/src/core/pbuf.o \
./lwip/src/core/raw.o \
./lwip/src/core/stats.o \
./lwip/src/core/sys.o \
./lwip/src/core/tcp.o \
./lwip/src/core/tcp_in.o \
./lwip/src/core/tcp_out.o \
./lwip/src/core/timeouts.o \
./lwip/src/core/udp.o 

C_DEPS += \
./lwip/src/core/altcp.d \
./lwip/src/core/altcp_alloc.d \
./lwip/src/core/altcp_tcp.d \
./lwip/src/core/def.d \
./lwip/src/core/dns.d \
./lwip/src/core/inet_chksum.d \
./lwip/src/core/init.d \
./lwip/src/core/ip.d \
./lwip/src/core/mem.d \
./lwip/src/core/memp.d \
./lwip/src/core/netif.d \
./lwip/src/core/pbuf.d \
./lwip/src/core/raw.d \
./lwip/src/core/stats.d \
./lwip/src/core/sys.d \
./lwip/src/core/tcp.d \
./lwip/src/core/tcp_in.d \
./lwip/src/core/tcp_out.d \
./lwip/src/core/timeouts.d \
./lwip/src/core/udp.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/src/core/%.o: ../lwip/src/core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DST7789_LCD -DLV_EX_CONF_INCLUDE_SIMPLE=1 -DLV_CONF_INCLUDE_SIMPLE=1 -DCPU_MIMXRT1021DAG5A -DCPU_MIMXRT1021DAG5A_cm7 -DFSL_SDK_ENABLE_DRIVER_CACHE_CONTROL=1 -D_POSIX_SOURCE -DXIP_BOOT_HEADER_DCD_ENABLE=1 -DDATA_SECTION_IS_CACHEABLE=1 -DSDK_DEBUGCONSOLE=1 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DUSE_RTOS=1 -DPRINTF_ADVANCED_ENABLE=1 -DSERIAL_PORT_TYPE_UART=1 -DFSL_RTOS_FREE_RTOS -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSKIP_SYSCLK_INIT -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\board" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\littlevgl\lvgl\src\lv_core" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\CMSIS_driver" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\evkmimxrt1020\littlevgl_examples\littlevgl_guider" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\generated" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\generated\guider_fonts" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\generated\guider_customer_fonts" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\generated\images" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\littlevgl" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\littlevgl\lvgl" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\littlevgl\lvgl\src" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\custom" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\lcd" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\touchpanel" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\source" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\mdio" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\phy" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\drivers" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\lwip\src\include\lwip\apps" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\lwip\port" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\lwip\src" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\lwip\src\include" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\utilities" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\device" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\component\uart" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\component\serial_manager" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\component\lists" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\xip" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\CMSIS" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\freertos\freertos_kernel\include" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\ext_modules" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


