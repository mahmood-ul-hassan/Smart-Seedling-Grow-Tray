################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include xip/subdir.mk
-include utilities/subdir.mk
-include touchpanel/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include phy/subdir.mk
-include mdio/subdir.mk
-include lwip/src/netif/ppp/subdir.mk
-include lwip/src/netif/subdir.mk
-include lwip/src/core/ipv6/subdir.mk
-include lwip/src/core/ipv4/subdir.mk
-include lwip/src/core/subdir.mk
-include lwip/src/apps/mqtt/subdir.mk
-include lwip/src/api/subdir.mk
-include lwip/port/subdir.mk
-include littlevgl/lvgl/src/lv_widgets/subdir.mk
-include littlevgl/lvgl/src/lv_themes/subdir.mk
-include littlevgl/lvgl/src/lv_misc/subdir.mk
-include littlevgl/lvgl/src/lv_hal/subdir.mk
-include littlevgl/lvgl/src/lv_gpu/subdir.mk
-include littlevgl/lvgl/src/lv_font/subdir.mk
-include littlevgl/lvgl/src/lv_draw/subdir.mk
-include littlevgl/lvgl/src/lv_core/subdir.mk
-include littlevgl/lvgl/examples/porting/subdir.mk
-include lcd/subdir.mk
-include generated/images/subdir.mk
-include generated/guider_fonts/subdir.mk
-include generated/subdir.mk
-include freertos/freertos_kernel/portable/MemMang/subdir.mk
-include freertos/freertos_kernel/portable/GCC/ARM_CM4F/subdir.mk
-include freertos/freertos_kernel/subdir.mk
-include ext_modules/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include custom/subdir.mk
-include component/uart/subdir.mk
-include component/serial_manager/subdir.mk
-include component/lists/subdir.mk
-include board/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: evkmimxrt1020_nxp_hackathon.axf

# Tool invocations
evkmimxrt1020_nxp_hackathon.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="evkmimxrt1020_nxp_hackathon.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -T evkmimxrt1020_lwip_mqtt_freertos_Debug.ld -o "evkmimxrt1020_nxp_hackathon.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) evkmimxrt1020_nxp_hackathon.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "evkmimxrt1020_nxp_hackathon.axf" ; arm-none-eabi-objcopy -v -O binary "evkmimxrt1020_nxp_hackathon.axf" "evkmimxrt1020_nxp_hackathon.bin" ; # checksum -p MIMXRT1021xxxxx -d "evkmimxrt1020_nxp_hackathon.bin"
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
