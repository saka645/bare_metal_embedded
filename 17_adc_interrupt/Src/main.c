#include <stm32f0xx.h>
#include <stdio.h>
#include "adc.h"


uint32_t sensor_value = 0;

int main()
{
	pa0_adc_interrupt_init();
	start_conversion();
	while(1)
	{

	}
}




static void Adc_Callback()
{
	sensor_value = ADC1->DR;
}
void ADC_IRQHandler(void)
{
	//check for eoc in status reg
	if(ADC1->ISR & ADC_SR_RDY)
	{
		//CLEAR interrupt
		ADC1->ISR &= ~ADC_SR_RDY;
		Adc_Callback();
	}
}
