/*
 * adc.h
 *
 *  Created on: Jan 22, 2024
 *      Author: sanjay.kumar
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

#define ADC_SR_EOC_IE	(1U<<2)
#define ADC_SR_RDY		(1U<<0)

void pa0_adc_init(void);
void start_conversion(void);
uint32_t adc_read(void);
void pa0_adc_interrupt_init(void);
#endif /* ADC_H_ */
