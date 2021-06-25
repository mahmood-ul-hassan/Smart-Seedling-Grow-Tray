/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "littlevgl_support.h"
#include "lvgl.h"
#if defined(FSL_RTOS_FREE_RTOS)
#include "FreeRTOS.h"
#include "semphr.h"
#endif

#include "board.h"
#include "pin_mux.h"

#include "littlevgl_support.h"
#include "fsl_gpio.h"
#include "fsl_debug_console.h"
#include <lcd.h>
#include "fsl_lpspi_cmsis.h"
#include "fsl_enc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Port Me, Start. */
#define BOARD_LCD_SPI            Driver_SPI3
#define BOARD_LCD_SPI_BAUDRATE   10000000U
#define BOARD_LCD_SPI_IRQ        LPSPI3_IRQn
#define BOARD_LCD_SPI_FREQ_FUNC  LPSPI3_GetFreq
#define BOARD_LCD_SPI_FREQ       CLOCK_GetFreq(kCLOCK_SysPllClk) / LPSPI_CLOCK_SOURCE_DIVIDER
#define BOARD_LCD_SPI_DMA_TX_IRQ DMA13_DMA29_IRQn
#define BOARD_LCD_SPI_DMA_RX_IRQ DMA12_DMA28_IRQn
/* Port Me, End. */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void DEMO_InitLcd(void);
static void DEMO_InitEncoder(void);
static bool DEMO_ReadEncoder(lv_indev_drv_t *drv, lv_indev_data_t *data);
static void DEMO_FlushDisplay(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);
/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(FSL_RTOS_FREE_RTOS)
static SemaphoreHandle_t s_transferDone;
#else
static volatile bool s_transferDone;
#endif

AT_NONCACHEABLE_SECTION_ALIGN_INIT(static uint8_t s_frameBuffer[2][LCD_VIRTUAL_BUF_SIZE * LCD_FB_BYTE_PER_PIXEL], 4);
AT_NONCACHEABLE_SECTION_ALIGN_INIT(uint8_t tft_spi_data[4], 4);

lv_indev_t* encoder_indev; //The input device

/*******************************************************************************
 * Code
 ******************************************************************************/
void lv_port_pre_init(void)
{
}

uint32_t BOARD_LCD_SPI_FREQ_FUNC(void)
{
    return BOARD_LCD_SPI_FREQ;
}

static void SPI_MasterSignalEvent(uint32_t event)
{
#if defined(FSL_RTOS_FREE_RTOS)
    BaseType_t taskAwake = pdFALSE;

    xSemaphoreGiveFromISR(s_transferDone, &taskAwake);

    portYIELD_FROM_ISR(taskAwake);
#else
    s_transferDone = true;
#endif
}

static void SPI_WaitEvent(void)
{
#if defined(FSL_RTOS_FREE_RTOS)
    if (xSemaphoreTake(s_transferDone, portMAX_DELAY) != pdTRUE)
    {
        PRINTF("LCD SPI transfer error\r\n");
    }
#else
    while (false == s_transferDone)
    {
    }
    s_transferDone = false;
#endif
}

static void DEMO_SPI_LCD_WriteCmd(uint8_t Data)
{
	tft_spi_data[0]=Data;
    GPIO_PortClear(BOARD_INITPINS_TFT_DC_GPIO, BOARD_INITPINS_TFT_DC_GPIO_PIN_MASK);
    BOARD_LCD_SPI.Send(tft_spi_data, 1);
    SPI_WaitEvent();
}

static void DEMO_SPI_LCD_WriteData(uint8_t Data)
{
	tft_spi_data[0]=Data;
    GPIO_PortSet(BOARD_INITPINS_TFT_DC_GPIO, BOARD_INITPINS_TFT_DC_GPIO_PIN_MASK);
    BOARD_LCD_SPI.Send(tft_spi_data, 1);
    SPI_WaitEvent();
}

static void DEMO_SPI_LCD_WriteMultiData(const uint8_t *pData, int NumItems)
{
    GPIO_PortSet(BOARD_INITPINS_TFT_DC_GPIO, BOARD_INITPINS_TFT_DC_GPIO_PIN_MASK);
    BOARD_LCD_SPI.Send(pData, NumItems);
    SPI_WaitEvent();
}

static void DEMO_InitLcdSPiClk(void)
{
    /* Set LPSPI_PODF. */
    CLOCK_SetDiv(kCLOCK_LpspiDiv, LPSPI_CLOCK_SOURCE_DIVIDER);
    /* Set Lpspi clock source. */
    CLOCK_SetMux(kCLOCK_LpspiMux, LPSPI_CLOCK_SOURCE_SELECT);
}

static void DEMO_InitLcd(void)
{
/* Define the init structure for the data/command output pin */

    /* Clear frame buffer. */
    memset((void *)s_frameBuffer, 0, sizeof(s_frameBuffer));

    DEMO_InitLcdSPiClk();

#if defined(FSL_RTOS_FREE_RTOS)
    s_transferDone = xSemaphoreCreateBinary();
    if (NULL == s_transferDone)
    {
        PRINTF("Semaphore create failed\r\n");
        assert(0);
    }
#else
    s_transferDone = false;
#endif

#if defined(FSL_RTOS_FREE_RTOS)
    /* FreeRTOS kernel API is used in SPI ISR, so need to set proper IRQ priority. */
    NVIC_SetPriority(BOARD_LCD_SPI_IRQ, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1);
    NVIC_SetPriority(BOARD_LCD_SPI_DMA_TX_IRQ, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1);
    NVIC_SetPriority(BOARD_LCD_SPI_DMA_RX_IRQ, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1);
#endif

    /* SPI master init */
    BOARD_LCD_SPI.Initialize(SPI_MasterSignalEvent);
    BOARD_LCD_SPI.PowerControl(ARM_POWER_FULL);
    BOARD_LCD_SPI.Control(ARM_SPI_MODE_MASTER | ARM_SPI_CPOL1_CPHA0 | ARM_SPI_DATA_BITS(8), BOARD_LCD_SPI_BAUDRATE);
    BOARD_LCD_SPI.Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_INACTIVE);


	GPIO_PortSet(BOARD_INITPINS_TFT_RES_GPIO, BOARD_INITPINS_TFT_RES_GPIO_PIN_MASK);
	SDK_DelayAtLeastUs(25 * 1000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
	GPIO_PortClear(BOARD_INITPINS_TFT_RES_GPIO, BOARD_INITPINS_TFT_RES_GPIO_PIN_MASK);
	SDK_DelayAtLeastUs(100 * 1000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    GPIO_PortSet(BOARD_INITPINS_TFT_RES_GPIO, BOARD_INITPINS_TFT_RES_GPIO_PIN_MASK);
	SDK_DelayAtLeastUs(50 * 1000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);

	LCD_Init(DEMO_SPI_LCD_WriteData, DEMO_SPI_LCD_WriteCmd);
}

void lv_port_disp_init(void)
{
    static lv_disp_buf_t disp_buf;
    memset(s_frameBuffer, 0, sizeof(s_frameBuffer));
    lv_disp_buf_init(&disp_buf, s_frameBuffer[0], s_frameBuffer[1], LCD_VIRTUAL_BUF_SIZE);

    /*-------------------------
     * Initialize your display
     * -----------------------*/
    DEMO_InitLcd();

    /*-----------------------------------
     * Register the display in LittlevGL
     *----------------------------------*/

    lv_disp_drv_t disp_drv;      /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv); /*Basic initialization*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = LCD_WIDTH;
    disp_drv.ver_res = LCD_HEIGHT;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = DEMO_FlushDisplay;

    /*Set a display buffer*/
    disp_drv.buffer = &disp_buf;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}

static void DEMO_FlushDisplay(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    lv_coord_t x1 = area->x1;
    lv_coord_t y1 = area->y1;
    lv_coord_t x2 = area->x2;
    lv_coord_t y2 = area->y2;

    const uint8_t *pdata = (const uint8_t *)color_p;
    uint32_t send_size   = (x2 - x1 + 1) * (y2 - y1 + 1) * LCD_FB_BYTE_PER_PIXEL;

    /*Column addresses*/
    DEMO_SPI_LCD_WriteCmd(ST7789_CASET);
    tft_spi_data[0] = (x1 >> 8) & 0xFF;
    tft_spi_data[1] = x1 & 0xFF;
    tft_spi_data[2] = (x2 >> 8) & 0xFF;
    tft_spi_data[3] = x2 & 0xFF;
    DEMO_SPI_LCD_WriteMultiData(tft_spi_data, 4);

    /*Page addresses*/
    DEMO_SPI_LCD_WriteCmd(ST7789_RASET);
    tft_spi_data[0] = (y1 >> 8) & 0xFF;
    tft_spi_data[1] = y1 & 0xFF;
    tft_spi_data[2] = (y2 >> 8) & 0xFF;
    tft_spi_data[3] = y2 & 0xFF;
    DEMO_SPI_LCD_WriteMultiData(tft_spi_data, 4);

    /*Memory write*/
    DEMO_SPI_LCD_WriteCmd(ST7789_RAMWR);
    DEMO_SPI_LCD_WriteMultiData(pdata, send_size);

    lv_disp_flush_ready(disp_drv);
}

void lv_port_indev_init(void)
{
    lv_indev_drv_t indev_drv;

    /*------------------
     * Touchpad
     * -----------------*/

    /*Initialize your touchpad */
//    DEMO_InitEncoder();

    /*Register a touchpad input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type    = LV_INDEV_TYPE_ENCODER;
    indev_drv.read_cb = DEMO_ReadEncoder;
    encoder_indev = lv_indev_drv_register(&indev_drv);
}

/*Initialize your encoder*/
static void DEMO_InitEncoder(void)
{
    enc_config_t mEncConfigStruct;

    /* Initialize the ENC module. */
    ENC_GetDefaultConfig(&mEncConfigStruct);
    /* Setup the hardware. */
    ENC_Init(ENC1, &mEncConfigStruct);
    /* Update position counter from initial position register. */
    ENC_DoSoftwareLoadInitialPositionValue(ENC1);

    ENC_ClearStatusFlags(ENC1, kENC_INDEXPulseFlag);

	PRINTF("Encoder init\n");
}

/* Will be called by the library to read the encoder */
static bool DEMO_ReadEncoder(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    static int32_t mPosdiff = 0;
    static int32_t mPrePosValue = 0;
    static int32_t mCurPosValue;

    mCurPosValue = (int32_t)ENC_GetPositionValue(ENC1);
    mPosdiff = mCurPosValue-mPrePosValue;

    if(mPosdiff/2){
    	mPrePosValue=mCurPosValue;
        data->enc_diff = mPosdiff/2;

    }

    data->state = !GPIO_PinRead(BOARD_INITPINS_ENC_SW_GPIO, BOARD_INITPINS_ENC_SW_GPIO_PIN);

/*
    if(data->enc_diff)
    	PRINTF("Encoder diff %d\n", (int32_t)data->enc_diff);

    if(data->state)
    	PRINTF("Encoder SW %d\n", data->state);
*/
    /*Return `false` because we are not buffering and no more data to read*/
    return false;
}
