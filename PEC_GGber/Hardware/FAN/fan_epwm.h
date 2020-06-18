/*********************************************************************
* �ļ���: fan_epwm.h
* Copyright(c): 2020,SDC, All Rights Reserved
* �� ��: epwm�������ȵײ�����
* ��������:2020.6.18
* ������: GGber
* �޸ļ�¼:
**********************************************************************/

#ifndef HARDWARE_FAN_FAN_EPWM_H_
#define HARDWARE_FAN_FAN_EPWM_H_

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "stdint.h"
#include "system.h"
#include "epwm.h"

#define FAN_FRE     (20e3)  //����Ƶ��
#define FAN_DUTY    (70u)   //����ռ�ձ�


void fanEpwm_Init(void);
void fanControl(void);

#endif /* HARDWARE_FAN_FAN_EPWM_H_ */
