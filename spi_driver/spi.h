/*
 * spi.h
 *
 *  Created on: 07-Jul-2026
 *      Author: rohan
 */

#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

#include<stdint.h>
#include "stm32f051x8.h"

//SPI Config structure
typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkConfig;
	uint8_t SPI_DataSize;
	uint8_t SPI_Cpol;
	uint8_t SPI_Cphase;
	uint8_t SPI_SSM;
}SPI_Config_t;

typedef struct
{
	SPI_TypeDef *pSPIx;
	SPI_Config_t SPI_Config;
}SPI_Handel_t;

//SPI Device Mode
#define SPI_DEVICE_SLAVE_MODE 0
#define SPI_DEVICE_MASTER_MODE 1

//SPI Bus Config Select
#define SPI_DEVICE_FULL_DUPLEX_MODE 1
#define SPI_DEVICE_HALF_DUPLEX_MODE 0

//SPI Clock Prescalar
#define SPI_SCLK_DIV2   0
#define SPI_SCLK_DIV4   1
#define SPI_SCLK_DIV8   2
#define SPI_SCLK_DIV16  3
#define SPI_SCLK_DIV32  4
#define SPI_SCLK_DIV64  5
#define SPI_SCLK_DIV128 6
#define SPI_SCLK_DIV256 7

//SPI Data Size
#define SPI_DATA_SIZE_8BIT  0x7
#define SPI_DATA_SIZE_16BIT 0xF

//SPI SCLK CPOL
#define SPI_SCLK_LOW   0
#define SPI_SCLK_HIGH  1

//SPI CPH
#define SPI_SCLK_FRIST_EDGE   0
#define SPI_SCLK_SECOND_EDGE  1
#endif /* SPI_H_ */

/* SPI Software Slave Management */
#define SPI_SSM_DISABLE     0
#define SPI_SSM_ENABLE      1

/*SPI ENABLE or DISABLE*/
#define ENABLE  1
#define DISABLE 0

//SET RESET Flag
#define FLAG_SET    1
#define FLAG_RESET  0

void SPI_periclockcontrol(SPI_TypeDef *pSPIx,uint8_t ENorDI);
void SPI_Init(SPI_Handel_t *SPI_Handel);
void SPI_Send(SPI_Handel_t *pSPIhandel,uint8_t *pTxBuffer,uint32_t len);
void SPI_PeripheralControl(SPI_TypeDef *pSPIx,uint8_t ENorDI);
uint32_t SPI_GetStatusFlag(SPI_TypeDef *pSPIx,uint32_t Spi_Flagname);
void SPI_Receive(SPI_Handel_t *pSPIHandel,uint8_t *RxneBuffer, uint32_t len);
