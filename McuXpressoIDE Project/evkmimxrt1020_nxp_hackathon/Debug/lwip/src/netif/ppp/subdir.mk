################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/src/netif/ppp/auth.c \
../lwip/src/netif/ppp/ccp.c \
../lwip/src/netif/ppp/chap-md5.c \
../lwip/src/netif/ppp/chap-new.c \
../lwip/src/netif/ppp/chap_ms.c \
../lwip/src/netif/ppp/demand.c \
../lwip/src/netif/ppp/eap.c \
../lwip/src/netif/ppp/eui64.c \
../lwip/src/netif/ppp/fsm.c \
../lwip/src/netif/ppp/ipcp.c \
../lwip/src/netif/ppp/ipv6cp.c \
../lwip/src/netif/ppp/lcp.c \
../lwip/src/netif/ppp/lwip_ecp.c \
../lwip/src/netif/ppp/magic.c \
../lwip/src/netif/ppp/mppe.c \
../lwip/src/netif/ppp/multilink.c \
../lwip/src/netif/ppp/ppp.c \
../lwip/src/netif/ppp/pppapi.c \
../lwip/src/netif/ppp/pppcrypt.c \
../lwip/src/netif/ppp/pppoe.c \
../lwip/src/netif/ppp/pppol2tp.c \
../lwip/src/netif/ppp/pppos.c \
../lwip/src/netif/ppp/upap.c \
../lwip/src/netif/ppp/utils.c \
../lwip/src/netif/ppp/vj.c 

OBJS += \
./lwip/src/netif/ppp/auth.o \
./lwip/src/netif/ppp/ccp.o \
./lwip/src/netif/ppp/chap-md5.o \
./lwip/src/netif/ppp/chap-new.o \
./lwip/src/netif/ppp/chap_ms.o \
./lwip/src/netif/ppp/demand.o \
./lwip/src/netif/ppp/eap.o \
./lwip/src/netif/ppp/eui64.o \
./lwip/src/netif/ppp/fsm.o \
./lwip/src/netif/ppp/ipcp.o \
./lwip/src/netif/ppp/ipv6cp.o \
./lwip/src/netif/ppp/lcp.o \
./lwip/src/netif/ppp/lwip_ecp.o \
./lwip/src/netif/ppp/magic.o \
./lwip/src/netif/ppp/mppe.o \
./lwip/src/netif/ppp/multilink.o \
./lwip/src/netif/ppp/ppp.o \
./lwip/src/netif/ppp/pppapi.o \
./lwip/src/netif/ppp/pppcrypt.o \
./lwip/src/netif/ppp/pppoe.o \
./lwip/src/netif/ppp/pppol2tp.o \
./lwip/src/netif/ppp/pppos.o \
./lwip/src/netif/ppp/upap.o \
./lwip/src/netif/ppp/utils.o \
./lwip/src/netif/ppp/vj.o 

C_DEPS += \
./lwip/src/netif/ppp/auth.d \
./lwip/src/netif/ppp/ccp.d \
./lwip/src/netif/ppp/chap-md5.d \
./lwip/src/netif/ppp/chap-new.d \
./lwip/src/netif/ppp/chap_ms.d \
./lwip/src/netif/ppp/demand.d \
./lwip/src/netif/ppp/eap.d \
./lwip/src/netif/ppp/eui64.d \
./lwip/src/netif/ppp/fsm.d \
./lwip/src/netif/ppp/ipcp.d \
./lwip/src/netif/ppp/ipv6cp.d \
./lwip/src/netif/ppp/lcp.d \
./lwip/src/netif/ppp/lwip_ecp.d \
./lwip/src/netif/ppp/magic.d \
./lwip/src/netif/ppp/mppe.d \
./lwip/src/netif/ppp/multilink.d \
./lwip/src/netif/ppp/ppp.d \
./lwip/src/netif/ppp/pppapi.d \
./lwip/src/netif/ppp/pppcrypt.d \
./lwip/src/netif/ppp/pppoe.d \
./lwip/src/netif/ppp/pppol2tp.d \
./lwip/src/netif/ppp/pppos.d \
./lwip/src/netif/ppp/upap.d \
./lwip/src/netif/ppp/utils.d \
./lwip/src/netif/ppp/vj.d 


# Each subdirectory must supply rules for building sources it contributes
lwip/src/netif/ppp/%.o: ../lwip/src/netif/ppp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DST7789_LCD -DLV_EX_CONF_INCLUDE_SIMPLE=1 -DLV_CONF_INCLUDE_SIMPLE=1 -DCPU_MIMXRT1021DAG5A -DCPU_MIMXRT1021DAG5A_cm7 -DFSL_SDK_ENABLE_DRIVER_CACHE_CONTROL=1 -D_POSIX_SOURCE -DXIP_BOOT_HEADER_DCD_ENABLE=1 -DDATA_SECTION_IS_CACHEABLE=1 -DSDK_DEBUGCONSOLE=1 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DUSE_RTOS=1 -DPRINTF_ADVANCED_ENABLE=1 -DSERIAL_PORT_TYPE_UART=1 -DFSL_RTOS_FREE_RTOS -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSKIP_SYSCLK_INIT -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\board" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\littlevgl\lvgl\src\lv_core" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\CMSIS_driver" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\evkmimxrt1020\littlevgl_examples\littlevgl_guider" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\generated" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\generated\guider_fonts" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\generated\guider_customer_fonts" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\generated\images" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\littlevgl" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\littlevgl\lvgl" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\littlevgl\lvgl\src" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\custom" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\lcd" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\touchpanel" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\source" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\mdio" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\phy" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\drivers" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\lwip\src\include\lwip\apps" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\lwip\port" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\lwip\src" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\lwip\src\include" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\utilities" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\device" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\component\uart" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\component\serial_manager" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\component\lists" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\xip" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\CMSIS" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\freertos\freertos_kernel\include" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\HASSAN\Documents\MCUXpressoIDE_11.3.1_5262\workspace\evkmimxrt1020_nxp_hackathon\ext_modules" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


