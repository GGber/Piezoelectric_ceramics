/*********************************************************************
* �ļ���: system.h
* Copyright(c): 2020,SDC, All Rights Reserved
* �� ��: ϵͳ����ͷ�ļ�
* ��������:2020.6.18
* ������: GGber
* �޸ļ�¼:
**********************************************************************/

#ifndef HARDWARE_SYSTEM_SYSTEM_H_
#define HARDWARE_SYSTEM_SYSTEM_H_

#ifdef __cplusplus
extern "C"
{
#endif

//ͷ�ļ���������
#include <stdint.h>
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define RUN_IN_FLASH  1          // 1�����FLASH���У���������Ƶ�RAM������,��������ٶ�;

#define delay_us(us)    DELAY_US(us)    // us�����ʱ����

void sys_init();
void delay_ms(uint16_t ms);             // ms�����ʱ����

extern uint16_t led_Task_Count;

#ifdef __cplusplus
}
#endif


#endif /* HARDWARE_SYSTEM_SYSTEM_H_ */
