#include "girouette.h"

#include "MyTimer.h"

#include "stdlib.h"

int i = 0;

void Girouette_Conf(TIM_TypeDef * Timer)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	LL_GPIO_InitTypeDef GPIO_Init_5;
	GPIO_Init_5.Pin = LL_GPIO_PIN_5;
	GPIO_Init_5.Mode = LL_GPIO_MODE_INPUT;
	GPIO_Init_5.Pull = LL_GPIO_PULL_DOWN;
	LL_GPIO_Init( GPIOA, &GPIO_Init_5 );
	
	LL_GPIO_InitTypeDef GPIO_Init_6;
	GPIO_Init_6.Pin = LL_GPIO_PIN_6;
	GPIO_Init_6.Mode = LL_GPIO_MODE_INPUT;
		GPIO_Init_6.Pull = LL_GPIO_PULL_DOWN;

	LL_GPIO_Init( GPIOA, &GPIO_Init_6 );

	LL_GPIO_InitTypeDef GPIO_Init_7;
	GPIO_Init_7.Pin = LL_GPIO_PIN_7;
	GPIO_Init_7.Mode = LL_GPIO_MODE_INPUT;
		GPIO_Init_7.Pull = LL_GPIO_PULL_DOWN;

	LL_GPIO_Init( GPIOA, &GPIO_Init_7 );
	
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
		
	TIM3->ARR = 1440;
	
	TIM3->CCMR1 |= TIM_CCMR1_CC1S_0;
	TIM3->CCMR1 &= ~TIM_CCMR1_CC1S_1;
	
	TIM3->CCMR1 |= TIM_CCMR1_CC2S_0;
	TIM3->CCMR1 &= ~TIM_CCMR1_CC2S_1;
	
	TIM3->CCER  |= TIM_CCER_CC1P;
	
	TIM3->CCER |= TIM_CCER_CC2P;
	
	TIM3->SMCR  |= TIM_SMCR_SMS_0;
	TIM3->SMCR  |= TIM_SMCR_SMS_1;
	TIM3->SMCR  &= ~TIM_SMCR_SMS_2;

	LL_TIM_CC_EnableChannel(Timer,LL_TIM_CHANNEL_CH1);
	LL_TIM_CC_EnableChannel(Timer,LL_TIM_CHANNEL_CH2);
				
	LL_TIM_EnableCounter(Timer);
}

void Girouette_Reset(void)
{
	while(!LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_5)){
	}
	TIM3->CNT = 0;		

}


