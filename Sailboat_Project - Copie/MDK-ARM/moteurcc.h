#include "Chrono.h"
#include "MyTimer.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_tim.h" 
#include "stdlib.h"
#include "stm32f103xb.h" 

void MoteurCC_Congif(TIM_TypeDef * Timer, int valeurTelecommande);
