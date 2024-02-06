#include <stm32f0xx.h>
#include <stdio.h>
#include "tim.h"
#include "uart2.h"


#define GPIOCEN		(1<<19)
#define PIN9		(1<<9)
#define LED_PIN		PIN9

int timestamp = 0;

int main()
{
//	RCC->AHBENR |= GPIOCEN;
//	GPIOC->MODER |= (1<<18);
//	GPIOC->MODER &= ~(1<<19);
//	timer6_init1Hz();
//	uart2_tx_init();
	timer15_ch1_OutputCompare();
	timer3_Pc6_InputCapture();
	while(1)
	{
		/*wait until edge is captured*/
		while(!(TIM3->SR & SR_CC1IF));
		/*read captured value*/
		timestamp = TIM3->CCR1;
	}
}
