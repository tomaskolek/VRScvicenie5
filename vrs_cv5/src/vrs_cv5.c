/*
 * vrs_cv.c
 *
 *  Created on: 18. 10. 2016
 *      Author: tomas
 */
#include "vrs_cv5.h"
#include <stddef.h>
#include "stm32l1xx.h"

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
  }

void NVIC_init(){
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  	NVIC_InitTypeDef NVIC_struktura;
  	NVIC_struktura.NVIC_IRQChannel = ADC1_IRQn;
  	NVIC_struktura.NVIC_IRQChannelPreemptionPriority = 1;
  	NVIC_struktura.NVIC_IRQChannelSubPriority = 0;
  	NVIC_struktura.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_struktura);
  	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
  	ADC_ITConfig(ADC1, ADC_IT_OVR, ENABLE);
}

void USART_init(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_InitTypeDef USART_struktura;
	USART_struktura.USART_BaudRate = 9600;
	USART_struktura.USART_WordLength = USART_WordLength_8b;
	USART_struktura.USART_StopBits = USART_StopBits_1;
	USART_struktura.USART_Parity = USART_Parity_No;
	USART_struktura.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_struktura.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_struktura);
}

void ADC1_IRQHandler(){
	uint16_t AD_value;
	ADC_SoftwareStartConv(ADC1);
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)){}
	AD_value=ADC_GetConversionValue(ADC1);

	if ((AD_value >= 1980) && (AD_value <= 2100)){
		blikamLEDku(1);
	}
	else if ((AD_value >= 2800) && (AD_value <= 2940)){
		blikamLEDku(2);
	}
	else if ((AD_value >= 3440) && (AD_value <= 3480)){
		blikamLEDku(3);
	}
	else if ((AD_value >= 3640) && (AD_value <= 3680)){
		blikamLEDku(4);
	}
	else if ((AD_value >= 3900)){
		blikamLEDku(0);
	}
}


void blikamLEDku(int tlacitko){
	int i, j;
	if (tlacitko == 0){
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	}
	else if (tlacitko == 1){
		GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
		for (i = 1; i <= 200; i++){
			for (j = 1; j <= 200; j++){
				}
		}
	}
	else if (tlacitko == 2){
		GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
		for (i = 1; i <= 400; i++){
			for (j = 1; j <= 400; j++){
				}
		}
	}
	else if (tlacitko == 3){
		GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
		for (i = 1; i <= 700; i++){
			for (j = 1; j <= 700; j++){
				}
		}
	}
	else if (tlacitko == 4){
		GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
		for (i = 1; i <= 1000; i++){
			for (j = 1; j <= 1000; j++){
			}
		}
	}
}
