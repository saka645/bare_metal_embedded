/*
 * exti.c
 *
 *  Created on: Feb 4, 2024
 *      Author: sanjay.kumar
 */
#include "exti.h"

#define GPIOBEN		(1<<18)
#define SYSCONFIG	(1<<0)
#define EXTIPORTB1 	(1<<4)

void pb1_exti_init(void)
{
	//disable global interrupts
	__disable_irq();
	//enable clock for gpio b
	RCC->AHBENR |= GPIOBEN;
	//enable clock access to sysconfig
	RCC->APB2ENR |= SYSCONFIG;
	//set pb1 as input pin
	GPIOB->MODER &= ~(1<<26);
	GPIOB->MODER &= ~(1<<27);
	//select pb1 connected to exti1
	SYSCFG->EXTICR[0] |= (1<<EXTIPORTB1);
	//unmask exti1
	EXTI->IMR |= (1<<1);
	//select falling edge trigger
	EXTI->FTSR |= (1<<1);
	//enable exti line in nvic
	NVIC_EnableIRQ(EXTI0_1_IRQn);
	//enable global interrupt
	__enable_irq();
}

