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
#define RCC_AHBENR_OFFSET	(0X14UL)
#define RCC_AHBENR_R		(*(volatile unsigned int *)(RCC_BASE+RCC_AHBENR_OFFSET))

#define MODER_OFFSET		(0x00UL)
#define GPIOC_MODER_R		(*(volatile unsigned int *)(GPIOC_BASE+MODER_OFFSET))

//#define MODER9_OFFSET		(18U)
#define ODR_OFFSET			(0x14UL)
#define GPIOC_ODR_R			(*(volatile unsigned int *)(GPIOC_BASE+ODR_OFFSET))

#define GPIOx_OTYPER_BASE  	(0x04UL)
#define GPIOx_OTYPER_R		(*(volatile unsigned int *)(GPIOC_BASE+GPIOx_OTYPER_BASE))

#define GPIOx_PUPDR_BASE  	(0x0CUL)
#define GPIOx_PUPDR_R		(*(volatile unsigned int *)(GPIOC_BASE+GPIOx_PUPDR_BASE))

#define GPIOCEN				(1U<<19)
#define LED3_PIN			(1U<<9)



int main()
{
	/*enable clock*/
	RCC_AHBENR_R |= GPIOCEN;
	/*enable push pull mode*/
	GPIOx_OTYPER_R &= ~LED3_PIN;
	/*enable pullup*/
	GPIOx_PUPDR_R |= (0X01<<18);
	GPIOx_PUPDR_R &= ~(0X01<<19);
	/*set pc9 as output*/
	GPIOC_MODER_R |= (0X01<<18);
	GPIOC_MODER_R &= ~(0X01<<19);
	while(1)
	{
		/*toggle pc9*/
		GPIOC_ODR_R ^= LED3_PIN;
		for(int i=0; i<100000; i++);
	}
	return 0;
}


