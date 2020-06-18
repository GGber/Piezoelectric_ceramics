/*********************************************************************
* �ļ���: epwm.h
* Copyright(c): 2020,SDC, All Rights Reserved
* �� ��: epwm����mos�ܵײ�����
* ��������:2020.6.18
* ������: GGber
* �޸ļ�¼:
**********************************************************************/
#ifndef HARDWARE_EPWM_EPWM_H_
#define HARDWARE_EPWM_EPWM_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "stdint.h"
#include "system.h"

/*����pwmƵ��100kHZ*/
#define EPWM_FRE  (100e3)
/*������������*/
#define PHSA_3    (0)
#define PHSA_4    (90)  //�����޸�90->180
#define PHSA_5    (180)
#define PHSA_6    (90)
/*����ʱ��*/
#define DEAD_TIME (200)
/*��ʼ��ռ�ձ�*/
#define INIT_DUTY (50)

/*EPWM�ο�ֵ�궨��*/
#define ARRAY_MOUNT_VALUE      ( 256u )         // SPWM���ɵ����������  ע��  DDS�����Ĳ����У�ȡ32λ�ۼ����ĸ�8λ��Ϊ��Чֵ
#define LOSE_RANGE_VALUE       ( 0.1f )         // ��ʧռ�ձȣ����Ϊ(1-2*LoseRangeValue)*sin(wt)
#define DDS_FREOUT             ( 500u )         // Sine���Ҳ����Ƶ�ʳ�ʼ��
#define COS_ARRAY_MAX          ( 2000u)         // ���е������ܳ��ȣ����ܴ���cmd�ļ������õ�.ebss����Ĵ�С

/*EPWM�������ýṹ��*/
struct PWM_CONTROL_STRUCT{

    uint32_t pwm_prd;       // Reload value
    uint16_t pwm_lead_dt;   // Dead time of lead lead
    uint16_t pwm_lag_dt;    // Dead time of lag lead
    uint16_t pwm_cmp;       // PWM compare value
    uint16_t pwm_phsa;      // PWM phase-shifted angle
};
typedef struct PWM_CONTROL_STRUCT PwmControl_ST;

/*EPWM����ʹ�ܽṹ��*/
struct PWM_CONFIG_SELECT{

    uint8_t PHS_EN;        //����ʧ��ʹ��
    uint8_t SHDW_LOADB_EN; //��Ӱ�Ĵ���Bʹ��ʧ��
    uint8_t CMPB_EN;       //����Bʹ��ʧ��
    uint8_t DB_FULL_EN;    //����ʹ��ʧ��
};
typedef struct PWM_CONFIG_SELECT PwmConfig_SE;

/*EPWM �ο�ֵ����*/
struct EPWM_nature
{
    uint16_t ReloadValue;              // SPWM�е���װֵ
    uint16_t ArrayMountValue;          // SPWM���ɵ��������
    float LoseRangeValue;              // ��ʧռ�ձȷ�Χ������IO�ں�MOSFET�������½�����ʱԭ��PWM��0%��100%������ʧ�棬������ʹ�ã�
    uint16_t CosArray[COS_ARRAY_MAX];  // ���ɵ�SPWM����
    uint32_t DDSFreOut;                // DDS���Ƶ��
    uint32_t DDSFw;                    // DDSƵ�ʿ�����
    uint32_t Index;                    // ����������ֵ
    volatile uint32_t DDSCount;        // DDS�ۼ���
};

typedef struct EPWM_nature EPWM_nature_ref;
extern EPWM_nature_ref EPWM_nature_com; //EPWM �ο�ֵȫ�ֱ���

void ePWM_Init(void);
void ePWMparameter_Init(PwmControl_ST *PwmControl_st,
                        uint32_t INVERTER_FRE,
                        uint16_t INVERTER_INIT_PHSA,
                        uint16_t INVERTER_INIT_DUTY,
                        uint16_t INVERTER_LEAD_DEAD_TIME);
void ePWMConfig_Init(PwmConfig_SE *PwmConfig_se,
                     uint8_t PHS_EN,
                     uint8_t SHDW_LOADB_EN,
                     uint8_t CMPB_EN,
                     uint8_t DB_FULL_EN);
void ePWMx_Init(volatile struct EPWM_REGS *EPwmxRegs,
                PwmControl_ST *PwmControl_st,
                PwmConfig_SE *PwmConfig_se);
void ePWMx_setDuty(volatile struct EPWM_REGS *EPwmxRegs,
                   PwmConfig_SE *PwmConfig_se,
                   uint32_t INVERTER_FRE,
                   uint16_t HALF_BRIDGE_DUTY);

void epwm_Mos_Init(void);
void ePWM_EnGpio(void);
void ePWM_EN(void);
void ePWM_DISABLE(void);

#endif /* HARDWARE_EPWM_EPWM_H_ */
