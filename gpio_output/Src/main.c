#include <stm32f0xx.h>

#define GPIOCEN		(1<<19)
#define PIN9		(1<<9)
#define LED_PIN		PIN9


int main()
{
	RCC->AHBENR |= GPIOCEN;
	GPIOC->MODER |= (1<<18);
	GPIOC->MODER &= ~(1<<19);
	while(1)
	{
		GPIOC->ODR ^= LED_PIN;
		for(int i=0; i<200000; i++);
	}
}
