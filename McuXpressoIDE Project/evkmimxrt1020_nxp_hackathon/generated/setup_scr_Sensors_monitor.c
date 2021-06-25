/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"
#include <ext_modules.h>

extern lv_indev_t* encoder_indev; //The input device
static lv_group_t* sensors_monitor; //An Object Group

extern float dht_readings[3];
extern float power_readings[3];
extern float adc_readings[4];
extern float als_reading;
extern uint16_t proximity_reading;

void setup_scr_Sensors_monitor(lv_ui *ui){

    //Create Group for encoder
	sensors_monitor = lv_group_create();
    lv_indev_set_group(encoder_indev, sensors_monitor);

	//Write codes Sensors_monitor
	ui->Sensors_monitor = lv_obj_create(NULL, NULL);

	//Write codes Sensors_monitor_sensors_menu_btn
	ui->Sensors_monitor_sensors_menu_btn = lv_btn_create(ui->Sensors_monitor, NULL);

	//Write style LV_BTN_PART_MAIN for Sensors_monitor_sensors_menu_btn
	static lv_style_t style_Sensors_monitor_sensors_menu_btn_main;
	lv_style_init(&style_Sensors_monitor_sensors_menu_btn_main);

	//Write style state: LV_STATE_DEFAULT for style_Sensors_monitor_sensors_menu_btn_main
	lv_style_set_radius(&style_Sensors_monitor_sensors_menu_btn_main, LV_STATE_DEFAULT, 5);
	lv_style_set_bg_color(&style_Sensors_monitor_sensors_menu_btn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0xa3, 0x00));
	lv_style_set_bg_grad_color(&style_Sensors_monitor_sensors_menu_btn_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x18, 0x00));
	lv_style_set_bg_grad_dir(&style_Sensors_monitor_sensors_menu_btn_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Sensors_monitor_sensors_menu_btn_main, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Sensors_monitor_sensors_menu_btn_main, LV_STATE_DEFAULT, lv_color_make(0x0f, 0x55, 0x0f));
	lv_style_set_border_width(&style_Sensors_monitor_sensors_menu_btn_main, LV_STATE_DEFAULT, 2);
	lv_style_set_border_opa(&style_Sensors_monitor_sensors_menu_btn_main, LV_STATE_DEFAULT, 255);
	lv_style_set_outline_color(&style_Sensors_monitor_sensors_menu_btn_main, LV_STATE_DEFAULT, lv_color_make(0xd9, 0xd9, 0xd9));
	lv_style_set_outline_opa(&style_Sensors_monitor_sensors_menu_btn_main, LV_STATE_DEFAULT, 255);

	//Write style state: LV_STATE_FOCUSED for style_Sensors_monitor_sensors_menu_btn_main
	lv_style_set_radius(&style_Sensors_monitor_sensors_menu_btn_main, LV_STATE_FOCUSED, 5);
	lv_style_set_bg_color(&style_Sensors_monitor_sensors_menu_btn_main, LV_STATE_FOCUSED, lv_color_make(0x00, 0x18, 0x00));
	lv_style_set_bg_grad_color(&style_Sensors_monitor_sensors_menu_btn_main, LV_STATE_FOCUSED, lv_color_make(0x00, 0xa3, 0x00));
	lv_style_set_bg_grad_dir(&style_Sensors_monitor_sensors_menu_btn_main, LV_STATE_FOCUSED, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Sensors_monitor_sensors_menu_btn_main, LV_STATE_FOCUSED, 255);
	lv_style_set_border_color(&style_Sensors_monitor_sensors_menu_btn_main, LV_STATE_FOCUSED, lv_color_make(0xe3, 0xe3, 0xe3));
	lv_style_set_border_width(&style_Sensors_monitor_sensors_menu_btn_main, LV_STATE_FOCUSED, 2);
	lv_style_set_border_opa(&style_Sensors_monitor_sensors_menu_btn_main, LV_STATE_FOCUSED, 255);
	lv_style_set_outline_color(&style_Sensors_monitor_sensors_menu_btn_main, LV_STATE_FOCUSED, lv_color_make(0xe6, 0xe6, 0xe6));
	lv_style_set_outline_opa(&style_Sensors_monitor_sensors_menu_btn_main, LV_STATE_FOCUSED, 255);
	lv_obj_add_style(ui->Sensors_monitor_sensors_menu_btn, LV_BTN_PART_MAIN, &style_Sensors_monitor_sensors_menu_btn_main);
	lv_obj_set_pos(ui->Sensors_monitor_sensors_menu_btn, 2, 2);
	lv_obj_set_size(ui->Sensors_monitor_sensors_menu_btn, 236, 50);
	ui->Sensors_monitor_sensors_menu_btn_label = lv_label_create(ui->Sensors_monitor_sensors_menu_btn, NULL);
	lv_label_set_text(ui->Sensors_monitor_sensors_menu_btn_label, "SENSORS");
	lv_obj_set_style_local_text_color(ui->Sensors_monitor_sensors_menu_btn_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(0xfa, 0xfa, 0xfa));
	lv_obj_set_style_local_text_font(ui->Sensors_monitor_sensors_menu_btn_label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserratMedium_20);

	//Write codes Sensors_monitor_table_1
	ui->Sensors_monitor_table_1 = lv_table_create(ui->Sensors_monitor, NULL);

	//Write style LV_TABLE_PART_BG for Sensors_monitor_table_1
	static lv_style_t style_Sensors_monitor_table_1_bg;
	lv_style_init(&style_Sensors_monitor_table_1_bg);

	//Write style state: LV_STATE_DEFAULT for style_Sensors_monitor_table_1_bg
	lv_style_set_bg_color(&style_Sensors_monitor_table_1_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_Sensors_monitor_table_1_bg, LV_STATE_DEFAULT, lv_color_make(0xd2, 0xdc, 0xd2));
	lv_style_set_bg_grad_dir(&style_Sensors_monitor_table_1_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Sensors_monitor_table_1_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Sensors_monitor_table_1_bg, LV_STATE_DEFAULT, lv_color_make(0xd5, 0xde, 0xe6));
	lv_style_set_border_width(&style_Sensors_monitor_table_1_bg, LV_STATE_DEFAULT, 1);
	lv_style_set_text_color(&style_Sensors_monitor_table_1_bg, LV_STATE_DEFAULT, lv_color_make(0x05, 0x19, 0x05));
	lv_style_set_text_decor(&style_Sensors_monitor_table_1_bg, LV_STATE_DEFAULT, LV_TEXT_DECOR_NONE);
	lv_style_set_pad_left(&style_Sensors_monitor_table_1_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_right(&style_Sensors_monitor_table_1_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_top(&style_Sensors_monitor_table_1_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_bottom(&style_Sensors_monitor_table_1_bg, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(ui->Sensors_monitor_table_1, LV_TABLE_PART_BG, &style_Sensors_monitor_table_1_bg);

	//Write style LV_TABLE_PART_CELL1 for Sensors_monitor_table_1
	static lv_style_t style_Sensors_monitor_table_1_cell1;
	lv_style_init(&style_Sensors_monitor_table_1_cell1);

	//Write style state: LV_STATE_DEFAULT for style_Sensors_monitor_table_1_cell1
	lv_style_set_border_color(&style_Sensors_monitor_table_1_cell1, LV_STATE_DEFAULT, lv_color_make(0x0f, 0x55, 0x0f));
	lv_style_set_border_width(&style_Sensors_monitor_table_1_cell1, LV_STATE_DEFAULT, 1);
	lv_obj_add_style(ui->Sensors_monitor_table_1, LV_TABLE_PART_CELL1, &style_Sensors_monitor_table_1_cell1);
	lv_obj_set_pos(ui->Sensors_monitor_table_1, 15, 62);
	lv_table_set_col_cnt(ui->Sensors_monitor_table_1,2);
	lv_table_set_row_cnt(ui->Sensors_monitor_table_1,5);
	lv_table_set_cell_value(ui->Sensors_monitor_table_1,0,0,"Parameter");
	lv_table_set_cell_value(ui->Sensors_monitor_table_1,1,0,"Temperature");
	lv_table_set_cell_value(ui->Sensors_monitor_table_1,2,0,"Humidity");
	lv_table_set_cell_value(ui->Sensors_monitor_table_1,3,0,"Soil Moisture");
	lv_table_set_cell_value(ui->Sensors_monitor_table_1,4,0,"Heat Index");
	lv_table_set_cell_value(ui->Sensors_monitor_table_1,0,1,"Value (unit)");

	char table_1_val[24]={0};

	memset(table_1_val, 0, sizeof(table_1_val));
	sprintf(table_1_val, "%2.2f C", dht_readings[0]);
	lv_table_set_cell_value(guider_ui.Sensors_monitor_table_1,1,1,table_1_val);

	memset(table_1_val, 0, sizeof(table_1_val));
	sprintf(table_1_val, "%2.2f %%", dht_readings[1]);
	lv_table_set_cell_value(guider_ui.Sensors_monitor_table_1,2,1,table_1_val);

	memset(table_1_val, 0, sizeof(table_1_val));
	sprintf(table_1_val, "%2.1f %%", adc_readings[0]);
	sprintf(table_1_val, "%s | %2.1f %%", table_1_val, adc_readings[1]);
	lv_table_set_cell_value(guider_ui.Sensors_monitor_table_1,3,1,table_1_val);

	memset(table_1_val, 0, sizeof(table_1_val));
	sprintf(table_1_val, "%2.2f C", dht_readings[2]);
	lv_table_set_cell_value(guider_ui.Sensors_monitor_table_1,4,1,table_1_val);

	lv_obj_set_style_local_pad_left(ui->Sensors_monitor_table_1, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 10);
	lv_obj_set_style_local_pad_right(ui->Sensors_monitor_table_1, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 10);
	lv_obj_set_style_local_pad_top(ui->Sensors_monitor_table_1, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 8);
	lv_obj_set_style_local_pad_bottom(ui->Sensors_monitor_table_1, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 8);

	//Write codes Sensors_monitor_table_2
	ui->Sensors_monitor_table_2 = lv_table_create(ui->Sensors_monitor, NULL);

	//Write style LV_TABLE_PART_BG for Sensors_monitor_table_2
	static lv_style_t style_Sensors_monitor_table_2_bg;
	lv_style_init(&style_Sensors_monitor_table_2_bg);

	//Write style state: LV_STATE_DEFAULT for style_Sensors_monitor_table_1_bg
	lv_style_set_bg_color(&style_Sensors_monitor_table_2_bg, LV_STATE_DEFAULT, lv_color_make(0xd2, 0xdc, 0xd2));
	lv_style_set_bg_grad_color(&style_Sensors_monitor_table_2_bg, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_Sensors_monitor_table_2_bg, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_Sensors_monitor_table_2_bg, LV_STATE_DEFAULT, 255);
	lv_style_set_border_color(&style_Sensors_monitor_table_2_bg, LV_STATE_DEFAULT, lv_color_make(0xd5, 0xde, 0xe6));
	lv_style_set_border_width(&style_Sensors_monitor_table_2_bg, LV_STATE_DEFAULT, 1);
	lv_style_set_text_color(&style_Sensors_monitor_table_2_bg, LV_STATE_DEFAULT, lv_color_make(0x05, 0x19, 0x05));
	lv_style_set_text_decor(&style_Sensors_monitor_table_2_bg, LV_STATE_DEFAULT, LV_TEXT_DECOR_NONE);
	lv_style_set_pad_left(&style_Sensors_monitor_table_2_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_right(&style_Sensors_monitor_table_2_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_top(&style_Sensors_monitor_table_2_bg, LV_STATE_DEFAULT, 5);
	lv_style_set_pad_bottom(&style_Sensors_monitor_table_2_bg, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(ui->Sensors_monitor_table_2, LV_TABLE_PART_BG, &style_Sensors_monitor_table_2_bg);

	//Write style LV_TABLE_PART_CELL1 for Sensors_monitor_table_1
	static lv_style_t style_Sensors_monitor_table_2_cell1;
	lv_style_init(&style_Sensors_monitor_table_2_cell1);

	//Write style state: LV_STATE_DEFAULT for style_Sensors_monitor_table_1_cell1
	lv_style_set_border_color(&style_Sensors_monitor_table_2_cell1, LV_STATE_DEFAULT, lv_color_make(0x0f, 0x55, 0x0f));
	lv_style_set_border_width(&style_Sensors_monitor_table_2_cell1, LV_STATE_DEFAULT, 1);
	lv_obj_add_style(ui->Sensors_monitor_table_2, LV_TABLE_PART_CELL1, &style_Sensors_monitor_table_2_cell1);
	lv_obj_set_pos(ui->Sensors_monitor_table_2, 15, 62);
	lv_table_set_col_cnt(ui->Sensors_monitor_table_2,2);
	lv_table_set_row_cnt(ui->Sensors_monitor_table_2,5);
	lv_table_set_cell_value(ui->Sensors_monitor_table_2,0,0,"Parameter");
	lv_table_set_cell_value(ui->Sensors_monitor_table_2,1,0,"Voltage");
	lv_table_set_cell_value(ui->Sensors_monitor_table_2,2,0,"Current");
	lv_table_set_cell_value(ui->Sensors_monitor_table_2,3,0,"Power");
	lv_table_set_cell_value(ui->Sensors_monitor_table_2,4,0,"Light Level");
	lv_table_set_cell_value(ui->Sensors_monitor_table_2,0,1,"Value (unit)");

	char table_2_val[24]={0};

	memset(table_2_val, 0, sizeof(table_2_val));
	sprintf(table_2_val, "%2.2f V", power_readings[0]);
	sprintf(table_2_val, "%s | %2.2f V", table_2_val, adc_readings[2]);
	lv_table_set_cell_value(guider_ui.Sensors_monitor_table_2,1,1,table_2_val);

	memset(table_2_val, 0, sizeof(table_2_val));
	sprintf(table_2_val, "%d mA", (int)power_readings[1]);
	lv_table_set_cell_value(guider_ui.Sensors_monitor_table_2,2,1,table_2_val);

	memset(table_2_val, 0, sizeof(table_2_val));
	sprintf(table_2_val, "%d mW", (int)power_readings[2]);
	lv_table_set_cell_value(guider_ui.Sensors_monitor_table_2,3,1,table_2_val);

	memset(table_2_val, 0, sizeof(table_2_val));
	sprintf(table_2_val, "%d lx", (int)als_reading);
	lv_table_set_cell_value(guider_ui.Sensors_monitor_table_2,4,1,table_2_val);

	lv_obj_set_style_local_pad_left(ui->Sensors_monitor_table_2, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 10);
	lv_obj_set_style_local_pad_right(ui->Sensors_monitor_table_2, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 10);
	lv_obj_set_style_local_pad_top(ui->Sensors_monitor_table_2, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 8);
	lv_obj_set_style_local_pad_bottom(ui->Sensors_monitor_table_2, LV_TABLE_PART_CELL1, LV_STATE_DEFAULT, 8);
	lv_obj_set_hidden(guider_ui.Sensors_monitor_table_2, true);

	//Init events for screen
	events_init_Sensors_monitor(ui);

	lv_group_add_obj(sensors_monitor, ui->Sensors_monitor_sensors_menu_btn);
}
