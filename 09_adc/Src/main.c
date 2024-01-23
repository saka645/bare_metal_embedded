#include <stm32f0xx.h>
#include <stdio.h>
#include "adc.h"

#define UART2EN			(1U<<17)
#define GPIOAEN			(1U<<17)
#define SYS_FREQ		48000000U//16000000
#define APB1_CLK		SYS_FREQ
#define UART_BAUDRATE	9600U
#define CR1_TE			(1U<<3)
#define CR1_RE			(1U<<2)
#define UART_EN			(1U<<0)
#define SR_TXE			(1U<<7)
#define SR_RXNE			(1U<<5)

static void set_baudrate(USART_TypeDef *USARTTX, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);
void uart2_write(uint8_t ch);
void uart2_tx_init();
char uart2_read(void);

uint32_t sensor_value = 0;

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}
int main()
{
	uart2_tx_init();
	pa1_adc_init();
	//start_conversion();
	while(1)
	{
		start_conversion();
		sensor_value = adc_read();
		//uart2_write("Hello\n");
		printf("sensor value=%d\n",(int)sensor_value);
		for(int i=0; i<100000; i++);
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

	/*PA3 AS ALTERNATE FUN*/
	//alternate fun mode RX//
	GPIOA->MODER &= ~(1U<<6);
	GPIOA->MODER |= (1U<<7);
	//pa2 to alternate fun tx, af1
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
	USART2->CR2 = 0x00;
	//configure transmit direction//
	USART2->CR1 = (CR1_TE | CR1_RE);
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

char uart2_read(void)
{
	while(!(USART2->ISR & SR_RXNE));
	return USART2->RDR;
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
