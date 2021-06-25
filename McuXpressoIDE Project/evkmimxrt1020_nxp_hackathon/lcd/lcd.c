/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017,2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <lcd.h>

void LCD_Init(lcd_send_byte_t _writeData, lcd_send_byte_t _writeCommand)
{

////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef ST7789_LCD

    _writeCommand(ST7789_COLMOD);		//	Set color mode
    _writeData(ST7789_COLOR_MODE_16bit);
  	_writeCommand(0xB2);				//	Porch control
	{
		uint8_t data[] = {0x0C, 0x0C, 0x00, 0x33, 0x33};
		for(uint8_t i=0; i< sizeof(data);i++){
			_writeData(data[i]);
		}
//		ST7789_WriteData(data, sizeof(data));
	}
//	ST7789_SetRotation(ST7789_ROTATION);	//	MADCTL (Display Rotation)

	_writeCommand(ST7789_MADCTL);	// MADCTL
	switch (ST7789_ROTATION) {
	case 0:
		_writeData(ST7789_MADCTL_MX | ST7789_MADCTL_MY | ST7789_MADCTL_RGB);
		break;
	case 1:
		_writeData(ST7789_MADCTL_MY | ST7789_MADCTL_MV | ST7789_MADCTL_RGB);
		break;
	case 2:
		_writeData(ST7789_MADCTL_RGB);
		break;
	case 3:
		_writeData(ST7789_MADCTL_MX | ST7789_MADCTL_MV | ST7789_MADCTL_RGB);
		break;
	default:
		break;
	}


	/* Internal LCD Voltage generator settings */
    _writeCommand(0XB7);				//	Gate Control
    _writeData(0x35);			//	Default value
    _writeCommand(0xBB);				//	VCOM setting
    _writeData(0x19);			//	0.725v (default 0.75v for 0x20)
    _writeCommand(0xC0);				//	LCMCTRL
    _writeData (0x2C);			//	Default value
    _writeCommand (0xC2);				//	VDV and VRH command Enable
    _writeData (0x01);			//	Default value
    _writeCommand (0xC3);				//	VRH set
    _writeData (0x12);			//	+-4.45v (defalut +-4.1v for 0x0B)
    _writeCommand (0xC4);				//	VDV set
    _writeData (0x20);			//	Default value
    _writeCommand (0xC6);				//	Frame rate control in normal mode
    _writeData (0x0F);			//	Default value (60HZ)
    _writeCommand (0xD0);				//	Power control
    _writeData (0xA4);			//	Default value
    _writeData (0xA1);			//	Default value
	/**************** Division line ****************/

	_writeCommand(0xE0);
	{
		uint8_t data[] = {0xD0, 0x04, 0x0D, 0x11, 0x13, 0x2B, 0x3F, 0x54, 0x4C, 0x18, 0x0D, 0x0B, 0x1F, 0x23};
		for(uint8_t i=0; i< sizeof(data);i++){
			_writeData(data[i]);
		}
//		ST7789_WriteData(data, sizeof(data));
	}

    _writeCommand(0xE1);
	{
		uint8_t data[] = {0xD0, 0x04, 0x0C, 0x11, 0x13, 0x2C, 0x3F, 0x44, 0x51, 0x2F, 0x1F, 0x1F, 0x20, 0x23};
		for(uint8_t i=0; i< sizeof(data);i++){
			_writeData(data[i]);
		}
//		ST7789_WriteData(data, sizeof(data));
	}
    _writeCommand (ST7789_INVON);		//	Inversion ON
	_writeCommand (ST7789_SLPOUT);	//	Out of sleep mode
  	_writeCommand (ST7789_NORON);		//	Normal Display on
  	_writeCommand (ST7789_DISPON);	//	Main screen turned on

#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef ILI9341_LCD
    SDK_DelayAtLeastUs(ILI9341_RESET_CANCEL_MS * 1000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    _writeCommand(ILI9341_CMD_PWRA);
    _writeData(0x39);
    _writeData(0x2C);
    _writeData(0x00);
    _writeData(0x34);
    _writeData(0x02);
    _writeCommand(ILI9341_CMD_PWRB);
    _writeData(0x00);
    _writeData(0xC1);
    _writeData(0x30);
    _writeCommand(ILI9341_CMD_DTCA);
    _writeData(0x85);
    _writeData(0x00);
    _writeData(0x78);
    _writeCommand(ILI9341_CMD_DTCB);
    _writeData(0x00);
    _writeData(0x00);
    _writeCommand(ILI9341_CMD_PWRSEQ);
    _writeData(0x64);
    _writeData(0x03);
    _writeData(0x12);
    _writeData(0x81);
    _writeCommand(ILI9341_CMD_PRC);
    _writeData(0x20);
    _writeCommand(ILI9341_CMD_PWR1);
    _writeData(0x23);
    _writeCommand(ILI9341_CMD_PWR2);
    _writeData(0x10);
    _writeCommand(ILI9341_CMD_VCOM1);
    _writeData(0x3E);
    _writeData(0x28);
    _writeCommand(ILI9341_CMD_VCOM2);
    _writeData(0x86);
    _writeCommand(ILI9341_CMD_MAC);
    _writeData(0x40);
    _writeCommand(ILI9341_CMD_PIXELFORMAT);
    _writeData(0x55);
    _writeCommand(ILI9341_CMD_FRC);
    _writeData(0x00);
    _writeData(0x18);
    _writeCommand(ILI9341_CMD_DFC);
    _writeData(0x08);
    _writeData(0x82);
    _writeData(0x27);
    _writeCommand(ILI9341_CMD_3GAMMAEN);
    _writeData(0x00);
    _writeCommand(ILI9341_CMD_COLADDR);
    _writeData(0x00);
    _writeData(0x00);
    _writeData(0x00);
    _writeData(0xEF);
    _writeCommand(ILI9341_CMD_PAGEADDR);
    _writeData(0x00);
    _writeData(0x00);
    _writeData(0x01);
    _writeData(0x3F);
    _writeCommand(ILI9341_CMD_GAMMA);
    _writeData(0x01);
    _writeCommand(ILI9341_CMD_PGAMMA);
    _writeData(0x0F);
    _writeData(0x31);
    _writeData(0x2B);
    _writeData(0x0C);
    _writeData(0x0E);
    _writeData(0x08);
    _writeData(0x4E);
    _writeData(0xF1);
    _writeData(0x37);
    _writeData(0x07);
    _writeData(0x10);
    _writeData(0x03);
    _writeData(0x0E);
    _writeData(0x09);
    _writeData(0x00);
    _writeCommand(ILI9341_CMD_NGAMMA);
    _writeData(0x00);
    _writeData(0x0E);
    _writeData(0x14);
    _writeData(0x03);
    _writeData(0x11);
    _writeData(0x07);
    _writeData(0x31);
    _writeData(0xC1);
    _writeData(0x48);
    _writeData(0x08);
    _writeData(0x0F);
    _writeData(0x0C);
    _writeData(0x31);
    _writeData(0x36);
    _writeData(0x0F);
    _writeCommand(ILI9341_CMD_SLEEPOUT);
    _writeCommand(ILI9341_CMD_DISPLAYON);
#endif

}
