/*********************************************************************
* �ļ���: con_pid.h
* Copyright(c): 2020,SDC, All Rights Reserved
* �� ��: ����ϵͳpid����
* ��������:2020.6.18
* ������: GGber
* �޸ļ�¼:
**********************************************************************/

#ifndef HARDWARE_PID_CON_PID_H_
#define HARDWARE_PID_CON_PID_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "stdint.h"
#include "system.h"
#include "epwm.h"
#include "mcbsp.h"

#define OUTPUT_GAIN_LOOP    1     //��������ģʽ
#define SPWM_OUTPUT         0     //SPWMģʽ

#define ADAS_FREE           2u     //ADAS����
#define ADAS_OK             1u     //ת���ɹ�
#define ADAS_ERROR          0u     //ת��ʧ��

extern uint16_t adasFlag;         //SIGNALת����־

#endif /* HARDWARE_PID_CON_PID_H_ */
