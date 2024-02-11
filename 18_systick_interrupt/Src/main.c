#include <stm32f0xx.h>
#include <stdio.h>
#include "systick.h"

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

int main()
{
	RCC->AHBENR |= GPIOCEN;
	GPIOC->MODER |= (1<<18);
	GPIOC->MODER &= ~(1<<19);
	systick1HzInterruptInit();
	while(1)
	{

	}
}
static void systick_handler()
{
	GPIOC->ODR ^= LED_PIN;
}

void SysTick_Handler(void)
{
	systick_handler();
}
