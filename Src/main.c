#include <stdint.h>
#include "stm32f0xx.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f051x8.h"
#include"spi.h"

#include <stdlib.h>
#include <string.h>


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

static void SPI_GPIOInit(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* Enable GPIOA Clock */
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

	/* Configure PA4, PA5, PA6, PA7 */
	GPIO_InitStruct.Pin = LL_GPIO_PIN_4 |
						  LL_GPIO_PIN_5 |
						  LL_GPIO_PIN_6 |
						  LL_GPIO_PIN_7;

	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;

	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

int main(void)
{
	SPI_Handel_t SPI_Handel;

	SPI_Handel.pSPIx = SPI1;

	SPI_Handel.SPI_Config.SPI_BusConfig = SPI_DEVICE_FULL_DUPLEX_MODE;
	SPI_Handel.SPI_Config.SPI_Cphase = SPI_SCLK_FRIST_EDGE;
	SPI_Handel.SPI_Config.SPI_Cpol = SPI_SCLK_LOW;
	SPI_Handel.SPI_Config.SPI_DataSize = SPI_DATA_SIZE_8BIT;
	SPI_Handel.SPI_Config.SPI_DeviceMode = SPI_DEVICE_MASTER_MODE;
	SPI_Handel.SPI_Config.SPI_SSM = SPI_SSM_ENABLE;
	SPI_Handel.SPI_Config.SPI_SclkConfig = SPI_SCLK_DIV8;

	SPI_GPIOInit();

	SPI_periclockcontrol(SPI1,ENABLE);
	SPI_Init(&SPI_Handel);

	uint8_t Msg[] = "hello";

	SPI_PeripheralControl(SPI1, ENABLE);

	SPI_Send(&SPI_Handel, Msg, 5);

	SPI_PeripheralControl(SPI1, DISABLE);

	while(1)
	{

	}
}
