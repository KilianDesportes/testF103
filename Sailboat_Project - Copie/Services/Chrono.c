// A COMPLETER

/*
Service permettant de chornométrer jusqu'à 59mn 59s 99 1/100
Utilise un timer au choix (TIMER1 à TIMER4).
Utilise la lib MyTimers.h /.c
*/



#include "Chrono.h"
#include "MyTimer.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_bus.h"
#include "stm32f1xx_hal_usart.h"
#include "stdlib.h"


// variable privée de type Time qui mémorise la durée mesurée
static Time Chrono_Time; // rem : static rend la visibilité de la variable Chrono_Time limitée à ce fichier 

// variable privée qui mémorise pour le module le timer utilisé par le module
static TIM_TypeDef * Chrono_Timer=TIM1; // init par défaut au cas où l'utilisateur ne lance pas Chrono_Conf avant toute autre fct.

// déclaration callback appelé toute les 10ms
void Chrono_Task_10ms(void);

/**
	* @brief  Configure le chronomètre. 
  * @note   A lancer avant toute autre fonction.
	* @param  Timer : indique le timer à utiliser par le chronomètre, TIM1, TIM2, TIM3 ou TIM4
  * @retval None
  */
	
	


void Chrono_Conf(TIM_TypeDef * Timer)
{
	
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
	
	LL_GPIO_InitTypeDef GPIO_InitStruct_LED;
	GPIO_InitStruct_LED.Pin = LL_GPIO_PIN_10;
	GPIO_InitStruct_LED.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
  GPIO_InitStruct_LED.Mode = LL_GPIO_MODE_OUTPUT_10MHz;
	GPIO_InitStruct_LED.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct_LED);
	
	LL_GPIO_InitTypeDef GPIO_InitStruct_START;
	GPIO_InitStruct_START.Pin = LL_GPIO_PIN_8;
	GPIO_InitStruct_LED.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
  GPIO_InitStruct_START.Mode = LL_GPIO_MODE_FLOATING;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct_START);
	
	LL_GPIO_InitTypeDef GPIO_InitStruct_STOP;
	GPIO_InitStruct_STOP.Pin = LL_GPIO_PIN_6;
	GPIO_InitStruct_LED.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
  GPIO_InitStruct_STOP.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct_STOP.Pull = LL_GPIO_PULL_DOWN;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct_STOP);
	
	
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	
	LL_USART_InitTypeDef USART_Init = {9600U, 
		LL_USART_DATAWIDTH_8B, 
		LL_USART_STOPBITS_1, 
		LL_USART_PARITY_NONE, 
		LL_USART_DIRECTION_TX,
		LL_USART_HWCONTROL_NONE};
	
	LL_USART_Init( USART2 , &USART_Init );
		
	LL_USART_Enable( USART2 );
		
	//LL_USART_EnableIT_TXE( USART2 );
		
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

	LL_GPIO_InitTypeDef GPIO_Init = {	LL_GPIO_PIN_2,
		LL_GPIO_MODE_ALTERNATE,
		LL_GPIO_SPEED_FREQ_MEDIUM,
		LL_GPIO_OUTPUT_PUSHPULL,
		LL_GPIO_PULL_DOWN };
		
	LL_GPIO_Init( GPIOA, &GPIO_Init );
	
	
	
	// Reset Time
	Chrono_Time.Hund=0;
	Chrono_Time.Sec=0;
	Chrono_Time.Min=0;
	
	// Fixation du Timer
	Chrono_Timer=Timer;

	// Réglage Timer pour un débordement à 10ms
	MyTimer_Conf(Chrono_Timer,999, 719);
	
	// Réglage interruption du Timer avec callback : Chrono_Task_10ms()
	MyTimer_IT_Conf(Chrono_Timer, Chrono_Task_10ms,3);
	
	// Validation IT
	MyTimer_IT_Enable(Chrono_Timer);
	
	
	
}


/**
	* @brief  Démarre le chronomètre. 
  * @note   si la durée dépasse 59mn 59sec 99 Hund, elle est remise à zéro et repart
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Start(void)
{
	MyTimer_Start(Chrono_Timer);
}


/**
	* @brief  Arrête le chronomètre. 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Stop(void)
{
	MyTimer_Stop(Chrono_Timer);
}


/**
	* @brief  Remet le chronomètre à 0 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Reset(void)
{
  // Arrêt Chrono
	MyTimer_Stop(Chrono_Timer);

	// Reset Time
	Chrono_Time.Hund=0;
	Chrono_Time.Sec=0;
	Chrono_Time.Min=0;
}


/**
	* @brief  Renvoie l'adresse de la variable Time privée gérée dans le module Chrono.c
  * @note   
	* @param  Aucun
  * @retval adresse de la variable Time
  */
Time * Chrono_Read(void)
{
	return &Chrono_Time;
}




/**
	* @brief  incrémente la variable privée Chron_Time modulo 60mn 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */




int d_c;
int u_c;
int d_s;
int u_s;
int d_m;
int u_m;
char tab_hour[8] = {0,0,':',0,0,':',0,0};




void Chrono_Task_10ms(void)
{ 
	
	Chrono_Time.Hund++;
	
	d_c = Chrono_Time.Hund/10;
	u_c = Chrono_Time.Hund%10;
	
	tab_hour[0] = d_c + 0x30;
	tab_hour[1] = u_c + 0x30;
	
	if (Chrono_Time.Hund==100)
	{
		Chrono_Time.Sec++;
		Chrono_Time.Hund=0;
		
		d_s = Chrono_Time.Sec/10;
		u_s = Chrono_Time.Sec%10;
		
		tab_hour[3] = d_s + 0x30;
		tab_hour[4] = u_s + 0x30;
		
		
	}
	if (Chrono_Time.Sec==60)
	{
		Chrono_Time.Min++;
		Chrono_Time.Sec=0;
		
		d_m = Chrono_Time.Min/10;
		u_m = Chrono_Time.Min%10;
		
		tab_hour[6] = d_m + 0x30;
		tab_hour[7] = u_m + 0x30;
		
	}
	if (Chrono_Time.Min==60)
	{
		Chrono_Time.Hund=0;
	}
	
	int i = 0;
	for(i = 0 ; i < 8 ; i++){
		LL_USART_TransmitData8(USART2, tab_hour[i]);
		while (LL_USART_IsActiveFlag_TXE(USART2));
	}
	
	LL_USART_TransmitData8(USART2, 0x0D);
	while (LL_USART_IsActiveFlag_TXE(USART2));	

}


