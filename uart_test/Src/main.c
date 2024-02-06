#include "stm32f0xx.h"

#define SystemCoreClock 48000000

void delay_ms(uint32_t ms) {
    volatile uint32_t i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 4000; j++) {}  // Adjust this loop for your clock frequency
}

void init_uart() {
    // Enable GPIOA clock
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // Configure PA2 (TX) as alternate function (AF1) and PA3 (RX) as input
    GPIOA->MODER |= GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1;
    GPIOA->AFR[0] |= (1 << (2 * 4)) | (1 << (3 * 4));

    // Enable USART2 clock
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    // Configure USART1: 115200 baud, 8 data bits, 1 stop bit, no parity
    USART2->BRR = SystemCoreClock / 115200;
    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

void send_char(char c) {
    // Wait until the transmit data register is empty
    while (!(USART2->ISR & USART_ISR_TXE)) {}
    // Send the character
    USART2->TDR = c;
}

int main(void) {
    init_uart();

    while (1) {
        send_char('H');
        send_char('i');
        send_char('\r');
        send_char('\n');
        delay_ms(1000);
    }
}
