/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *Home;
	lv_obj_t *Home_menu;
	lv_obj_t *Home_title;
	lv_obj_t *Home_NXP_logo;
	lv_obj_t *Home_electromaker_logo;
	lv_obj_t *Home_mouser_logo;
	lv_obj_t *PWM_control;
	lv_obj_t *PWM_control_pwm_val_slider;
//	lv_obj_t *PWM_control_pwm_screen_label;
	lv_obj_t *PWM_control_pwm_val_label;
	lv_obj_t *PWM_control_pwm_ch_sel_ddlist;
	lv_obj_t *PWM_control_pwm_menu_btn;
	lv_obj_t *PWM_control_pwm_menu_btn_label;
	lv_obj_t *Sensors_monitor;
	lv_obj_t *Sensors_monitor_sensors_menu_btn;
	lv_obj_t *Sensors_monitor_sensors_menu_btn_label;
	lv_obj_t *Sensors_monitor_table_1;
	lv_obj_t *Sensors_monitor_table_2;
	lv_obj_t *RGB_control;
	lv_obj_t *RGB_control_rgb_menu_btn;
	lv_obj_t *RGB_control_rgb_menu_btn_label;
	lv_obj_t *RGB_control_red;
	lv_obj_t *RGB_control_green;
	lv_obj_t *RGB_control_blue;
}lv_ui;

void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_Home(lv_ui *ui);
void setup_scr_PWM_control(lv_ui *ui);
void setup_scr_RGB_control(lv_ui *ui);
void setup_scr_Sensors_monitor(lv_ui *ui);
LV_IMG_DECLARE(nxp_logo);
LV_IMG_DECLARE(electromaker_logo);
LV_IMG_DECLARE(mouser_logo);

#ifdef __cplusplus
}
#endif
#endif
