/*********************************************************************
* �ļ���: fan_epwm.c
* Copyright(c): 2020,SDC, All Rights Reserved
* �� ��: epwm�������ȵײ�����
* ��������:2020.6.18
* ������: GGber
* �޸ļ�¼:
**********************************************************************/
#include "fan_epwm.h"

PwmControl_ST ePwm2FanControl_st;
PwmConfig_SE ePwm2FanConfig_se;

/**
  *@Function Name: fanEpwm_Init
  *@Function: ����pwm������ʼ��
  *@Incoming Parameters: ��
  *@Return Value: ��
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
void fanEpwm_Init(void){

    InitEPwm2Gpio();

    ePWMparameter_Init(&ePwm2FanControl_st,FAN_FRE,0,FAN_DUTY,0);
    ePWMConfig_Init(&ePwm2FanConfig_se,0,0,0,0);

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    ePWMx_Init(&EPwm2Regs,&ePwm2FanControl_st,&ePwm2FanConfig_se);

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}
/**
  *@Function Name: fanControl
  *@Function: ���ȿ�������
  *@Incoming Parameters: ��
  *@Return Value: ��
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
void fanControl(void){

    static uint16_t duty=0;

//    if(adc.t > FAN_STARTTEMP && adc.t < FAN_MAXOUT){
//
//        duty = 120 -2*adc.t;
//    }else if(adc.t >= FAN_MAXOUT){
//
//        duty = 40;
//    }else{
//
//        duty = 80;
//    }

    ePWMx_setDuty(&EPwm2Regs,&ePwm2FanConfig_se,FAN_FRE,duty);
}




