/*
 * uart2.c
 *
 *  Created on: Jan 26, 2024
 *      Author: sanjay.kumar
 */
#include <uart2.h>

#define UART2EN			(1U<<17)
#define GPIOAEN			(1U<<17)
#define SYS_FREQ		8000000U//16000000
#define APB1_CLK		SYS_FREQ
#define UART_BAUDRATE	9600U
#define CR1_TE			(1U<<3)
#define CR1_RE			(1U<<2)
#define UART_EN			(1U<<0)
#define SR_TXE			(1U<<7)
#define SR_RXNE			(1U<<5)

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}


void uart2_tx_init()
{
	//enable clock to gpio//
	RCC->AHBENR |= GPIOAEN;
	//alternate fun mode//
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);
	/*PA3 AS ALTERNATE FUN*/
	//alternate fun mode RX//
	GPIOA->MODER &= ~(1U<<6);
	GPIOA->MODER |= (1U<<7);
	//pa2 to alternate fun tx, af1
	GPIOA->AFR[0] |= (1<<8);
	GPIOA->AFR[0] &= ~(1<<9);
	GPIOA->AFR[0] &= ~(1<<10);
	GPIOA->AFR[0] &= ~(1<<11);
	//pa3 to alternate fun rx, af1
	GPIOA->AFR[0] |= (1<<12);
	GPIOA->AFR[0] &= ~(1<<13);
	GPIOA->AFR[0] &= ~(1<<14);
	GPIOA->AFR[0] &= ~(1<<15);


	//enable clock to uart2//
	RCC->APB1ENR |= UART2EN;
	//baud rate//
	set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);
	//USART2->BRR = 0x1388;
	//program stop bits//
	//USART2->CR2 = 0x00;
	//configure transmit direction//
	USART2->CR1 = (CR1_TE | CR1_RE | UART_EN);
	//enable uart module//
}
void set_baudrate(USART_TypeDef *USARTTX, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTTX->BRR = compute_uart_div(PeriphClk, BaudRate);//0x340//1a1
}

uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}

char uart2_read(void)
{
	while(!(USART2->ISR & SR_RXNE));
	return USART2->RDR;
}
void uart2_write(uint8_t ch)
{
	while(!(USART2->ISR & SR_TXE));
	USART2->TDR = (ch&0xff);
}
