#include "spi_test.h"
#include "spi.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_spi.h"
#include "stdlib.h"

#define SIZE 4

SPI_HandleTypeDef hspi_masterReceive;

/**
 * @brief  Initialize the needed GPIO.
 * @retval None
 */
void GPIO_Init(void) {

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SPI_SS_PORT, SPI_SS_PIN, GPIO_PIN_SET);

	/* Configure GPIO pins :
	 * PB0 : Slave Select 1 (Pressure Sensor)
	 * PB7 : LED */
	GPIO_InitStruct.Pin = SPI_SS_PIN | LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

void SPI_Test_Init() {

	GPIO_Init();
	hspi_masterReceive = SPI_Init_MasterReceiveOnly(SPI1);

}

void SPI_Test_Blink() {
	for (int i = 0; i < 2; i++) {
		HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);
		HAL_Delay(150);
		HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);
		HAL_Delay(150);
	}
}

/**
 * @brief  Initialize the Test service.
 * @retval Return a pointer to the received data
 */
uint8_t* ReadSensor_8() {

	static uint8_t data[8];

	SPI_Receive(&hspi_masterReceive, SPI_SS_PORT, SPI_SS_PIN, data, 8);

	return data;

}

void SPI_Test_Background() {

	/**
	 * The arduino used for the test
	 * output an increasing number % 16
	 * for each spi clock cycle and start at 0;
	 */

	uint8_t *pdata = ReadSensor_8();

	int ok = (pdata[0] == 0);

	if (ok == 1) {
		// LED ON
		HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);
		HAL_Delay(1000);
	} else {
		// LED OFF
		HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);
		HAL_Delay(1000);
	}

}
