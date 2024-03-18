#include <stm32f0xx.h>
#include <stdio.h>
#include <uart1.h>

#define GPIOCEN		(1<<19)
#define PIN9		(1<<9)
#define LED_PIN		PIN9

static void uart_callback();

char read_char=0;
int main()
{
	char msg[30]="hello please enter A\n";
	RCC->AHBENR |= GPIOCEN;
	GPIOC->MODER |= (1<<18);
	GPIOC->MODER &= ~(1<<19);
	uart1_tx_init();
	dma_init((uint32_t)msg,(uint32_t)&USART1->TDR,30);
	//printf("hello please enter A\n");
	while(1)
	{
		//read_char = uart1_read();

	}
}
static void uart_callback()
{
	GPIOC->ODR ^= LED_PIN;
}
void DMA1_CH2_3_IRQHandler(void)
{
	if(DMA1->ISR & DMA_TCIF2)
	{
		DMA1->ISR |= DMA_HTIF2;
		uart_callback();
	}
}
