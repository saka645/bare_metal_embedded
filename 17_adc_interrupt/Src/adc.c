/*
 * adc.c
 *
 *  Created on: Jan 22, 2024
 *      Author: sanjay.kumar
 */

#include <stm32f0xx.h>
#include "adc.h"

#define ADC1_EN			(1U<<9)
#define GPIOA_EN		(1U<<17)
#define ADC_EN			(1U<<0)
#define ADC_START		(1U<<2)
#define ADC_SR_EOC		(1U<<2)
#define ADC1_CH0		(1U<<0)



void pa0_adc_interrupt_init(void)
{
	/* configure adc gpio pin */

	/* enable clock access to gpioa */
	RCC->AHBENR |= GPIOA_EN;
	/* set pa0 mode to analog */
	GPIOA->MODER |= (1U<<0);
	GPIOA->MODER |= (1U<<1);
	/* enable clock access to adc */
	RCC->APB2ENR |= ADC1_EN;
	/*Enable adc eoc interrupt */
	ADC1->IER |= ADC_SR_EOC_IE;
	/*enable nvic adc */
	NVIC_EnableIRQ(ADC1_IRQn);
	/*configure adc module */
	ADC1->CHSELR |= ADC1_CH0;

	/* configure adc parameters */

    // Configure ADC1: 12-bit resolution, right-aligned data, single conversion mode
    ADC1->CFGR1 &= ~ADC_CFGR1_ALIGN;
    ADC1->CFGR1 &= ~ADC_CFGR1_CONT;



	ADC1->CR |= ADC_EN;

	//ADC->CCR |= ADC_CCR_VREFEN;
	while (!(ADC1->ISR & ADC_ISR_ADRDY)) {}

}

void pa0_adc_init(void)
{
	/* configure adc gpio pin */

	/* enable clock access to gpioa */
	RCC->AHBENR |= GPIOA_EN;
	/* set pa0 mode to analog */
	GPIOA->MODER |= (1U<<0);
	GPIOA->MODER |= (1U<<1);
	/* enable clock access to adc */
	RCC->APB2ENR |= ADC1_EN;
	start_conversion();
	/*configure adc module */
	ADC1->CHSELR |= ADC1_CH0;

	/* configure adc parameters */

    // Configure ADC1: 12-bit resolution, right-aligned data, single conversion mode
    ADC1->CFGR1 &= ~ADC_CFGR1_ALIGN;
    ADC1->CFGR1 &= ~ADC_CFGR1_CONT;



	ADC1->CR |= ADC_EN;

	//ADC->CCR |= ADC_CCR_VREFEN;
	while (!(ADC1->ISR & ADC_ISR_ADRDY)) {}

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
