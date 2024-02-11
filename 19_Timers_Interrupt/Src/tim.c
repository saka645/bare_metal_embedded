/*
 * tim.c
 *
 *  Created on: Jan 24, 2024
 *      Author: sanjay.kumar
 */

#include <stm32f0xx.h>

#define TIMER6_EN			(1U<<4)
#define CR1_CEN				(1U<<0)
#define DIER_UI				(1U<<0)

void timer6_init1Hz()
{
	/*enable clock access to timer6/*	 */
	RCC->APB1ENR |= TIMER6_EN;
	/*set prescalar value*/
	TIM6->PSC = 800 -1;
	/*set auto reload value*/
	TIM6->ARR = 10000 -1;
	/*enable timer*/
	TIM6->CNT = 0;
	TIM6->CR1 |= CR1_CEN;
}

void timer6_init1HzInterrupt()
{
	/*enable clock access to timer6/*	 */
	RCC->APB1ENR |= TIMER6_EN;
	/*set prescalar value*/
	TIM6->PSC = 800 -1;
	/*set auto reload value*/
	TIM6->ARR = 10000 -1;
	/*enable timer*/
	TIM6->CNT = 0;
	TIM6->CR1 |= CR1_CEN;

	/*enable timer interrupt*/
	TIM6->DIER |= DIER_UI;
	/*enable timer interrupt in nvic*/
	NVIC_EnableIRQ(TIM6_IRQn);
}
