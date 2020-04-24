#include "spi_driver.h"

SPI_HandleTypeDef SPI_Init_MasterReceiveOnly(SPI_TypeDef *SPI) {

	SPI_HandleTypeDef hspi;

	hspi.Instance = SPI;
	hspi.Init.Mode = SPI_MODE_MASTER;
	hspi.Init.Direction = SPI_DIRECTION_2LINES_RXONLY;
	hspi.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi.Init.NSS = SPI_NSS_SOFT;
	hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi) != HAL_OK) {
		Error_Handler();
	}

	return hspi;

}

void HAL_SPI_MspInit(SPI_HandleTypeDef *spiHandle) {

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	if (spiHandle->Instance == SPI1) {

		/*
		
		__HAL_RCC_SPI1_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();

		GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
		
		*/
		
		__HAL_RCC_SPI1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
		
    /**SPI1 GPIO Configuration    
    PA5     ------> SPI1_SCK
    PA7     ------> SPI1_MOSI 
    */
		
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	} 
	
	/*
	
	else if (spiHandle->Instance == SPI2) {

		__HAL_RCC_SPI2_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();

		GPIO_InitStruct.Pin = GPIO_PIN_2;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		
	} else if (spiHandle->Instance == SPI3) {

		__HAL_RCC_SPI3_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();

		GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	}
	
	*/
}

void SPI_Receive(SPI_HandleTypeDef *SPI_Struct, GPIO_TypeDef *GPIO,
		uint16_t GPIO_PIN, uint8_t *pdata, uint16_t size) {

	HAL_GPIO_WritePin(GPIO, GPIO_PIN, GPIO_PIN_RESET);
	HAL_SPI_Receive(SPI_Struct, pdata, size, 5000);
	HAL_GPIO_WritePin(GPIO, GPIO_PIN, GPIO_PIN_SET);

}
