/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include <ext_modules.h>
#include "events_init.h"
#include <stdio.h>
#include <stdlib.h>

#include "lvgl/lvgl.h"


static int16_t curr_pwm_ch = 0;
static uint16_t widget_value = 0;
static char label_val[24];
static float sensor_val = 0.0;
static lv_color_t rgb_val;
static lv_task_t * sensors_value_refresher_task;
static bool sensors_table_status = false;

extern float dht_readings[3];
extern float power_readings[3];
extern float adc_readings[4];
extern float als_reading;
extern uint16_t proximity_reading;
extern uint16_t pwm_readings[16];
extern bool COB_status;

void sensors_value_refresher(lv_task_t * task)
{
	lv_event_send_refresh(guider_ui.Sensors_monitor_sensors_menu_btn);
}

void events_init(lv_ui *ui)
{
}

static void Home_menuevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_CLICKED:
	{
		widget_value = lv_dropdown_get_selected(guider_ui.Home_menu);

		switch (widget_value)
		{
		case 0:
		{
			setup_scr_Sensors_monitor(&guider_ui);
			lv_scr_load_anim(guider_ui.Sensors_monitor, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);
			sensors_value_refresher_task = lv_task_create(sensors_value_refresher, 1000, LV_TASK_PRIO_MID, NULL);
		}
			break;
		case 1:
		{
			setup_scr_PWM_control(&guider_ui);
			lv_scr_load_anim(guider_ui.PWM_control, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);
		}
			break;
		case 2:
		{
			setup_scr_RGB_control(&guider_ui);
			lv_scr_load_anim(guider_ui.RGB_control, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);
		}
			break;
		default:
			break;
		}
	}
		break;
	default:
		break;
	}
}

void events_init_Home(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->Home_menu, Home_menuevent_handler);
}

static void PWM_control_pwm_val_sliderevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_PRESSED:
	{
		widget_value = lv_dropdown_get_selected(guider_ui.PWM_control_pwm_ch_sel_ddlist);
		curr_pwm_ch = widget_value;

		widget_value = lv_slider_get_value(guider_ui.PWM_control_pwm_val_slider);
		pwm_module_setPWM(curr_pwm_ch, (40.96 * widget_value));
	}
		break;
	case LV_EVENT_VALUE_CHANGED:
	{
		widget_value = lv_slider_get_value(guider_ui.PWM_control_pwm_val_slider);
		sprintf(label_val, "%d", widget_value);
		lv_obj_set_style_local_text_font(guider_ui.PWM_control_pwm_val_label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserratMedium_30);
		lv_label_set_text(guider_ui.PWM_control_pwm_val_label, label_val);
	}
		break;
	default:
		break;
	}
}

static void PWM_control_pwm_ch_sel_ddlistevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_PRESSED:
	{
		int i=0;
	}
		break;
	case LV_EVENT_VALUE_CHANGED:
	{
		widget_value = lv_dropdown_get_selected(guider_ui.PWM_control_pwm_ch_sel_ddlist);
		curr_pwm_ch = widget_value;
		widget_value = pwm_module_getPWM(curr_pwm_ch)/40.95;

		sprintf(label_val, "%d", widget_value);
		lv_obj_set_style_local_text_font(guider_ui.PWM_control_pwm_val_label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_montserratMedium_30);
		lv_label_set_text(guider_ui.PWM_control_pwm_val_label, label_val);

		lv_slider_set_value(guider_ui.PWM_control_pwm_val_slider, widget_value, false);
	}
		break;
	default:
		break;
	}
}

static void PWM_control_pwm_menu_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_LONG_PRESSED:
	{
		setup_scr_Home(&guider_ui);
		lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);
	}
		break;
	default:
		break;
	}
}

void events_init_PWM_control(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->PWM_control_pwm_val_slider, PWM_control_pwm_val_sliderevent_handler);
	lv_obj_set_event_cb(ui->PWM_control_pwm_ch_sel_ddlist, PWM_control_pwm_ch_sel_ddlistevent_handler);
	lv_obj_set_event_cb(ui->PWM_control_pwm_menu_btn, PWM_control_pwm_menu_btnevent_handler);
}

static void Sensors_monitor_sensors_menu_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_REFRESH:
	{
		sensor_val = dht_readings[0];
		memset(label_val, 0, sizeof(label_val));
		sprintf(label_val, "%2.2f C", sensor_val);
		lv_table_set_cell_value(guider_ui.Sensors_monitor_table_1,1,1,label_val);

		sensor_val = dht_readings[1];
		memset(label_val, 0, sizeof(label_val));
		sprintf(label_val, "%2.2f %%", sensor_val);
		lv_table_set_cell_value(guider_ui.Sensors_monitor_table_1,2,1,label_val);

		sensor_val = adc_readings[0];
		memset(label_val, 0, sizeof(label_val));
		sprintf(label_val, "%2.1f %%", sensor_val);
		sensor_val = adc_readings[1];
		sprintf(label_val, "%s | %2.1f %%", label_val, sensor_val);
		lv_table_set_cell_value(guider_ui.Sensors_monitor_table_1,3,1,label_val);

		sensor_val = dht_readings[2];
		memset(label_val, 0, sizeof(label_val));
		sprintf(label_val, "%2.2f C", sensor_val);
		lv_table_set_cell_value(guider_ui.Sensors_monitor_table_1,4,1,label_val);

		sensor_val = power_readings[0];
		memset(label_val, 0, sizeof(label_val));
		sprintf(label_val, "%2.2f V", sensor_val);
		sensor_val = adc_readings[2];
		sprintf(label_val, "%s | %2.2f V", label_val, sensor_val);
		lv_table_set_cell_value(guider_ui.Sensors_monitor_table_2,1,1,label_val);

		sensor_val = power_readings[1];
		memset(label_val, 0, sizeof(label_val));
		sprintf(label_val, "%d mA", (int)sensor_val);
		lv_table_set_cell_value(guider_ui.Sensors_monitor_table_2,2,1,label_val);

		sensor_val = power_readings[2];
		memset(label_val, 0, sizeof(label_val));
		sprintf(label_val, "%d mW", (int)sensor_val);
		lv_table_set_cell_value(guider_ui.Sensors_monitor_table_2,3,1,label_val);

		sensor_val = als_reading;
		memset(label_val, 0, sizeof(label_val));
		sprintf(label_val, "%d lx", (int)sensor_val);
		lv_table_set_cell_value(guider_ui.Sensors_monitor_table_2,4,1,label_val);
	}
		break;
	case LV_EVENT_SHORT_CLICKED:
	{
		lv_obj_set_hidden(guider_ui.Sensors_monitor_table_2, sensors_table_status);
		sensors_table_status = !sensors_table_status;
	}
		break;
	case LV_EVENT_LONG_PRESSED:
	{
		setup_scr_Home(&guider_ui);
		lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);

		lv_task_del(sensors_value_refresher_task);
	}
		break;
	default:
		break;
	}
}

void events_init_Sensors_monitor(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->Sensors_monitor_sensors_menu_btn, Sensors_monitor_sensors_menu_btnevent_handler);
}


static void RGB_control_rgb_menu_btnevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_LONG_PRESSED:
	{
		setup_scr_Home(&guider_ui);
		lv_scr_load_anim(guider_ui.Home, LV_SCR_LOAD_ANIM_NONE, 0, 0, true);
	}
		break;
	default:
		break;
	}
}

static void RGB_control_redevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_PRESSED:
	{
	}
		break;
	case LV_EVENT_VALUE_CHANGED:
	{
		widget_value = lv_slider_get_value(guider_ui.RGB_control_red);
		pwm_module_setPWM(1, (40.96 * widget_value));
	}
		break;
	default:
		break;
	}
}

static void RGB_control_greenevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_PRESSED:
	{
	}
		break;
	case LV_EVENT_VALUE_CHANGED:
	{
		widget_value = lv_slider_get_value(guider_ui.RGB_control_green);
		pwm_module_setPWM(2, (40.96 * widget_value));
	}
		break;
	default:
		break;
	}
}

static void RGB_control_blueevent_handler(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_PRESSED:
	{
	}
		break;
	case LV_EVENT_VALUE_CHANGED:
	{
		widget_value = lv_slider_get_value(guider_ui.RGB_control_blue);
		pwm_module_setPWM(3, (40.96 * widget_value));
	}
		break;
	default:
		break;
	}
}

void events_init_RGB_control(lv_ui *ui)
{
	lv_obj_set_event_cb(ui->RGB_control_rgb_menu_btn, RGB_control_rgb_menu_btnevent_handler);
	lv_obj_set_event_cb(ui->RGB_control_red, RGB_control_redevent_handler);
	lv_obj_set_event_cb(ui->RGB_control_green, RGB_control_greenevent_handler);
	lv_obj_set_event_cb(ui->RGB_control_blue, RGB_control_blueevent_handler);
}
