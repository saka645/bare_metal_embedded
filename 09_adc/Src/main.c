#include <stm32f0xx.h>
#include <stdio.h>
#include "adc.h"
#include "uart2.h"

uint32_t sensor_value = 0;

int main()
{
	uart2_tx_init();
	pa0_adc_init();
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

/*
#include "stm32f0xx.h"

volatile uint16_t adc_value;

void delay_ms(uint32_t ms) {
    volatile uint32_t i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 4000; j++) {}  // Adjust this loop for your clock frequency
}

void init_adc() {
    // Enable GPIOA clock
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // Configure PA0 as analog input
    GPIOA->MODER |= GPIO_MODER_MODER0;

    // Enable ADC1 clock
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    // Set ADC clock to PCLK/4 (Assuming PCLK is HSI, adjust if necessary)
    //ADC1->CFGR2 |= ADC_CFGR2_CKMODE_0;

    // Configure ADC1: 12-bit resolution, right-aligned data, single conversion mode
//    ADC1->CFGR1 &= ~ADC_CFGR1_ALIGN;
//    ADC1->CFGR1 &= ~ADC_CFGR1_CONT;  // Single conversion mode

    // Select the channel to be converted (PA0)
    ADC1->CHSELR |= ADC_CHSELR_CHSEL0;

    // Enable the ADC
    ADC1->CR |= ADC_CR_ADEN;

    // Wait for ADC to be ready
    while (!(ADC1->ISR & ADC_ISR_ADRDY)) {}

    // Calibrate the ADC
//    ADC1->CR |= ADC_CR_ADCAL;
//    while (ADC1->CR & ADC_CR_ADCAL) {}
}

uint16_t read_adc() {
    // Start a conversion
    ADC1->CR |= ADC_CR_ADSTART;

    // Wait for the end of conversion
    while (!(ADC1->ISR & ADC_ISR_EOC)) {}

    // Read the converted value
    return ADC1->DR;
}

int main(void) {
    init_adc();

    while (1) {
        adc_value = read_adc();
        // Process the ADC value as needed
        delay_ms(1000);
    }
}

*/
