#include <stm32f0xx.h>
#include <stdio.h>
#include "tim.h"

#define UART2EN			(1U<<17)
#define GPIOAEN			(1U<<17)
#define SYS_FREQ		8000000U//16000000
#define APB1_CLK		SYS_FREQ
#define UART_BAUDRATE	9600U
#define CR1_TE			(1U<<3)
#define UART_EN			(1U<<0)
#define SR_TXE			(1U<<7)

#define GPIOCEN		(1<<19)
#define PIN9		(1<<9)
#define LED_PIN		PIN9

static void set_baudrate(USART_TypeDef *USARTTX, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);
void uart2_write(uint8_t ch);
void uart2_tx_init();

uint32_t sensor_value = 0;

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}
int count=0;
int main()
{
	RCC->AHBENR |= GPIOCEN;
	GPIOC->MODER |= (1<<18);
	GPIOC->MODER &= ~(1<<19);
	timer6_init1Hz();
	uart2_tx_init();
	while(1)
	{
		while(!(TIM6->SR & UIF));
		TIM6->SR &= ~UIF;
		GPIOC->ODR ^= LED_PIN;
		count++;
		printf("count=%d\n",count);
	}
}

void uart2_tx_init()
{
	//enable clock to gpio//
	RCC->AHBENR |= GPIOAEN;
	//alternate fun mode//
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);
	//pa2 to alternate fun tx, af1
	GPIOA->AFR[0] |= (1<<8);
	GPIOA->AFR[0] &= ~(1<<9);
	GPIOA->AFR[0] &= ~(1<<10);
	GPIOA->AFR[0] &= ~(1<<11);
	//enable clock to uart2//
	RCC->APB1ENR |= UART2EN;
	//baud rate//
	set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);
	//USART2->BRR = 0x1388;
	//program stop bits//
	USART2->CR2 = 0x00;
	//configure transmit direction//
	USART2->CR1 = CR1_TE;
	//enable uart module//
	USART2->CR1 |= UART_EN;
}
static void set_baudrate(USART_TypeDef *USARTTX, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTTX->BRR = compute_uart_div(PeriphClk, BaudRate);//0x340//1a1
}

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}

void uart2_write(uint8_t ch)
{
	//while(*ch)
	{
	//make sure transmit data reg is empty//
	//write transmit data to reg//
	while(!(USART2->ISR & SR_TXE));
	USART2->TDR = (ch&0xff);
	//for(int i=0; i<1000; i++);
	//ch++;
	}
}
