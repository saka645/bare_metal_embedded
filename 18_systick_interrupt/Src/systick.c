/*
 * systick.c
 *
 *  Created on: Jan 23, 2024
 *      Author: sanjay.kumar
 */

#include <stm32f0xx.h>

#define SYSTICK_LOAD_VAL		8000U
#define CTRL_ENABLE				(1U<<0)
#define CTRL_SYSTICK_INT		(1U<<1)
#define CTRL_CLKSRC				(1U<<2)
#define CTRL_COUNTFLAG			(1U<<16)

#define ONE_SEC_LOAD			8000000U

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

void systick1HzInterruptInit()
{
	/*load with no of clocks per miliseconds*/
	SysTick->LOAD = ONE_SEC_LOAD-1;
	/*clear systick current value register*/
	SysTick->VAL = 0;
	/*enable systick and select internal clock source*/
	SysTick->CTRL = (CTRL_ENABLE | CTRL_CLKSRC);
	/*enable systick interrupt */
	SysTick->CTRL |= CTRL_SYSTICK_INT;

}
