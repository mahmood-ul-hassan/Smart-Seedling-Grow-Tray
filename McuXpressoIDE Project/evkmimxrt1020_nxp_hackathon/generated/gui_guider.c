/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"


void setup_ui(lv_ui *ui){
//	setup_scr_RGB_control(ui);
//	lv_scr_load(ui->RGB_control);
	setup_scr_Home(ui);
	lv_scr_load(ui->Home);
}
