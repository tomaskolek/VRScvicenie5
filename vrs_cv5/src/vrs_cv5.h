/*
 * vrs_cv5.h
 *
 *  Created on: 18. 10. 2016
 *      Author: tomas
 */

#ifndef VRS_CV5_H_
#define VRS_CV5_H_


int pom;
char data;

void adc_init(void);
void nvic_init();
void usart_init();
void blikamLEDku(volatile int);
//void ADC1_IRQHandler(void);
void gpio_init();
void USART2_IRQHandler();
void posli_znak(char znak[]);

#endif /* VRS_CV5_H_ */


