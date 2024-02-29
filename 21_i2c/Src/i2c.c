/*
 * i2c.c
 *
 *  Created on: Feb 20, 2024
 *      Author: sanjay.kumar
 */

#include <stm32f0xx.h>
#define I2C_RCC_EN			(1U<<21)
#define GPIOB_EN			(1U<<18)
#define I2C_EN				(1U<<0)
#define PRESC_BIT_POS		28
#define SCLDEL_BIT_POS		20
#define SDADEL_BIT_POS		16
#define SCLH_BIT_POS		8
#define SCLL_BIT_POS		0

#define I2C_SR_BUSY			(1U<<15)
#define I2C_CR2_START		(1U<<13)
#define I2C_SR_ADDR			(1U<<3)
#define I2C_SR_TXE			(1U<<0)
#define I2C_SR_RXNE			(1U<<2)
#define I2C_CR2_NACK		(1U<<15)
#define I2C_CR2_STOP		(1U<<14)
//PB9=SDA, AF1, PB8=SCL, AF1
void I2C_Init(void)
{
	/*ENABLE ACCSEE TO GPIO B*/
	RCC->AHBENR |= GPIOB_EN;
	/*SET PB8 AND PB9 TO AF*/
	GPIOB->MODER &= ~(1<<16);
	GPIOB->MODER |= (1<<17);
	GPIOB->MODER &= ~(1<<18);
	GPIOB->MODER |= (1<<19);
	/*SET PB8 AND PB9 TO AF1*/
	GPIOB->AFR[1] |= (1<<0);
	GPIOB->AFR[1] |= (1<<4);
	/*SET PB8 AND PB9 TO OPEN DRAIN*/
	GPIOB->OTYPER |= (1<<8);
	GPIOB->OTYPER |= (1<<9);
	/*SET PB8 AND PB9 TO PULL UPS*/
	GPIOB->PUPDR |= (1<<16);
	GPIOB->PUPDR |= (1<<18);
	/*ENABLE I2C CLOCK*/
	RCC->APB1ENR |= I2C_RCC_EN;
	/*I2C RESET MODE*/
	/*I2C FREQ@8MHZ I2C CLK AND 100KHZ*/
	I2C1->TIMINGR |= (PRESC_BIT_POS<<0x1);
	I2C1->TIMINGR |= (SCLDEL_BIT_POS<<0x2);
	I2C1->TIMINGR |= (SDADEL_BIT_POS<<0x4);
	I2C1->TIMINGR |= (SCLH_BIT_POS<<0xF);
	I2C1->TIMINGR |= (SCLL_BIT_POS<<0x13);
	/*ENABLE I2C*/
}


void i2c1_read(char sadd, char madd, char *data)
{
	volatile int temp;
	/*wait till i2c is busy*/
	while(I2C1->ISR & I2C_SR_BUSY);
	I2C1->CR2 |= I2C_CR2_START;
	while(I2C1->ISR & I2C_SR_BUSY);

	/*SEND ADDRESS AND WAIT TILL IT GETS SENT*/
	I2C1->TXDR = sadd <<1;
	while(!(I2C1->ISR & I2C_SR_ADDR));
	//CLEAR ADDR

	/*SEND MEMORY ADDRESS*/
	I2C1->TXDR = madd <<1;
	while(!(I2C1->ISR & I2C_SR_TXE));//wait till data reg is empty

	/*GENERATE REPEATED START*/
	I2C1->CR2 |= I2C_CR2_START;
	while(I2C1->ISR & I2C_SR_BUSY);

	/*SEND ADDRESS+READ AND WAIT TILL IT GETS SENT*/
	I2C1->TXDR = (sadd <<1)|1;
	while(!(I2C1->ISR & I2C_SR_ADDR));

	//DISABLE ACK//
	I2C1->CR2 |= I2C_CR2_NACK;

	//GENERATE STOP CONDITION//
	I2C1->CR2 |= I2C_CR2_STOP;

	//WAIT TILL RXNE//
	while(!(I2C1->ISR & I2C_SR_RXNE));

	//read data//
	*data++ = I2C1->RXDR;
}
