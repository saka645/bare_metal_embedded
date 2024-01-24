/*
 * adc.c
 *
 *  Created on: Jan 22, 2024
 *      Author: sanjay.kumar
 */

#include <stm32f0xx.h>
#include "adc.h"

#define ADC1_EN			(1U<<9)
#define GPIOA_EN		(1U<<16)
#define ADC_EN			(1U<<0)
#define ADC_START		(1U<<4)
#define ADC_SR_EOC		(1U<<2)
#define ADC1_CH1		(1U<<1)
#define ADC_CFGR1_CONT	(1U<<13)

void pa1_adc_init(void)
{
	/* configure adc gpio pin */

	/* enable clock access to gpioa */
	RCC->AHBENR |= GPIOA_EN;
	/* set pa1 mode to analog */
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);
	/*configure adc module */
	ADC1->CHSELR |= ADC1_CH1;
	/* enable clock access to adc */
	RCC->APB2ENR |= ADC1_EN;
	/* configure adc parameters */

	ADC1->CR |= ADC_EN;

}

void start_conversion(void)
{
	/*ENABLE CONT CONV*/
	ADC1->CFGR1 |= ADC_CFGR1_CONT;
	ADC1->CR |= ADC_START;
}

uint32_t adc_read(void)
{
	/*wait for conversion to finish*/
	while(!(ADC1->ISR & ADC_SR_EOC));
	/*read data */
	return ADC1->DR;
}
