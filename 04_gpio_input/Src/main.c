#include <stm32f0xx.h>

#define GPIOCEN		(1<<19)
#define GPIOAEN		(1<<17)
#define PIN9		(1<<9)
#define LED_PIN		PIN9
#define PUSH_BUTTON	(1<<0)


int main()
{
	RCC->AHBENR |= GPIOCEN;//LED ON PORT C
	RCC->AHBENR |= GPIOAEN;//PUSH BUTTON ON PORT A
	/*MAKE LED(PC9) AS OUTPUT*/
	GPIOC->MODER |= (1<<18);
	GPIOC->MODER &= ~(1<<19);

	GPIOA->MODER &= ~(1<<0);//MAKE (PA0)SWITCH AS INPUT
	GPIOA->MODER &= ~(1<<1);
	while(1)
	{
		/*check if pa0 is pressed-active low*/
		if(GPIOA->IDR&PUSH_BUTTON)
			GPIOC->BSRR |= LED_PIN;
		else
			GPIOC->BSRR |= (1<<25);
	}
}
