/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include <ext_modules.h>
#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


extern lv_indev_t* encoder_indev; //The input device
static lv_group_t* pca9685_pwm_ctrl; //An Object Group

void setup_scr_PWM_control(lv_ui *ui){

    //Create Group for encoder
    pca9685_pwm_ctrl = lv_group_create();
    lv_indev_set_group(encoder_indev, pca9685_pwm_ctrl);

	//Write codes PWM_control
	ui->PWM_control = lv_obj_create(NULL, NULL);

	//Write codes PWM_control_pwm_val_slider
	ui->PWM_control_pwm_val_slider = lv_slider_create(ui->PWM_control, NULL);

	//Write style LV_SLIDER_PART_INDIC for PWM_control_pwm_val_slider
	static lv_style_t style_PWM_control_pwm_val_slider_indic;
	lv_style_init(&style_PWM_control_pwm_val_slider_indic);

	//Write style state: LV_STATE_DEFAULT for style_PWM_control_pwm_val_slider_indic
	lv_style_set_radius(&style_PWM_control_pwm_val_slider_indic, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_PWM_control_pwm_val_slider_indic, LV_STATE_DEFAULT, lv_color_make(0xb1, 0x02, 0x02));
	lv_style_set_bg_grad_color(&style_PWM_control_pwm_val_slider_indic, LV_STATE_DEFAULT, lv_color_make(0x61, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_PWM_control_pwm_val_slider_indic, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_PWM_control_pwm_val_slider_indic, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->PWM_control_pwm_val_slider, LV_SLIDER_PART_INDIC, &style_PWM_control_pwm_val_slider_indic);

	//Write style LV_SLIDER_PART_BG for PWM_control_pwm_val_slider
	static lv_style_t style_PWM_control_pwm_val_slider_bg;
	lv_style_init(&style_PWM_control_pwm_val_slider_bg);

	//Write style state: LV_STATE_DEFAULT for style_PWM_control_pwm_val_slider_bg
	lv_style_set_radius(&style_PWM_control_pwm_val_slider_bg, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_PWM_control_pwm_val_slider_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_bg_grad_color(&style_PWM_control_pwm_val_slider_bg, LV_STATE_DEFAULT, lv_color_make(0xc2, 0xb2, 0xb2));
	lv_style_set_bg_grad_dir(&style_PWM_control_pwm_val_slider_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_PWM_control_pwm_val_slider_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_PWM_control_pwm_val_slider_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_PWM_control_pwm_val_slider_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_PWM_control_pwm_val_slider_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_PWM_control_pwm_val_slider_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_PWM_control_pwm_val_slider_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_PWM_control_pwm_val_slider_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->PWM_control_pwm_val_slider, LV_SLIDER_PART_BG, &style_PWM_control_pwm_val_slider_bg);

	//Write style state: LV_STATE_FOCUSED for style_PWM_control_pwm_val_slider_bg
	lv_style_set_outline_color(&style_PWM_control_pwm_val_slider_bg, LV_STATE_FOCUSED, lv_color_make(0x00, 0xff, 0x33));
	lv_style_set_outline_width(&style_PWM_control_pwm_val_slider_bg, LV_STATE_FOCUSED, 3);
	lv_style_set_outline_opa(&style_PWM_control_pwm_val_slider_bg, LV_STATE_FOCUSED, 255);
	lv_obj_add_style(ui->PWM_control_pwm_val_slider, LV_SLIDER_PART_BG, &style_PWM_control_pwm_val_slider_bg);

	//Write style LV_SLIDER_PART_KNOB for PWM_control_pwm_val_slider
	static lv_style_t style_PWM_control_pwm_val_slider_knob;
	lv_style_init(&style_PWM_control_pwm_val_slider_knob);

	//Write style state: LV_STATE_DEFAULT for style_PWM_control_pwm_val_slider_knob
	lv_style_set_radius(&style_PWM_control_pwm_val_slider_knob, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_color(&style_PWM_control_pwm_val_slider_knob, LV_STATE_DEFAULT, lv_color_make(0x3d, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_PWM_control_pwm_val_slider_knob, LV_STATE_DEFAULT, lv_color_make(0xb8, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_PWM_control_pwm_val_slider_knob, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_PWM_control_pwm_val_slider_knob, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->PWM_control_pwm_val_slider, LV_SLIDER_PART_KNOB, &style_PWM_control_pwm_val_slider_knob);
	lv_obj_set_pos(ui->PWM_control_pwm_val_slider, 20, 180);
	lv_obj_set_size(ui->PWM_control_pwm_val_slider, 200, 20);
	lv_slider_set_range(ui->PWM_control_pwm_val_slider,0, 100);
	lv_slider_set_value(ui->PWM_control_pwm_val_slider,(pwm_module_getPWM(0)/40.96),false);
/*
	//Write codes PWM_control_pwm_screen_label
	ui->PWM_control_pwm_screen_label = lv_label_create(ui->PWM_control, NULL);
	lv_label_set_text(ui->PWM_control_pwm_screen_label, "PCA9685 PWM CTRL");
	lv_label_set_long_mode(ui->PWM_control_pwm_screen_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->PWM_control_pwm_screen_label, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for PWM_control_pwm_screen_label
	static lv_style_t style_PWM_control_pwm_screen_label_main;
	lv_style_init(&style_PWM_control_pwm_screen_label_main);

	//Write style state: LV_STATE_DEFAULT for style_PWM_control_pwm_screen_label_main
	lv_style_set_radius(&style_PWM_control_pwm_screen_label_main, LV_STATE_DEFAULT, 5);
	lv_style_set_bg_color(&style_PWM_control_pwm_screen_label_main, LV_STATE_DEFAULT, lv_color_make(0xa3, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_PWM_control_pwm_screen_label_main, LV_STATE_DEFAULT, lv_color_make(0x24, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_PWM_control_pwm_screen_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_PWM_control_pwm_screen_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_PWM_control_pwm_screen_label_main, LV_STATE_DEFAULT, lv_color_make(0xfa, 0xfa, 0xfa));
	lv_style_set_text_font(&style_PWM_control_pwm_screen_label_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_22);
	lv_style_set_text_letter_space(&style_PWM_control_pwm_screen_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_PWM_control_pwm_screen_label_main, LV_STATE_DEFAULT, 1);
	lv_style_set_pad_right(&style_PWM_control_pwm_screen_label_main, LV_STATE_DEFAULT, 1);
	lv_style_set_pad_top(&style_PWM_control_pwm_screen_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_bottom(&style_PWM_control_pwm_screen_label_main, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(ui->PWM_control_pwm_screen_label, LV_LABEL_PART_MAIN, &style_PWM_control_pwm_screen_label_main);
	lv_obj_set_pos(ui->PWM_control_pwm_screen_label, 2, 2);
	lv_obj_set_size(ui->PWM_control_pwm_screen_label, 236, 0);
*/
	//Write codes PWM_control_pwm_menu_btn
	ui->PWM_control_pwm_menu_btn = lv_btn_create(ui->PWM_control, NULL);

	//Write style LV_BTN_PART_MAIN for PWM_control_btn_1
	static lv_style_t style_PWM_control_pwm_menu_btn_main;
	lv_style_init(&style_PWM_control_pwm_menu_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_PWM_control_pwm_menu_btn_main
	lv_style_set_radius(&style_PWM_control_pwm_menu_btn_main, LV_STATE_DEFAULT, 5);
	lv_style_set_bg_color(&style_PWM_control_pwm_menu_btn_main, LV_STATE_DEFAULT, lv_color_make(0xa3, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_PWM_control_pwm_menu_btn_main, LV_STATE_DEFAULT, lv_color_make(0x18, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_PWM_control_pwm_menu_btn_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_PWM_control_pwm_menu_btn_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_PWM_control_pwm_menu_btn_main, LV_STATE_DEFAULT, lv_color_make(0x55, 0x0f, 0x0f));
	lv_style_set_border_width(&style_PWM_control_pwm_menu_btn_main, LV_STATE_DEFAULT, 3);
	lv_style_set_border_opa(&style_PWM_control_pwm_menu_btn_main, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_PWM_control_pwm_menu_btn_main, LV_STATE_DEFAULT, lv_color_make(0xd9, 0xd9, 0xd9));
	lv_style_set_outline_opa(&style_PWM_control_pwm_menu_btn_main, LV_STATE_DEFAULT, 255);

	//Write style state: LV_STATE_FOCUSED for style_PWM_control_pwm_menu_btn_main
	lv_style_set_radius(&style_PWM_control_pwm_menu_btn_main, LV_STATE_FOCUSED, 5);
	lv_style_set_bg_color(&style_PWM_control_pwm_menu_btn_main, LV_STATE_FOCUSED, lv_color_make(0x18, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_PWM_control_pwm_menu_btn_main, LV_STATE_FOCUSED, lv_color_make(0xa3, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_PWM_control_pwm_menu_btn_main, LV_STATE_FOCUSED, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_PWM_control_pwm_menu_btn_main, LV_STATE_FOCUSED, 255);
	lv_style_set_border_color(&style_PWM_control_pwm_menu_btn_main, LV_STATE_FOCUSED, lv_color_make(0xe3, 0xe3, 0xe3));
	lv_style_set_border_width(&style_PWM_control_pwm_menu_btn_main, LV_STATE_FOCUSED, 3);
	lv_style_set_border_opa(&style_PWM_control_pwm_menu_btn_main, LV_STATE_FOCUSED, 255);
	lv_style_set_outline_color(&style_PWM_control_pwm_menu_btn_main, LV_STATE_FOCUSED, lv_color_make(0xe6, 0xe6, 0xe6));
	lv_style_set_outline_opa(&style_PWM_control_pwm_menu_btn_main, LV_STATE_FOCUSED, 255);
	lv_obj_add_style(ui->PWM_control_pwm_menu_btn, LV_BTN_PART_MAIN, &style_PWM_control_pwm_menu_btn_main);
	lv_obj_set_pos(ui->PWM_control_pwm_menu_btn, 2, 2);
	lv_obj_set_size(ui->PWM_control_pwm_menu_btn, 236, 50);
	ui->PWM_control_pwm_menu_btn_label = lv_label_create(ui->PWM_control_pwm_menu_btn, NULL);
	lv_label_set_text(ui->PWM_control_pwm_menu_btn_label, "PCA9685 PWM CTRL");
	lv_obj_set_style_local_text_color(ui->PWM_control_pwm_menu_btn_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xfa, 0xfa, 0xfa));
	lv_obj_set_style_local_text_font(ui->PWM_control_pwm_menu_btn_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserratMedium_22);
	lv_obj_set_style_local_text_letter_space(ui->PWM_control_pwm_menu_btn_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 0);

	//Write codes PWM_control_pwm_val_label
	ui->PWM_control_pwm_val_label = lv_label_create(ui->PWM_control, NULL);
	char label_val[5]={0};
	uint16_t widget_value = 0;
	widget_value = pwm_module_getPWM(0)/40.96;
	sprintf(label_val, "%d", widget_value);
	lv_label_set_text(ui->PWM_control_pwm_val_label, label_val);
	lv_label_set_long_mode(ui->PWM_control_pwm_val_label, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->PWM_control_pwm_val_label, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for PWM_control_pwm_val_label
	static lv_style_t style_PWM_control_pwm_val_label_main;
	lv_style_init(&style_PWM_control_pwm_val_label_main);

	//Write style state: LV_STATE_DEFAULT for style_PWM_control_pwm_val_label_main
	lv_style_set_radius(&style_PWM_control_pwm_val_label_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_PWM_control_pwm_val_label_main, LV_STATE_DEFAULT, lv_color_make(0xbe, 0x19, 0x19));
	lv_style_set_bg_grad_color(&style_PWM_control_pwm_val_label_main, LV_STATE_DEFAULT, lv_color_make(0x2b, 0x03, 0x03));
	lv_style_set_bg_grad_dir(&style_PWM_control_pwm_val_label_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_PWM_control_pwm_val_label_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_PWM_control_pwm_val_label_main, LV_STATE_DEFAULT, lv_color_make(0xf2, 0xf2, 0xf2));
	lv_style_set_text_font(&style_PWM_control_pwm_val_label_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_30);
	lv_style_set_text_letter_space(&style_PWM_control_pwm_val_label_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_PWM_control_pwm_val_label_main, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_right(&style_PWM_control_pwm_val_label_main, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_top(&style_PWM_control_pwm_val_label_main, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_bottom(&style_PWM_control_pwm_val_label_main, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(ui->PWM_control_pwm_val_label, LV_LABEL_PART_MAIN, &style_PWM_control_pwm_val_label_main);
	lv_obj_set_pos(ui->PWM_control_pwm_val_label, 70, 120);
	lv_obj_set_size(ui->PWM_control_pwm_val_label, 100, 0);

	//Write codes PWM_control_pwm_ch_sel_ddlist
	ui->PWM_control_pwm_ch_sel_ddlist = lv_dropdown_create(ui->PWM_control, NULL);
	lv_dropdown_set_options(ui->PWM_control_pwm_ch_sel_ddlist, "Grow LED\nRGB-Red\nRGB-Green\nRGB-Blue\nFan 0\nFan 1\nWater Pump\nCH-7\nCH-8\nCH-9\nCH-10\nCH-11\nCH-12\nCH-13\nCH-14\nCH-15");
	lv_dropdown_set_max_height(ui->PWM_control_pwm_ch_sel_ddlist, 90);

	//Write style LV_DROPDOWN_PART_MAIN for PWM_control_pwm_ch_sel_ddlist
	static lv_style_t style_PWM_control_pwm_ch_sel_ddlist_main;
	lv_style_init(&style_PWM_control_pwm_ch_sel_ddlist_main);

	//Write style state: LV_STATE_DEFAULT for style_PWM_control_pwm_ch_sel_ddlist_main
	lv_style_set_radius(&style_PWM_control_pwm_ch_sel_ddlist_main, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_PWM_control_pwm_ch_sel_ddlist_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_PWM_control_pwm_ch_sel_ddlist_main, LV_STATE_DEFAULT, lv_color_make(0xd1, 0xd1, 0xd1));
	lv_style_set_bg_grad_dir(&style_PWM_control_pwm_ch_sel_ddlist_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_PWM_control_pwm_ch_sel_ddlist_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_PWM_control_pwm_ch_sel_ddlist_main, LV_STATE_DEFAULT, lv_color_make(0xf5, 0xf9, 0xff));
	lv_style_set_border_width(&style_PWM_control_pwm_ch_sel_ddlist_main, LV_STATE_DEFAULT, 4);
	lv_style_set_text_color(&style_PWM_control_pwm_ch_sel_ddlist_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_PWM_control_pwm_ch_sel_ddlist_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_24);
	lv_style_set_text_line_space(&style_PWM_control_pwm_ch_sel_ddlist_main, LV_STATE_DEFAULT, 20);
	lv_obj_add_style(ui->PWM_control_pwm_ch_sel_ddlist, LV_DROPDOWN_PART_MAIN, &style_PWM_control_pwm_ch_sel_ddlist_main);

	//Write style LV_DROPDOWN_PART_SELECTED for PWM_control_pwm_ch_sel_ddlist
	static lv_style_t style_PWM_control_pwm_ch_sel_ddlist_selected;
	lv_style_init(&style_PWM_control_pwm_ch_sel_ddlist_selected);

	//Write style state: LV_STATE_DEFAULT for style_PWM_control_pwm_ch_sel_ddlist_selected
	lv_style_set_radius(&style_PWM_control_pwm_ch_sel_ddlist_selected, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_PWM_control_pwm_ch_sel_ddlist_selected, LV_STATE_DEFAULT, lv_color_make(0xb3, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_PWM_control_pwm_ch_sel_ddlist_selected, LV_STATE_DEFAULT, lv_color_make(0x3c, 0x01, 0x01));
	lv_style_set_bg_grad_dir(&style_PWM_control_pwm_ch_sel_ddlist_selected, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_PWM_control_pwm_ch_sel_ddlist_selected, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_PWM_control_pwm_ch_sel_ddlist_selected, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_PWM_control_pwm_ch_sel_ddlist_selected, LV_STATE_DEFAULT, 1);
	lv_style_set_text_color(&style_PWM_control_pwm_ch_sel_ddlist_selected, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_PWM_control_pwm_ch_sel_ddlist_selected, LV_STATE_DEFAULT, &lv_font_montserratMedium_20);
	lv_obj_add_style(ui->PWM_control_pwm_ch_sel_ddlist, LV_DROPDOWN_PART_SELECTED, &style_PWM_control_pwm_ch_sel_ddlist_selected);

	//Write style LV_DROPDOWN_PART_LIST for PWM_control_pwm_ch_sel_ddlist
	static lv_style_t style_PWM_control_pwm_ch_sel_ddlist_list;
	lv_style_init(&style_PWM_control_pwm_ch_sel_ddlist_list);

	//Write style state: LV_STATE_DEFAULT for style_PWM_control_pwm_ch_sel_ddlist_list
	lv_style_set_radius(&style_PWM_control_pwm_ch_sel_ddlist_list, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_PWM_control_pwm_ch_sel_ddlist_list, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_PWM_control_pwm_ch_sel_ddlist_list, LV_STATE_DEFAULT, lv_color_make(0xe6, 0xe6, 0xe6));
	lv_style_set_bg_grad_dir(&style_PWM_control_pwm_ch_sel_ddlist_list, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_PWM_control_pwm_ch_sel_ddlist_list, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_PWM_control_pwm_ch_sel_ddlist_list, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_PWM_control_pwm_ch_sel_ddlist_list, LV_STATE_DEFAULT, 1);
	lv_style_set_text_color(&style_PWM_control_pwm_ch_sel_ddlist_list, LV_STATE_DEFAULT, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_PWM_control_pwm_ch_sel_ddlist_list, LV_STATE_DEFAULT, &lv_font_montserratMedium_20);
	lv_obj_add_style(ui->PWM_control_pwm_ch_sel_ddlist, LV_DROPDOWN_PART_LIST, &style_PWM_control_pwm_ch_sel_ddlist_list);
	lv_obj_set_pos(ui->PWM_control_pwm_ch_sel_ddlist, 30, 65);
	lv_obj_set_width(ui->PWM_control_pwm_ch_sel_ddlist, 180);

	//Init events for screen
	events_init_PWM_control(ui);

    lv_group_add_obj(pca9685_pwm_ctrl, ui->PWM_control_pwm_ch_sel_ddlist);
    lv_group_add_obj(pca9685_pwm_ctrl, ui->PWM_control_pwm_val_slider);
    lv_group_add_obj(pca9685_pwm_ctrl, ui->PWM_control_pwm_menu_btn);
}
