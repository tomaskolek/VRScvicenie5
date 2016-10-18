/*
 * vrs_cv.c
 *
 *  Created on: 18. 10. 2016
 *      Author: tomas
 */
#include "vrs_cv5.h"

void adc_init(void)			// inicalizujem ADC a GPIO
  {
  	GPIO_InitTypeDef GPIO_InitStructure;
  	ADC_InitTypeDef ADC_InitStructure;

  	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  	// LEDka//
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  	////
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
  	RCC_HSICmd(ENABLE);
  	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  	ADC_StructInit(&ADC_InitStructure);
  	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  	ADC_InitStructure.ADC_NbrOfConversion = 1;
  	ADC_Init(ADC1, &ADC_InitStructure);
  	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_16Cycles);
  	ADC_Cmd(ADC1, ENABLE);
  	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET){}
  	ADC_SoftwareStartConv(ADC1);
// dtruktura prerusenia //////////////////////////////////
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  	NVIC_InitTypeDef NVIC_InitStructure;
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);

  }

