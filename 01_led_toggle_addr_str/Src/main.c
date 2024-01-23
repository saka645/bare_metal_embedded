#include <stdint.h>

#define PERIPH_BASE			(0x40000000UL)
#define AHB1PERIPH_OFFSET	(0x00020000UL)
#define AHB1PERIPH_BASE		(PERIPH_BASE+AHB1PERIPH_OFFSET)
#define AHB2PERIPH_OFFSET	(0x08000000UL)
#define AHB2PERIPH_BASE		(PERIPH_BASE+AHB2PERIPH_OFFSET)
#define RCC_OFFSET			(0X1000UL)
#define RCC_BASE			(AHB1PERIPH_BASE+RCC_OFFSET)
#define GPIOA_OFFSET		(0X00UL)
#define GPIOA_BASE			(AHB2PERIPH_BASE+GPIOA_OFFSET)
#define GPIOC_OFFSET		(0x800UL)
#define GPIOC_BASE			(AHB2PERIPH_BASE+GPIOC_OFFSET)

#define GPIOCEN				(1U<<19)
#define LED3_PIN			(1U<<9)

#define __IO volatile

typedef struct
{
	__IO uint32_t MODER;
	__IO uint32_t OTYPER;
	__IO uint32_t OSPEEDR;
	__IO uint32_t PUPDR;
	__IO uint32_t IDR;
	__IO uint32_t ODR;
}GPIO_TypeDef;

typedef struct
{
	volatile uint32_t dummy[5];
	volatile uint32_t AHBENR;
}RCC_TypeDef;

#define RCC 		((RCC_TypeDef*)RCC_BASE)
#define GPIOC 		((GPIO_TypeDef*)GPIOC_BASE)

int main()
{
	/*enable clock*/
	RCC->AHBENR |= GPIOCEN;
	/*set pc9 as output*/
	GPIOC->MODER |= (0X01<<18);
	GPIOC->MODER &= ~(0X01<<19);
	while(1)
	{
		/*toggle pc9*/
		//GPIOC_ODR_R ^= LED3_PIN;
		GPIOC->ODR ^= LED3_PIN;
		for(int i=0; i<100000; i++);
	}
	return 0;
}


