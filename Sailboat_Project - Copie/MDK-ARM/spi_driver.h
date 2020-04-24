#ifndef PROJECTDRIVERS_SPI_H_
#define PROJECTDRIVERS_SPI_H_

#include "main.h"

extern SPI_HandleTypeDef hspi;

/**
 * @brief  Initialize the Test service.
 * @retval Return a SPI_HandleTypeDef
 */
SPI_HandleTypeDef SPI_Init_MasterReceiveOnly(SPI_TypeDef * SPI);

/**
 * @brief  Used by HAL to configure lower layer SPI needed features.
 * @retval None
 */
void HAL_SPI_MspInit(SPI_HandleTypeDef * spiHandle);

/**
 * @brief  Listen for incoming data and fill data array given as parameter.
 * @retval None
 */
void SPI_Receive(SPI_HandleTypeDef * SPI_Struct, GPIO_TypeDef * GPIO, uint16_t GPIO_PIN, uint8_t * pdata, uint16_t Size);

#endif
