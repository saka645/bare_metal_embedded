#include <stm32f0xx.h>
#include <stdio.h>
#define UART2EN			(1U<<17)
#define GPIOAEN			(1U<<17)
#define SYS_FREQ		8000000U//16000000
#define APB1_CLK		SYS_FREQ
#define UART_BAUDRATE	9600U
#define CR1_TE			(1U<<3)
#define UART_EN			(1U<<0)
#define SR_TXE			(1U<<7)

static void set_baudrate(USART_TypeDef *USARTTX, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);
void uart2_write(uint8_t ch);
void uart2_tx_init();
int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}
int main()
{
	uart2_tx_init();
	while(1)
	{
		puts("Hello\n");
		for(int i=0; i<100000; i++);
	}
}

void uart2_tx_init()
{
	//RCC->CR = 0x3004e83U;
	//enable clock to gpio//
	RCC->AHBENR |= GPIOAEN;
	//alternate fun mode//
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);
	/*gpio speed high*/
	GPIOA->OSPEEDR |= (1U<<4);
	GPIOA->OSPEEDR |= (1U<<5);
	//pa2 to alternate fun tx, af1
	GPIOA->AFR[0] |= (1<<8);
	GPIOA->AFR[0] &= ~(1<<9);
	GPIOA->AFR[0] &= ~(1<<10);
	GPIOA->AFR[0] &= ~(1<<11);
	//enable clock to uart2//
	RCC->APB1ENR |= UART2EN;

	RCC->APB2ENR |= (1U<<0);
	RCC->APB1ENR |= (1U<<28);
	//baud rate//
	set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);
	//USART2->BRR = SYS_FREQ/UART_BAUDRATE;
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
	//make sure transmit data reg is empty//
	//write transmit data to reg//
	while(!(USART2->ISR & SR_TXE));
	USART2->TDR = (ch&0xff);
}
