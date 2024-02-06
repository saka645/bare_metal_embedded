/*
 * tim.c
 *
 *  Created on: Jan 24, 2024
 *      Author: sanjay.kumar
 */

#include <stm32f0xx.h>

#define TIMER15_EN			(1U<<16)
#define TIMER6_EN			(1U<<4)
#define CR1_CEN				(1U<<0)
#define OCTOGGLE			((1U<<4) | (1U<<5))
#define CC1E				(1U<<0)
#define RCC_GPIOAEN			(1U<<17)

#define RCC_GPIOCEN			(1U<<19)
#define TIMER3_EN			(1U<<1)
#define CCR1_CC1S			(1U<<0)
#define CCER_CC1E			(1U<<0)

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


void timer15_ch1_OutputCompare()
{
	//PA2
	RCC->AHBENR |= RCC_GPIOAEN;
	/*gpio PA2 as alternate function mode*/
	GPIOC->MODER &= ~(1U<<4);
	GPIOC->MODER |= (1U<<5);
	/*Set PA2 to alternate function 2 mode*/
	GPIOC->AFR[0] &= ~(1U<<8);
	GPIOC->AFR[0] &= ~(1U<<9);
	GPIOC->AFR[0] &= ~(1U<<10);
	GPIOC->AFR[0] &= ~(1U<<11);
	/*enable clock access to timer15 */
	RCC->APB2ENR |= TIMER15_EN;
	/*set prescalar value*/
	TIM15->PSC = 800 -1;
	/*set auto reload value*/
	TIM15->ARR = 10000 -1;

	/*set output compare toggle mode*/
	TIM15->CCMR1 |= OCTOGGLE;//OC1M
	/*enable timer3 compare mode channel1  */
	TIM15->CCER |= CC1E;

	/*enable timer*/
	TIM15->CNT = 0;
	TIM15->CR1 |= CR1_CEN;
}

void timer3_Pc6_InputCapture()
{
	/*clock to gpio c timer pin*/
	RCC->AHBENR |= RCC_GPIOCEN;
	/*gpio C6 as alternate function mode*/
	GPIOC->MODER &= ~(1U<<12);
	GPIOC->MODER |= (1U<<13);
	/*GPIO c6 as alternate function mode 0*/
	GPIOB->AFR[0] &= ~(1U<<24);
	GPIOB->AFR[0] &= ~(1U<<25);
	GPIOB->AFR[0] &= ~(1U<<26);
	GPIOB->AFR[0] &= ~(1U<<27);
	/*enable clock access to timer3 */
	RCC->APB1ENR |=TIMER3_EN;
	/*set prescalar*/
	TIM3->PSC = 8000 -1;
	/*set channel 1 input capture at every edge*/
	TIM3->CCMR1 |= CCR1_CC1S;
	/*capture at rising edge*/
	TIM3->CCER |= CCR1_CC1S;
	/*enable timer 3*/
	TIM3->CR1 |= CR1_CEN;
}
