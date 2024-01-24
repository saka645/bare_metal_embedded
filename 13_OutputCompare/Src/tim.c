/*
 * tim.c
 *
 *  Created on: Jan 24, 2024
 *      Author: sanjay.kumar
 */

#include <stm32f0xx.h>

#define TIMER16_EN			(1U<<17)
#define TIMER6_EN			(1U<<4)
#define CR1_CEN				(1U<<0)
#define OCTOGGLE			((1U<<4) | (1U<<5))
#define CC1E				(1U<<0)
#define RCC_GPIOBEN			(1U<<18)


void timer6_init1Hz()
{
	/*enable clock access to timer6*/
	RCC->APB1ENR |= TIMER6_EN;
	/*set prescalar value*/
	TIM6->PSC = 4800 -1;
	/*set auto reload value*/
	TIM6->ARR = 10000 -1;
	/*enable timer*/
	TIM6->CNT = 0;
	TIM6->CR1 |= CR1_CEN;
}


void timer16_OutputCompare()
{

	RCC->AHBENR |= RCC_GPIOBEN;
	/*gpio b8 as alternate function mode*/
	GPIOB->MODER &= ~(1U<<16);
	GPIOB->MODER |= (1U<<17);
	/*Set pb8 to alternate function 2 mode*/
	GPIOB->AFR[1] &= ~(1U<<0);
	GPIOB->AFR[1] |= (1U<<1);
	GPIOB->AFR[1] &= ~(1U<<2);
	GPIOB->AFR[1] &= ~(1U<<3);
	/*enable clock access to timer16 */
	RCC->APB2ENR |= TIMER16_EN;
	/*set prescalar value*/
	TIM16->PSC = 4800 -1;
	/*set auto reload value*/
	TIM16->ARR = 10000 -1;

	/*set output compare toggle mode*/
	TIM16->CCMR1 |= OCTOGGLE;
	/*enable timer3 compare mode channel6 PB8 */
	TIM16->CCER |= CC1E;



	/*enable timer*/
	TIM16->CNT = 0;
	TIM16->CR1 |= CR1_CEN;
}
