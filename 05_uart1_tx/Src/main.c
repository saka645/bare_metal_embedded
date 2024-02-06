#include <stm32f0xx.h>

#define UART1EN			(1U<<14)
#define UART2EN			(1U<<17)
#define GPIOAEN			(1U<<17)
#define GPIOBEN			(1U<<18)
#define SYS_FREQ		8000000U//16000000
#define APB1_CLK		SYS_FREQ
#define UART_BAUDRATE	9600U
#define CR1_TE			(1U<<3)
#define UART_EN			(1U<<0)
#define SR_TXE			(1U<<7)

static void set_baudrate(USART_TypeDef *USARTTX, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);
void uart1_write(uint8_t ch);
void uart1_tx_init();

int main()
{
	uart1_tx_init();
	while(1)
	{
		uart1_write('S');
		for(int i=0; i<100000; i++);
	}
}

void uart1_tx_init()
{
	//enable clock to gpio//
	RCC->AHBENR |= GPIOBEN;
	//alternate fun mode//pb6
	GPIOB->MODER &= ~(1U<<12);
	GPIOB->MODER |= (1U<<13);
	//pb6 to alternate fun tx, af0
	GPIOB->AFR[0] &= ~(1<<24);
	GPIOB->AFR[0] &= ~(1<<25);
	GPIOB->AFR[0] &= ~(1<<26);
	GPIOB->AFR[0] &= ~(1<<27);
	//enable clock to uart1//
	RCC->APB2ENR |= UART1EN;
	//baud rate//
	set_baudrate(USART1, APB1_CLK, UART_BAUDRATE);
	//USART1->BRR = 80000/96;
	//program stop bits//
	//USART1->CR2 = 0x00;
	//configure transmit direction//
	USART1->CR1 = (CR1_TE|UART_EN);
	//enable uart module//
}
static void set_baudrate(USART_TypeDef *USARTTX, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTTX->BRR = compute_uart_div(PeriphClk, BaudRate);//0x340//1a1
}

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}

void uart1_write(uint8_t ch)
{

	//make sure transmit data reg is empty//
	//write transmit data to reg//
	while(!(USART1->ISR & SR_TXE));
	USART1->TDR = (ch&0xff);


}
