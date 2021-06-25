/*
 * Copyright 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RTE_DEVICE_H
#define _RTE_DEVICE_H

extern void LPI2C4_InitPins();
extern void LPI2C4_DeinitPins();
extern void LPSPI3_InitPins();
extern void LPSPI3_DeinitPins();

/* User needs to provide the implementation of LPI2CX_GetFreq/LPI2CX_InitPins/LPI2CX_DeinitPins for the enabled LPI2C
 * instance. */
#define RTE_I2C4            1
#define RTE_I2C4_PIN_INIT   LPI2C4_InitPins
#define RTE_I2C4_PIN_DEINIT LPI2C4_DeinitPins
#define RTE_I2C4_DMA_EN     0

/*
#define RTE_I2C1        1
#define RTE_I2C1_DMA_EN 1

// LPI2C configuration. //
#define RTE_I2C1_PIN_INIT           LPI2C1_InitPins
#define RTE_I2C1_PIN_DEINIT         LPI2C1_DeinitPins
#define RTE_I2C1_DMA_TX_CH          0
#define RTE_I2C1_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMuxLPI2C1
#define RTE_I2C1_DMA_TX_DMAMUX_BASE DMAMUX
#define RTE_I2C1_DMA_TX_DMA_BASE    DMA0
#define RTE_I2C1_DMA_RX_CH          1
#define RTE_I2C1_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMuxLPI2C1
#define RTE_I2C1_DMA_RX_DMAMUX_BASE DMAMUX
#define RTE_I2C1_DMA_RX_DMA_BASE    DMA0
*/
////////////////////////////////////////////////////////////////////////////////////////////////////
#define RTE_SPI3 1
#define RTE_SPI3_PIN_INIT   LPSPI3_InitPins
#define RTE_SPI3_PIN_DEINIT LPSPI3_DeinitPins
#define RTE_SPI3_DMA_EN     1

#define SPI3_RX_FIFO_SIZE 8
#define SPI3_TX_FIFO_SIZE 8

#define RTE_SPI3_SSEL_NUM           kSPI_Ssel0
#define RTE_SPI3_PIN_INIT           LPSPI3_InitPins
#define RTE_SPI3_PIN_DEINIT         LPSPI3_DeinitPins
#define RTE_SPI3_DMA_TX_CH          13
#define RTE_SPI3_DMA_TX_PERI_SEL    (uint8_t) kDmaRequestMuxLPSPI3Tx
#define RTE_SPI3_DMA_TX_DMAMUX_BASE DMAMUX
#define RTE_SPI3_DMA_TX_DMA_BASE    DMA0
#define RTE_SPI3_DMA_RX_CH          12
#define RTE_SPI3_DMA_RX_PERI_SEL    (uint8_t) kDmaRequestMuxLPSPI3Rx
#define RTE_SPI3_DMA_RX_DMAMUX_BASE DMAMUX
#define RTE_SPI3_DMA_RX_DMA_BASE    DMA0

#define RTE_SPI3_PCS_TO_SCK_DELAY 0
#define RTE_SPI3_SCK_TO_PSC_DELAY 0
#define RTE_SPI3_BETWEEN_TRANSFER_DELAY 10 /* For 10MHz baudrate. delay(ns) = 10^9/baudrate/2. */
#define RTE_SPI3_MASTER_PCS_PIN_SEL     kLPSPI_MasterPcs0

#endif /* _RTE_DEVICE_H */
