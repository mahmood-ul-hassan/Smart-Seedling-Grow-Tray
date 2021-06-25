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

extern lv_indev_t* encoder_indev; //The input device
static lv_group_t* home_menu_ctrl; //An Object Group

void setup_scr_Home(lv_ui *ui){

    //Create Group for encoder
	home_menu_ctrl = lv_group_create();
    lv_indev_set_group(encoder_indev, home_menu_ctrl);

	//Write codes Home
	ui->Home = lv_obj_create(NULL, NULL);

	//Write codes Home_menu
	ui->Home_menu = lv_dropdown_create(ui->Home, NULL);
	lv_dropdown_set_options(ui->Home_menu, "SENORS MONITORING\nPWM CONTROL\nRGB CONTROL");
	lv_dropdown_set_max_height(ui->Home_menu, 90);

	//Write style LV_DROPDOWN_PART_MAIN for Home_menu
	static lv_style_t style_Home_menu_main;
	lv_style_init(&style_Home_menu_main);

	//Write style state: LV_STATE_DEFAULT for style_Home_menu_main
	lv_style_set_radius(&style_Home_menu_main, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_Home_menu_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xfa, 0xf5));
	lv_style_set_bg_grad_color(&style_Home_menu_main, LV_STATE_DEFAULT, lv_color_make(0xf0, 0xfa, 0xff));
	lv_style_set_bg_grad_dir(&style_Home_menu_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Home_menu_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Home_menu_main, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_Home_menu_main, LV_STATE_DEFAULT, 4);
	lv_style_set_text_color(&style_Home_menu_main, LV_STATE_DEFAULT, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_Home_menu_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_16);
	lv_style_set_text_line_space(&style_Home_menu_main, LV_STATE_DEFAULT, 20);
	lv_obj_add_style(ui->Home_menu, LV_DROPDOWN_PART_MAIN, &style_Home_menu_main);

	//Write style LV_DROPDOWN_PART_SELECTED for Home_menu
	static lv_style_t style_Home_menu_selected;
	lv_style_init(&style_Home_menu_selected);

	//Write style state: LV_STATE_DEFAULT for style_Home_menu_selected
	lv_style_set_radius(&style_Home_menu_selected, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_Home_menu_selected, LV_STATE_DEFAULT, lv_color_make(0xb5, 0xa1, 0x00));
	lv_style_set_bg_grad_color(&style_Home_menu_selected, LV_STATE_DEFAULT, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_dir(&style_Home_menu_selected, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Home_menu_selected, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Home_menu_selected, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_Home_menu_selected, LV_STATE_DEFAULT, 1);
	lv_style_set_text_color(&style_Home_menu_selected, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_Home_menu_selected, LV_STATE_DEFAULT, &lv_font_montserratMedium_16);
	lv_obj_add_style(ui->Home_menu, LV_DROPDOWN_PART_SELECTED, &style_Home_menu_selected);

	//Write style LV_DROPDOWN_PART_LIST for Home_menu
	static lv_style_t style_Home_menu_list;
	lv_style_init(&style_Home_menu_list);

	//Write style state: LV_STATE_DEFAULT for style_Home_menu_list
	lv_style_set_radius(&style_Home_menu_list, LV_STATE_DEFAULT, 3);
	lv_style_set_bg_color(&style_Home_menu_list, LV_STATE_DEFAULT, lv_color_make(0xf5, 0xfa, 0xff));
	lv_style_set_bg_grad_color(&style_Home_menu_list, LV_STATE_DEFAULT, lv_color_make(0xff, 0xfa, 0xf5));
	lv_style_set_bg_grad_dir(&style_Home_menu_list, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Home_menu_list, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Home_menu_list, LV_STATE_DEFAULT, lv_color_make(0xe1, 0xe6, 0xee));
	lv_style_set_border_width(&style_Home_menu_list, LV_STATE_DEFAULT, 1);
	lv_style_set_text_color(&style_Home_menu_list, LV_STATE_DEFAULT, lv_color_make(0x0D, 0x30, 0x55));
	lv_style_set_text_font(&style_Home_menu_list, LV_STATE_DEFAULT, &lv_font_montserratMedium_16);
	lv_obj_add_style(ui->Home_menu, LV_DROPDOWN_PART_LIST, &style_Home_menu_list);
	lv_obj_set_pos(ui->Home_menu, 10, 80);
	lv_obj_set_width(ui->Home_menu, 220);

	//Write codes Home_NXP_logo
	ui->Home_NXP_logo = lv_img_create(ui->Home, NULL);

	//Write style LV_IMG_PART_MAIN for Home_NXP_logo
	static lv_style_t style_Home_NXP_logo_main;
	lv_style_init(&style_Home_NXP_logo_main);

	//Write style state: LV_STATE_DEFAULT for style_Home_NXP_logo_main
	lv_style_set_image_recolor(&style_Home_NXP_logo_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_Home_NXP_logo_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_Home_NXP_logo_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->Home_NXP_logo, LV_IMG_PART_MAIN, &style_Home_NXP_logo_main);
	lv_obj_set_pos(ui->Home_NXP_logo, 0, 160);
	lv_obj_set_size(ui->Home_NXP_logo, 80, 80);
	lv_obj_set_click(ui->Home_NXP_logo, true);
	lv_img_set_src(ui->Home_NXP_logo,&nxp_logo);
	lv_img_set_pivot(ui->Home_NXP_logo, 0,0);
	lv_img_set_angle(ui->Home_NXP_logo, 0);

	//Write codes Home_electromaker_logo
	ui->Home_electromaker_logo = lv_img_create(ui->Home, NULL);

	//Write style LV_IMG_PART_MAIN for Home_electromaker_logo
	static lv_style_t style_Home_electromaker_logo_main;
	lv_style_init(&style_Home_electromaker_logo_main);

	//Write style state: LV_STATE_DEFAULT for style_Home_electromaker_logo_main
	lv_style_set_image_recolor(&style_Home_electromaker_logo_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_Home_electromaker_logo_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_Home_electromaker_logo_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->Home_electromaker_logo, LV_IMG_PART_MAIN, &style_Home_electromaker_logo_main);
	lv_obj_set_pos(ui->Home_electromaker_logo, 80, 160);
	lv_obj_set_size(ui->Home_electromaker_logo, 80, 80);
	lv_obj_set_click(ui->Home_electromaker_logo, true);
	lv_img_set_src(ui->Home_electromaker_logo,&electromaker_logo);
	lv_img_set_pivot(ui->Home_electromaker_logo, 0,0);
	lv_img_set_angle(ui->Home_electromaker_logo, 0);

	//Write codes Home_mouser_logo
	ui->Home_mouser_logo = lv_img_create(ui->Home, NULL);

	//Write style LV_IMG_PART_MAIN for Home_mouser_logo
	static lv_style_t style_Home_mouser_logo_main;
	lv_style_init(&style_Home_mouser_logo_main);

	//Write style state: LV_STATE_DEFAULT for style_Home_mouser_logo_main
	lv_style_set_image_recolor(&style_Home_mouser_logo_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_Home_mouser_logo_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_Home_mouser_logo_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->Home_mouser_logo, LV_IMG_PART_MAIN, &style_Home_mouser_logo_main);
	lv_obj_set_pos(ui->Home_mouser_logo, 160, 160);
	lv_obj_set_size(ui->Home_mouser_logo, 80, 80);
	lv_obj_set_click(ui->Home_mouser_logo, true);
	lv_img_set_src(ui->Home_mouser_logo,&mouser_logo);
	lv_img_set_pivot(ui->Home_mouser_logo, 0,0);
	lv_img_set_angle(ui->Home_mouser_logo, 0);

	//Write codes Home_title
	ui->Home_title = lv_label_create(ui->Home, NULL);
	lv_label_set_text(ui->Home_title, "NXP Hackathon 2021");
	lv_label_set_long_mode(ui->Home_title, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->Home_title, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for Home_title
	static lv_style_t style_Home_title_main;
	lv_style_init(&style_Home_title_main);

	//Write style state: LV_STATE_DEFAULT for style_Home_title_main
	lv_style_set_radius(&style_Home_title_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_Home_title_main, LV_STATE_DEFAULT, lv_color_make(0xb5, 0xa1, 0x00));
	lv_style_set_bg_grad_color(&style_Home_title_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_bg_grad_dir(&style_Home_title_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Home_title_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_Home_title_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_text_font(&style_Home_title_main, LV_STATE_DEFAULT, &lv_font_montserratMedium_22);
	lv_style_set_text_letter_space(&style_Home_title_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_Home_title_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_Home_title_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_Home_title_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_Home_title_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->Home_title, LV_LABEL_PART_MAIN, &style_Home_title_main);
	lv_obj_set_pos(ui->Home_title, 2, 2);
	lv_obj_set_size(ui->Home_title, 236, 0);

	//Init events for screen
	events_init_Home(ui);

	lv_group_add_obj(home_menu_ctrl, ui->Home_menu);
}
