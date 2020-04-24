#include "stm32f103xb.h" 
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_tim.h" 

void Girouette_Conf(TIM_TypeDef * Timer);
void Girouette_Reset(void);
