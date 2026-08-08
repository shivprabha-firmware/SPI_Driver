/*
 * spi.c
 *
 *  Created on: 07-Jul-2026
 *      Author: Shivprabha
 */

#include"spi.h"

/*
 * This function is for enable peripheral clock
 */
void SPI_periclockcontrol(SPI_TypeDef *pSPIx,uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
		}
	}
	else
	{

	}
}
/*
 * This function is for SPI init
 */
void SPI_Init(SPI_Handel_t *SPI_Handel)
{
	uint32_t tempreg = 0;

	//Configure Mode Master or Slave
	if(SPI_Handel->SPI_Config.SPI_DeviceMode == SPI_DEVICE_MASTER_MODE)
	{
		tempreg |= SPI_CR1_MSTR;
	}
	else
	{
		//tempreg is alredy zero,no need to do anything
	}

	//Configure Bus Configuration
	if(SPI_Handel->SPI_Config.SPI_BusConfig == SPI_DEVICE_FULL_DUPLEX_MODE)
	{
		/* Nothing to do */
	}
	else if(SPI_Handel->SPI_Config.SPI_BusConfig == SPI_DEVICE_HALF_DUPLEX_MODE)
	{
		tempreg |= SPI_CR1_BIDIMODE;
	}

	//SPI sclk and Baudrate Configure
	tempreg |= (SPI_Handel->SPI_Config.SPI_SclkConfig << SPI_CR1_BR_Pos);

	/* Configure Clock Polarity */
	/*Reset value is 0.
	So if the user wants CPOL = LOW, we don't need
	to do anything because tempreg is already initialized to 0.*/
	if(SPI_Handel->SPI_Config.SPI_Cpol == SPI_SCLK_HIGH)
	{
		tempreg |= SPI_CR1_CPOL;
	}

	/* Configure Clock Phase */
	if(SPI_Handel->SPI_Config.SPI_Cphase == SPI_SCLK_SECOND_EDGE)
	{
		tempreg |= SPI_CR1_CPHA;
	}

	/*Software slave managment*/
	if(SPI_Handel->SPI_Config.SPI_SSM == SPI_SSM_ENABLE)
	{
		tempreg |= SPI_CR1_SSM;
		tempreg |= SPI_CR1_SSI;
	}

	SPI_Handel->pSPIx->CR1 = tempreg;

	tempreg = 0;

	/* Configure Data Size */
	tempreg |= (SPI_Handel->SPI_Config.SPI_DataSize << SPI_CR2_DS_Pos);

	SPI_Handel->pSPIx->CR2 = tempreg;
}

/*
 * This function enables peripheral
 */
void SPI_PeripheralControl(SPI_TypeDef *pSPIx,uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{
		pSPIx->CR1 |= SPI_CR1_SPE;
	}
	else
	{
		pSPIx->CR1 &= ~SPI_CR1_SPE;
	}
}

/*
 * This function sends byte
 */
void SPI_Send(SPI_Handel_t *pSPIhandel,uint8_t *pTxBuffer,uint32_t len)
{
	while(len > 0)
	{
		while(SPI_GetStatusFlag(pSPIhandel->pSPIx,SPI_SR_TXE) == FLAG_RESET);

		if(pSPIhandel->SPI_Config.SPI_DataSize == SPI_DATA_SIZE_8BIT)
		{
			pSPIhandel->pSPIx->DR = *pTxBuffer;
			pTxBuffer++;
			len--;
		}
		else if(pSPIhandel->SPI_Config.SPI_DataSize == SPI_DATA_SIZE_16BIT)
				{
					pSPIhandel->pSPIx->DR = *(uint16_t*)pTxBuffer;
					pTxBuffer+=2;
					len-=2;
				}
	}

	while(SPI_GetStatusFlag(pSPIhandel->pSPIx,SPI_SR_BSY) == FLAG_SET);
}

/*
 * This function checks status flag
 */
uint32_t SPI_GetStatusFlag(SPI_TypeDef *pSPIx,uint32_t Spi_Flagname)
{
	if(pSPIx->SR & Spi_Flagname)
	{
		return FLAG_SET;
	}
	else
		return FLAG_RESET;
}

/*
 * This function receives bytes
 */
void SPI_Receive(SPI_Handel_t *pSPIHandel,uint8_t *RxBuffer, uint32_t len)
{
	while(len > 0)
	{
		while(SPI_GetStatusFlag(pSPIHandel->pSPIx,SPI_SR_RXNE)== FLAG_RESET);

		if(pSPIHandel->SPI_Config.SPI_DataSize == SPI_DATA_SIZE_8BIT)
		{
			*RxBuffer = pSPIHandel->pSPIx->DR;
			RxBuffer++;
			len--;
		}
		else if(pSPIHandel->SPI_Config.SPI_DataSize == SPI_DATA_SIZE_16BIT)
				{
					*(uint16_t*)RxBuffer = pSPIHandel->pSPIx->DR;
					RxBuffer+=2;
					len-=2;
				}
	}
}



