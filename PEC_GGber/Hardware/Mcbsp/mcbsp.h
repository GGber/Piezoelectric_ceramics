/*********************************************************************
* �ļ���: mcbsp.h
* Copyright(c): 2020,SDC, All Rights Reserved
* �� ��: adas3022�����ļ�
* ��������:2020.6.18
* ������: GGber
* �޸ļ�¼:
**********************************************************************/

#ifndef HARDWARE_MCBSP_MCBSP_H_
#define HARDWARE_MCBSP_MCBSP_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "stdint.h"
#include "system.h"
#include "con_pid.h"
/*****************************************ADAD3022_�ײ���������*******************************************************************/

void McBSP_Init(void);
void McBSP_write(uint16_t dat);
void McBSP_write_no(uint16_t dat);
uint16_t Mcbsp_read(void);


/*****************************************ADAD3022_API�ӿڴ���*******************************************************************/

#define CFG_OVERWRITE           (0x8000)     //����ѡ��(0:���֣�1������)
/*ͨ��ѡ��*/
#define INX_0                   (0<<12)
#define INX_1                   (1<<12)
#define INX_2                   (2<<12)
#define INX_3                   (3<<12)
#define INX_4                   (4<<12)
#define INX_5                   (5<<12)
#define INX_6                   (6<<12)
#define INX_7                   (7<<12)
/*ͨ���ο�*/
#define COM_DIFF                (0<<11)
#define COM_COM                 (1<<11)
/*�ɱ������*/
#define PGIA_24V576             (0<<7)
#define PGIA_10V24              (1<<7)
#define PGIA_5V12               (2<<7)
#define PGIA_2V56               (3<<7)
#define PGIA_1V28               (4<<7)
#define PGIA_0V64               (5<<7)
#define NC                      (6<<7)
#define PGIA_20V48              (7<<7)
/*��������ͨ��*/
#define MUX_AUX                 (0<<6)
#define MUX_AFE                 (1<<6)
/*ͨ��������*/
#define SEQ_DISABLE                     (0<<4)
#define SEQ_UPDATE_DURING_BASIC         (1<<4)
#define SEQ_ADV                         (2<<4)
#define SEQ_BASIC                       (3<<4)
/*�¶ȴ�����EN*/
#define TEMP_ENABLE                     (0<<3)
#define TEMP_DISABLE                    (1<<3)
/*��׼��ѹԴѡ��*/
#define REFN_DISABLE                    (0<<2)
#define REFN_ENABLE                     (1<<2)
/*ת��ģʽѡ��*/
#define CMS_WRAP                        (0<<1)
#define CMS_NORMAL                      (1<<1)
/*MSBѡ��*/
#define CHPA_CHANGE                     (0)
#define CHPA_NORMAL                     (1)

struct SENSOR_VAL{

    float u;
    float i;
    int16_t signal;
};
typedef struct SENSOR_VAL SENSOR;
extern SENSOR adas_sensor_origin_data;//AD�ɼ�����ԭʼ����ȫ�ֱ���

void adas3022_Init(void);
void adas3022_ResetGpioInit(void);
void adas3022_StartWork(void);
void adas3022_WREG(uint16_t regVal);
void adas3022_StarCnv(void);
void adas3022_Reset(void);


#endif /* HARDWARE_MCBSP_MCBSP_H_ */
