/*
 * uart2.h
 *
 *  Created on: Jan 26, 2024
 *      Author: sanjay.kumar
 */

#ifndef UART2_H_
#define UART2_H_

#include <stm32f0xx.h>

void set_baudrate(USART_TypeDef *USARTTX, uint32_t PeriphClk, uint32_t BaudRate);
uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);
void uart2_write(uint8_t ch);
void uart2_tx_init();
char uart2_read(void);

#endif /* UART2_H_ */
