/*
 * tim.h
 *
 *  Created on: Jan 24, 2024
 *      Author: sanjay.kumar
 */

#ifndef TIM_H_
#define TIM_H_

#define UIF		 (1U<<0)
#define SR_CC1IF (1U<<0)
void timer6_init1Hz();
void timer15_ch1_OutputCompare();
void timer3_Pc6_InputCapture();
#endif /* TIM_H_ */
