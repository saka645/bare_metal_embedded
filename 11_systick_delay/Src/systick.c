/*
 * systick.c
 *
 *  Created on: Jan 23, 2024
 *      Author: sanjay.kumar
 */

#include <stm32f0xx.h>

#define SYSTICK_LOAD_VAL		48000U
#define CTRL_ENABLE				(1U<<0)
#define CTRL_CLKSRC				(1U<<2)
#define CTRL_COUNTFLAG			(1U<<16)

void systickDelayMs(int delay)
{
	/*load with no of clocks per miliseconds*/
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	/*clear systick current value register*/
	SysTick->VAL = 0;

	/*enable systick and select internal clock source*/
	SysTick->CTRL = (CTRL_ENABLE | CTRL_CLKSRC);

	for(int i=0; i<delay; i++)
	{
		/*wait until counter is set*/
		while((SysTick->CTRL & CTRL_COUNTFLAG)==0);

	}
	SysTick->CTRL = 0;
}
