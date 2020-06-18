/*********************************************************************
* �ļ���: dap_adc.h
* Copyright(c): 2020,SDC, All Rights Reserved
* �� ��: DSP�ڲ�adc�ײ�����
* ��������:2020.6.18
* ������: GGber
* �޸ļ�¼:
**********************************************************************/

#ifndef HARDWARE_DSP_ADC_DSP_ADC_H_
#define HARDWARE_DSP_ADC_DSP_ADC_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "system.h"

extern uint16_t adc_val[2];

void ADC_Init(void);
void ADC_StarCnv(void);
void ADC_getValue(void);

#endif /* HARDWARE_DSP_ADC_DSP_ADC_H_ */
