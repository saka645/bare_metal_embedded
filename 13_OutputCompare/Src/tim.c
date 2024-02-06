/*
 * tim.c
 *
 *  Created on: Jan 24, 2024
 *      Author: sanjay.kumar
 */

#include <stm32f0xx.h>

#define TIMER3_EN			(1U<<1)
#define TIMER6_EN			(1U<<4)
#define CR1_CEN				(1U<<0)
#define OCTOGGLE			((1U<<4) | (1U<<5))
#define CC3E				(1U<<8)
#define RCC_GPIOCEN			(1U<<19)


void timer6_init1Hz()
{
	/*enable clock access to timer6*/
	RCC->APB1ENR |= TIMER6_EN;
	/*set prescalar value*/
	TIM6->PSC = 800 -1;
	/*set auto reload value*/
	TIM6->ARR = 10000 -1;
	/*enable timer*/
	TIM6->CNT = 0;
	TIM6->CR1 |= CR1_CEN;
}


void timer3_ch3_OutputCompare()
{

	RCC->AHBENR |= RCC_GPIOCEN;
	/*gpio C8 as alternate function mode*/
	GPIOC->MODER &= ~(1U<<16);
	GPIOC->MODER |= (1U<<17);
	/*Set C8 to alternate function 2 mode*/
	GPIOC->AFR[1] &= ~(1U<<0);
	GPIOC->AFR[1] &= ~(1U<<1);
	GPIOC->AFR[1] &= ~(1U<<2);
	GPIOC->AFR[1] &= ~(1U<<3);
	/*enable clock access to timer16 */
	RCC->APB1ENR |= TIMER3_EN;
	/*set prescalar value*/
	TIM3->PSC = 800 -1;
	/*set auto reload value*/
	TIM3->ARR = 10000 -1;

	/*set output compare toggle mode*/
	TIM3->CCMR2 |= OCTOGGLE;
	/*enable timer3 compare mode channel3  */
	TIM3->CCER |= CC3E;



	/*enable timer*/
	TIM3->CNT = 0;
	TIM3->CR1 |= CR1_CEN;
}
