#include <stm32f0xx.h>
#include <stdio.h>
#include "exti.h"
#define GPIOCEN		(1<<19)
#define PIN9		(1<<9)
#define LED_PIN		PIN9


int main()
{
	RCC->AHBENR |= GPIOCEN;
	GPIOC->MODER |= (1<<18);
	GPIOC->MODER &= ~(1<<19);
	pb1_exti_init();
	while(1)
	{
	}
}

static void exti_callback(void)
{
	GPIOC->ODR ^= LED_PIN;
}
void EXTI0_1_IRQHandler(void)
{
	if(EXTI->PR & LINE1)
	{
		EXTI->PR |= LINE1;
		exti_callback();
	}
}
