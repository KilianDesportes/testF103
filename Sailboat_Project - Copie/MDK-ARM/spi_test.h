#ifndef INC_SPI_TEST_H_
#define INC_SPI_TEST_H_

#include "spi_test.h"
#include "stm32f1xx_hal_gpio.h"

#define SPI_SS_PIN GPIO_PIN_0
#define SPI_SS_PORT GPIOB

#define LED_PIN GPIO_PIN_7
#define LED_PORT GPIOB

/**
 * @brief  Initialize the Test service.
 * @retval None
 */
void SPI_Test_Init();

/**
 * @brief  Blink the LED twice.
 * @retval None
 */
void SPI_Test_Blink();

/**
 * @brief Light an LED according to the received data.
 * @retval None
 */
void SPI_Test_Background();

#endif /* INC_SPI_TEST_H_ */
