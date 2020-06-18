/*********************************************************************
* 文件名: dap_adc.h
* Copyright(c): 2020,SDC, All Rights Reserved
* 描 述: DSP内部adc底层驱动
* 创建日期:2020.6.18
* 创建人: GGber
* 修改记录:
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
