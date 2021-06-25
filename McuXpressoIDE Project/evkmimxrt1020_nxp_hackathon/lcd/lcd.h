/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_ILI9341_H_
#define _FSL_ILI9341_H_

#include "fsl_common.h"

/*
 * Change log:
 *
 *   1.0.1
 *     - Fix MISRA 2012 issues.
 *
 *   1.0.0
 *     - Initial version
 */

/*!
 * @addtogroup ili9341
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifdef ILI9341_LCD
/* Register defines */
#define ILI9341_CMD_RST          0x01
#define ILI9341_CMD_SLEEPOUT     0x11
#define ILI9341_CMD_GAMMA        0x26
#define ILI9341_CMD_DISPLAYOFF   0x28
#define ILI9341_CMD_DISPLAYON    0x29
#define ILI9341_CMD_COLADDR      0x2A
#define ILI9341_CMD_PAGEADDR     0x2B
#define ILI9341_CMD_GRAM         0x2C
#define ILI9341_CMD_MAC          0x36
#define ILI9341_CMD_PIXELFORMAT  0x3A
#define ILI9341_CMD_WDB          0x51
#define ILI9341_CMD_WCD          0x53
#define ILI9341_CMD_RGBINTERFACE 0xB0
#define ILI9341_CMD_FRC          0xB1
#define ILI9341_CMD_BPC          0xB5
#define ILI9341_CMD_DFC          0xB6
#define ILI9341_CMD_PWR1         0xC0
#define ILI9341_CMD_PWR2         0xC1
#define ILI9341_CMD_VCOM1        0xC5
#define ILI9341_CMD_VCOM2        0xC7
#define ILI9341_CMD_PWRA         0xCB
#define ILI9341_CMD_PWRB         0xCF
#define ILI9341_CMD_PGAMMA       0xE0
#define ILI9341_CMD_NGAMMA       0xE1
#define ILI9341_CMD_DTCA         0xE8
#define ILI9341_CMD_DTCB         0xEA
#define ILI9341_CMD_PWRSEQ       0xED
#define ILI9341_CMD_3GAMMAEN     0xF2
#define ILI9341_CMD_INTERFACE    0xF6
#define ILI9341_CMD_PRC          0xF7
#define ILI9341_CMD_INVON        0x21
#define ILI9341_CMD_INVOFF       0x20
#endif
/**************************************************************************************/
#ifdef ST7789_LCD
/* Choose a type you are using */
//#define USING_135X240
#define USING_240X240


/* Choose a display rotation you want to use: (0-3) */
//#define ST7789_ROTATION 0
//#define ST7789_ROTATION 1
#define ST7789_ROTATION 2				//  use Normally on 240x240
//#define ST7789_ROTATION 3

#ifdef USING_135X240

    #if ST7789_ROTATION == 0
        #define ST7789_WIDTH 135
        #define ST7789_HEIGHT 240
        #define X_SHIFT 53
        #define Y_SHIFT 40
    #endif

    #if ST7789_ROTATION == 1
        #define ST7789_WIDTH 240
        #define ST7789_HEIGHT 135
        #define X_SHIFT 40
        #define Y_SHIFT 52
    #endif

    #if ST7789_ROTATION == 2
        #define ST7789_WIDTH 135
        #define ST7789_HEIGHT 240
        #define X_SHIFT 52
        #define Y_SHIFT 40
    #endif

    #if ST7789_ROTATION == 3
        #define ST7789_WIDTH 240
        #define ST7789_HEIGHT 135
        #define X_SHIFT 40
        #define Y_SHIFT 53
    #endif

#endif

#ifdef USING_240X240

    #define ST7789_WIDTH 240
    #define ST7789_HEIGHT 240

		#if ST7789_ROTATION == 0
			#define X_SHIFT 0
			#define Y_SHIFT 80
		#elif ST7789_ROTATION == 1
			#define X_SHIFT 80
			#define Y_SHIFT 0
		#elif ST7789_ROTATION == 2
			#define X_SHIFT 0
			#define Y_SHIFT 0
		#elif ST7789_ROTATION == 3
			#define X_SHIFT 0
			#define Y_SHIFT 0
		#endif

#endif

/**
 *Color of pen
 *If you want to use another color, you can choose one in RGB565 format.
 */

#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define GRAY 0X8430
#define BRED 0XF81F
#define GRED 0XFFE0
#define GBLUE 0X07FF
#define BROWN 0XBC40
#define BRRED 0XFC07
#define DARKBLUE 0X01CF
#define LIGHTBLUE 0X7D7C
#define GRAYBLUE 0X5458

#define LIGHTGREEN 0X841F
#define LGRAY 0XC618
#define LGRAYBLUE 0XA651
#define LBBLUE 0X2B12

/* Control Registers and constant codes */
#define ST7789_NOP     0x00
#define ST7789_SWRESET 0x01
#define ST7789_RDDID   0x04
#define ST7789_RDDST   0x09

#define ST7789_SLPIN   0x10
#define ST7789_SLPOUT  0x11
#define ST7789_PTLON   0x12
#define ST7789_NORON   0x13

#define ST7789_INVOFF  0x20
#define ST7789_INVON   0x21
#define ST7789_DISPOFF 0x28
#define ST7789_DISPON  0x29
#define ST7789_CASET   0x2A
#define ST7789_RASET   0x2B
#define ST7789_RAMWR   0x2C
#define ST7789_RAMRD   0x2E

#define ST7789_PTLAR   0x30
#define ST7789_COLMOD  0x3A
#define ST7789_MADCTL  0x36

/**
 * Memory Data Access Control Register (0x36H)
 * MAP:     D7  D6  D5  D4  D3  D2  D1  D0
 * param:   MY  MX  MV  ML  RGB MH  -   -
 *
 */

/* Page Address Order ('0': Top to Bottom, '1': the opposite) */
#define ST7789_MADCTL_MY  0x80
/* Column Address Order ('0': Left to Right, '1': the opposite) */
#define ST7789_MADCTL_MX  0x40
/* Page/Column Order ('0' = Normal Mode, '1' = Reverse Mode) */
#define ST7789_MADCTL_MV  0x20
/* Line Address Order ('0' = LCD Refresh Top to Bottom, '1' = the opposite) */
#define ST7789_MADCTL_ML  0x10
/* RGB/BGR Order ('0' = RGB, '1' = BGR) */
#define ST7789_MADCTL_RGB 0x00

#define ST7789_RDID1   0xDA
#define ST7789_RDID2   0xDB
#define ST7789_RDID3   0xDC
#define ST7789_RDID4   0xDD

/* Advanced options */
/**
 * Caution: Do not operate these settings
 * You know what you are doing
 */


#define ST7789_COLOR_MODE_16bit 0x55    //  RGB565 (16bit)
#define ST7789_COLOR_MODE_18bit 0x66    //  RGB666 (18bit)


#endif
/**************************************************************************************/



/* 120ms is necessary after reset, for loading ID bytes, VCOM setting,
 * and other settings from NV memory to registers.
 */
#define ILI9341_RESET_CANCEL_MS 120U

typedef void (*lcd_send_byte_t)(uint8_t dataToSend);
void LCD_Init(lcd_send_byte_t _writeData, lcd_send_byte_t _writeCommand);

#endif
