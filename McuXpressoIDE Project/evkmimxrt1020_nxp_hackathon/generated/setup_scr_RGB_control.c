/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include <ext_modules.h>

static uint16_t color_value = 0;

extern lv_indev_t* encoder_indev; //The input device
static lv_group_t* rgb_color_ctrl; //An Object Group

void setup_scr_RGB_control(lv_ui *ui){

    //Create Group for encoder
	rgb_color_ctrl = lv_group_create();
    lv_indev_set_group(encoder_indev, rgb_color_ctrl);

	//Write codes RGB_control
	ui->RGB_control = lv_obj_create(NULL, NULL);

	//Write codes RGB_control_rgb_menu_btn
	ui->RGB_control_rgb_menu_btn = lv_btn_create(ui->RGB_control, NULL);

	//Write style LV_BTN_PART_MAIN for RGB_control_rgb_menu_btn
	static lv_style_t style_RGB_control_rgb_menu_btn_main;
	lv_style_init(&style_RGB_control_rgb_menu_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_RGB_control_rgb_menu_btn_main
	lv_style_set_radius(&style_RGB_control_rgb_menu_btn_main, LV_STATE_DEFAULT, 5);
	lv_style_set_bg_color(&style_RGB_control_rgb_menu_btn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0xa3));
	lv_style_set_bg_grad_color(&style_RGB_control_rgb_menu_btn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x18));
	lv_style_set_bg_grad_dir(&style_RGB_control_rgb_menu_btn_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_RGB_control_rgb_menu_btn_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_RGB_control_rgb_menu_btn_main, LV_STATE_DEFAULT, lv_color_make(0x0f, 0x0f, 0x55));
	lv_style_set_border_width(&style_RGB_control_rgb_menu_btn_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_RGB_control_rgb_menu_btn_main, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_RGB_control_rgb_menu_btn_main, LV_STATE_DEFAULT, lv_color_make(0xd7, 0xd7, 0xd7));
	lv_style_set_outline_opa(&style_RGB_control_rgb_menu_btn_main, LV_STATE_DEFAULT, 255);

	//Write style state: LV_STATE_FOCUSED for style_RGB_control_rgb_menu_btn_main
	lv_style_set_radius(&style_RGB_control_rgb_menu_btn_main, LV_STATE_FOCUSED, 5);
	lv_style_set_bg_color(&style_RGB_control_rgb_menu_btn_main, LV_STATE_FOCUSED, lv_color_make(0x00, 0x00, 0x18));
	lv_style_set_bg_grad_color(&style_RGB_control_rgb_menu_btn_main, LV_STATE_FOCUSED, lv_color_make(0x00, 0x00, 0xa3));
	lv_style_set_bg_grad_dir(&style_RGB_control_rgb_menu_btn_main, LV_STATE_FOCUSED, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_RGB_control_rgb_menu_btn_main, LV_STATE_FOCUSED, 255);
	lv_style_set_border_color(&style_RGB_control_rgb_menu_btn_main, LV_STATE_FOCUSED, lv_color_make(0xe3, 0xe3, 0xe3));
	lv_style_set_border_width(&style_RGB_control_rgb_menu_btn_main, LV_STATE_FOCUSED, 2);
	lv_style_set_border_opa(&style_RGB_control_rgb_menu_btn_main, LV_STATE_FOCUSED, 255);
	lv_style_set_outline_color(&style_RGB_control_rgb_menu_btn_main, LV_STATE_FOCUSED, lv_color_make(0xe6, 0xe6, 0xe6));
	lv_style_set_outline_opa(&style_RGB_control_rgb_menu_btn_main, LV_STATE_FOCUSED, 255);
	lv_obj_add_style(ui->RGB_control_rgb_menu_btn, LV_BTN_PART_MAIN, &style_RGB_control_rgb_menu_btn_main);
	lv_obj_set_pos(ui->RGB_control_rgb_menu_btn, 2, 2);
	lv_obj_set_size(ui->RGB_control_rgb_menu_btn, 236, 50);
	ui->RGB_control_rgb_menu_btn_label = lv_label_create(ui->RGB_control_rgb_menu_btn, NULL);
	lv_label_set_text(ui->RGB_control_rgb_menu_btn_label, "RGB COLOR CONTRL");
	lv_obj_set_style_local_text_color(ui->RGB_control_rgb_menu_btn_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xfa, 0xfa, 0xfa));
	lv_obj_set_style_local_text_font(ui->RGB_control_rgb_menu_btn_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserratMedium_20);

	//Write codes RGB_control_red
	ui->RGB_control_red = lv_slider_create(ui->RGB_control, NULL);

	//Write style LV_SLIDER_PART_INDIC for RGB_control_red
	static lv_style_t style_RGB_control_red_indic;
	lv_style_init(&style_RGB_control_red_indic);

	//Write style state: LV_STATE_DEFAULT for style_RGB_control_red_indic
	lv_style_set_radius(&style_RGB_control_red_indic, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_RGB_control_red_indic, LV_STATE_DEFAULT, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_RGB_control_red_indic, LV_STATE_DEFAULT, lv_color_make(0xc8, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_RGB_control_red_indic, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_RGB_control_red_indic, LV_STATE_DEFAULT, 255);

	//Write style state: LV_STATE_FOCUSED for style_RGB_control_red_indic
	lv_style_set_radius(&style_RGB_control_red_indic, LV_STATE_FOCUSED, 50);
	lv_style_set_bg_color(&style_RGB_control_red_indic, LV_STATE_FOCUSED, lv_color_make(0xb8, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_RGB_control_red_indic, LV_STATE_FOCUSED, lv_color_make(0x3d, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_RGB_control_red_indic, LV_STATE_FOCUSED, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_RGB_control_red_indic, LV_STATE_FOCUSED, 255);
	lv_obj_add_style(ui->RGB_control_red, LV_SLIDER_PART_INDIC, &style_RGB_control_red_indic);

	//Write style LV_SLIDER_PART_BG for RGB_control_red
	static lv_style_t style_RGB_control_red_bg;
	lv_style_init(&style_RGB_control_red_bg);

	//Write style state: LV_STATE_DEFAULT for style_RGB_control_red_bg
	lv_style_set_radius(&style_RGB_control_red_bg, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_RGB_control_red_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_bg_grad_color(&style_RGB_control_red_bg, LV_STATE_DEFAULT, lv_color_make(0xc2, 0xb2, 0xb2));
	lv_style_set_bg_grad_dir(&style_RGB_control_red_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_RGB_control_red_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_RGB_control_red_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_RGB_control_red_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_RGB_control_red_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_RGB_control_red_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_RGB_control_red_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_RGB_control_red_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->RGB_control_red, LV_SLIDER_PART_BG, &style_RGB_control_red_bg);

	//Write style LV_SLIDER_PART_KNOB for RGB_control_red
	static lv_style_t style_RGB_control_red_knob;
	lv_style_init(&style_RGB_control_red_knob);

	//Write style state: LV_STATE_DEFAULT for style_RGB_control_red_knob
	lv_style_set_radius(&style_RGB_control_red_knob, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_color(&style_RGB_control_red_knob, LV_STATE_DEFAULT, lv_color_make(0xc8, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_RGB_control_red_knob, LV_STATE_DEFAULT, lv_color_make(0xff, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_RGB_control_red_knob, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_RGB_control_red_knob, LV_STATE_DEFAULT, 255);

	//Write style state: LV_STATE_FOCUSED for style_RGB_control_red_knob
	lv_style_set_radius(&style_RGB_control_red_knob, LV_STATE_FOCUSED, 5);
	lv_style_set_bg_color(&style_RGB_control_red_knob, LV_STATE_FOCUSED, lv_color_make(0x3d, 0x00, 0x00));
	lv_style_set_bg_grad_color(&style_RGB_control_red_knob, LV_STATE_FOCUSED, lv_color_make(0xb8, 0x00, 0x00));
	lv_style_set_bg_grad_dir(&style_RGB_control_red_knob, LV_STATE_FOCUSED, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_RGB_control_red_knob, LV_STATE_FOCUSED, 255);
	lv_obj_add_style(ui->RGB_control_red, LV_SLIDER_PART_KNOB, &style_RGB_control_red_knob);
	lv_obj_set_pos(ui->RGB_control_red, 20, 80);
	lv_obj_set_size(ui->RGB_control_red, 200, 20);
	lv_slider_set_range(ui->RGB_control_red,0, 100);

	color_value = pwm_module_getPWM(1)/40.96;

	lv_slider_set_value(ui->RGB_control_red,color_value,false);

	//Write codes RGB_control_green
	ui->RGB_control_green = lv_slider_create(ui->RGB_control, NULL);

	//Write style LV_SLIDER_PART_INDIC for RGB_control_green
	static lv_style_t style_RGB_control_green_indic;
	lv_style_init(&style_RGB_control_green_indic);

	//Write style state: LV_STATE_DEFAULT for style_RGB_control_green_indic
	lv_style_set_radius(&style_RGB_control_green_indic, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_RGB_control_green_indic, LV_STATE_DEFAULT, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_grad_color(&style_RGB_control_green_indic, LV_STATE_DEFAULT, lv_color_make(0x00, 0xc8, 0x00));
	lv_style_set_bg_grad_dir(&style_RGB_control_green_indic, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_RGB_control_green_indic, LV_STATE_DEFAULT, 255);

	//Write style state: LV_STATE_FOCUSED for style_RGB_control_green_indic
	lv_style_set_radius(&style_RGB_control_green_indic, LV_STATE_FOCUSED, 50);
	lv_style_set_bg_color(&style_RGB_control_green_indic, LV_STATE_FOCUSED, lv_color_make(0x00, 0xb8, 0x00));
	lv_style_set_bg_grad_color(&style_RGB_control_green_indic, LV_STATE_FOCUSED, lv_color_make(0x00, 0x3d, 0x00));
	lv_style_set_bg_grad_dir(&style_RGB_control_green_indic, LV_STATE_FOCUSED, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_RGB_control_green_indic, LV_STATE_FOCUSED, 255);
	lv_obj_add_style(ui->RGB_control_green, LV_SLIDER_PART_INDIC, &style_RGB_control_green_indic);

	//Write style LV_SLIDER_PART_BG for RGB_control_green
	static lv_style_t style_RGB_control_green_bg;
	lv_style_init(&style_RGB_control_green_bg);

	//Write style state: LV_STATE_DEFAULT for style_RGB_control_green_bg
	lv_style_set_radius(&style_RGB_control_green_bg, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_RGB_control_green_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_bg_grad_color(&style_RGB_control_green_bg, LV_STATE_DEFAULT, lv_color_make(0xb2, 0xc2, 0xb2));
	lv_style_set_bg_grad_dir(&style_RGB_control_green_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_RGB_control_green_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_RGB_control_green_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_RGB_control_green_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_RGB_control_green_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_RGB_control_green_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_RGB_control_green_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_RGB_control_green_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->RGB_control_green, LV_SLIDER_PART_BG, &style_RGB_control_green_bg);

	//Write style LV_SLIDER_PART_KNOB for RGB_control_green
	static lv_style_t style_RGB_control_green_knob;
	lv_style_init(&style_RGB_control_green_knob);

	//Write style state: LV_STATE_DEFAULT for style_RGB_control_green_knob
	lv_style_set_radius(&style_RGB_control_green_knob, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_color(&style_RGB_control_green_knob, LV_STATE_DEFAULT, lv_color_make(0x00, 0xc8, 0x00));
	lv_style_set_bg_grad_color(&style_RGB_control_green_knob, LV_STATE_DEFAULT, lv_color_make(0x00, 0xff, 0x00));
	lv_style_set_bg_grad_dir(&style_RGB_control_green_knob, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_RGB_control_green_knob, LV_STATE_DEFAULT, 255);

	//Write style state: LV_STATE_FOCUSED for style_RGB_control_green_knob
	lv_style_set_radius(&style_RGB_control_green_knob, LV_STATE_FOCUSED, 5);
	lv_style_set_bg_color(&style_RGB_control_green_knob, LV_STATE_FOCUSED, lv_color_make(0x00, 0x3d, 0x00));
	lv_style_set_bg_grad_color(&style_RGB_control_green_knob, LV_STATE_FOCUSED, lv_color_make(0x00, 0xb8, 0x00));
	lv_style_set_bg_grad_dir(&style_RGB_control_green_knob, LV_STATE_FOCUSED, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_RGB_control_green_knob, LV_STATE_FOCUSED, 255);
	lv_obj_add_style(ui->RGB_control_green, LV_SLIDER_PART_KNOB, &style_RGB_control_green_knob);
	lv_obj_set_pos(ui->RGB_control_green, 20, 140);
	lv_obj_set_size(ui->RGB_control_green, 200, 20);
	lv_slider_set_range(ui->RGB_control_green,0, 100);

	color_value = pwm_module_getPWM(2)/40.96;

	lv_slider_set_value(ui->RGB_control_green,color_value,false);

	//Write codes RGB_control_blue
	ui->RGB_control_blue = lv_slider_create(ui->RGB_control, NULL);

	//Write style LV_SLIDER_PART_INDIC for RGB_control_blue
	static lv_style_t style_RGB_control_blue_indic;
	lv_style_init(&style_RGB_control_blue_indic);

	//Write style state: LV_STATE_DEFAULT for style_RGB_control_blue_indic
	lv_style_set_radius(&style_RGB_control_blue_indic, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_RGB_control_blue_indic, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0xff));
	lv_style_set_bg_grad_color(&style_RGB_control_blue_indic, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0xc8));
	lv_style_set_bg_grad_dir(&style_RGB_control_blue_indic, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_RGB_control_blue_indic, LV_STATE_DEFAULT, 255);

	//Write style state: LV_STATE_FOCUSED for style_RGB_control_blue_indic
	lv_style_set_radius(&style_RGB_control_blue_indic, LV_STATE_FOCUSED, 50);
	lv_style_set_bg_color(&style_RGB_control_blue_indic, LV_STATE_FOCUSED, lv_color_make(0x00, 0x00, 0xb8));
	lv_style_set_bg_grad_color(&style_RGB_control_blue_indic, LV_STATE_FOCUSED, lv_color_make(0x00, 0x00, 0x3d));
	lv_style_set_bg_grad_dir(&style_RGB_control_blue_indic, LV_STATE_FOCUSED, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_RGB_control_blue_indic, LV_STATE_FOCUSED, 255);
	lv_obj_add_style(ui->RGB_control_blue, LV_SLIDER_PART_INDIC, &style_RGB_control_blue_indic);

	//Write style LV_SLIDER_PART_BG for RGB_control_blue
	static lv_style_t style_RGB_control_blue_bg;
	lv_style_init(&style_RGB_control_blue_bg);

	//Write style state: LV_STATE_DEFAULT for style_RGB_control_blue_bg
	lv_style_set_radius(&style_RGB_control_blue_bg, LV_STATE_DEFAULT, 50);
	lv_style_set_bg_color(&style_RGB_control_blue_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_bg_grad_color(&style_RGB_control_blue_bg, LV_STATE_DEFAULT, lv_color_make(0xb2, 0xb2, 0xc2));
	lv_style_set_bg_grad_dir(&style_RGB_control_blue_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_RGB_control_blue_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_RGB_control_blue_bg, LV_STATE_DEFAULT, lv_color_make(0xd4, 0xd7, 0xd9));
	lv_style_set_outline_opa(&style_RGB_control_blue_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_left(&style_RGB_control_blue_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_RGB_control_blue_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_RGB_control_blue_bg, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_RGB_control_blue_bg, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->RGB_control_blue, LV_SLIDER_PART_BG, &style_RGB_control_blue_bg);

	//Write style LV_SLIDER_PART_KNOB for RGB_control_blue
	static lv_style_t style_RGB_control_blue_knob;
	lv_style_init(&style_RGB_control_blue_knob);

	//Write style state: LV_STATE_DEFAULT for style_RGB_control_blue_knob
	lv_style_set_radius(&style_RGB_control_blue_knob, LV_STATE_DEFAULT, 10);
	lv_style_set_bg_color(&style_RGB_control_blue_knob, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0xc8));
	lv_style_set_bg_grad_color(&style_RGB_control_blue_knob, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0xff));
	lv_style_set_bg_grad_dir(&style_RGB_control_blue_knob, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_RGB_control_blue_knob, LV_STATE_DEFAULT, 255);

	//Write style state: LV_STATE_FOCUSED for style_RGB_control_blue_knob
	lv_style_set_radius(&style_RGB_control_blue_knob, LV_STATE_FOCUSED, 5);
	lv_style_set_bg_color(&style_RGB_control_blue_knob, LV_STATE_FOCUSED, lv_color_make(0x00, 0x00, 0x3d));
	lv_style_set_bg_grad_color(&style_RGB_control_blue_knob, LV_STATE_FOCUSED, lv_color_make(0x00, 0x00, 0xb8));
	lv_style_set_bg_grad_dir(&style_RGB_control_blue_knob, LV_STATE_FOCUSED, LV_GRAD_DIR_HOR);
	lv_style_set_bg_opa(&style_RGB_control_blue_knob, LV_STATE_FOCUSED, 255);
	lv_obj_add_style(ui->RGB_control_blue, LV_SLIDER_PART_KNOB, &style_RGB_control_blue_knob);
	lv_obj_set_pos(ui->RGB_control_blue, 20, 200);
	lv_obj_set_size(ui->RGB_control_blue, 200, 20);
	lv_slider_set_range(ui->RGB_control_blue,0, 100);

	color_value = pwm_module_getPWM(3)/40.96;

	lv_slider_set_value(ui->RGB_control_blue,color_value,false);

	//Init events for screen
	events_init_RGB_control(ui);

	lv_group_add_obj(rgb_color_ctrl, ui->RGB_control_rgb_menu_btn);
	lv_group_add_obj(rgb_color_ctrl, ui->RGB_control_red);
	lv_group_add_obj(rgb_color_ctrl, ui->RGB_control_green);
	lv_group_add_obj(rgb_color_ctrl, ui->RGB_control_blue);
}
