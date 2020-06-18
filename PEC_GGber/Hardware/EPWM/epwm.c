/*********************************************************************
* 文件名: epwm.c
* Copyright(c): 2020,SDC, All Rights Reserved
* 描 述: epwm驱动mos管底层驱动
* 创建日期:2020.6.18
* 创建人: GGber
* 修改记录:
**********************************************************************/
#include "epwm.h"

//PwmControl_ST ePwm1Control_st;
//PwmControl_ST ePwm2Control_st;
PwmControl_ST ePwm3Control_st;
PwmControl_ST ePwm4Control_st;
PwmControl_ST ePwm5Control_st;
PwmControl_ST ePwm6Control_st;

//PwmConfig_SE ePwm1Config_se;
//PwmConfig_SE ePwm2Config_se;
PwmConfig_SE ePwm3Config_se;
PwmConfig_SE ePwm4Config_se;
PwmConfig_SE ePwm5Config_se;
PwmConfig_SE ePwm6Config_se;

EPWM_nature_ref EPWM_nature_com = {
                   .ReloadValue = (150e6 + EPWM_FRE / 2) / EPWM_FRE - 1,
                   .ArrayMountValue = ARRAY_MOUNT_VALUE,
                   .LoseRangeValue = LOSE_RANGE_VALUE,
                   .CosArray = {0},
                   .DDSFreOut = DDS_FREOUT,
                   .DDSFw = 0,
};


__interrupt void epwm3_isr(void);

/**
  *@Function Name: epwm3_isr
  *@Function: EPWM3中断回调函数
  *@Incoming Parameters: 无
  *@Return Value: 无
  *@Author:GGber
  *@Date:2020.6.18
  *@Modified Date:
  */
#if RUN_IN_FLASH
#pragma CODE_SECTION(epwm3_isr, "ramfuncs"); // 当从FLASH运行时，将函数移动到RAM中运行，加快运行速度
#endif
__interrupt void epwm3_isr(void){

    //半桥输出控制任务
//    systemControl();

    // Clear INT flag for this timer
    EPwm3Regs.ETCLR.bit.INT = 1;
    // Acknowledge this interrupt to receive more interrupts from group 3
    PieCtrlRegs.PIEACK.bit.ACK3 = 1;
}

/**
  *@Function Name: ePWM_Init
  *@Function:ePWM底层驱动函数
  *@Incoming Parameters:无
  *@Return Value:无
  *@Author:GGber
  *@Date:2020.6.18
  *@Modified Date:
  */
#if RUN_IN_FLASH
#pragma CODE_SECTION(ePWM_Init, "ramfuncs"); // 当从FLASH运行时，将函数移动到RAM中运行，加快运行速度
#endif
void ePWM_Init(void){

    /****ePWM1-6 GPIO Init****/

    InitEPwmGpio();

//    ePWMparameter_Init(&ePwm1Control_st,20e3,0,20,100);
//    ePWMConfig_Init(&ePwm1Config_se,0,0,0,0);
//
//    ePWMparameter_Init(&ePwm2Control_st,30e3,0,30,200);
//    ePWMConfig_Init(&ePwm2Config_se,0,0,0,0);

    ePWMparameter_Init(&ePwm3Control_st,EPWM_FRE,PHSA_3,INIT_DUTY,DEAD_TIME);
    ePWMConfig_Init(&ePwm3Config_se,0,1,1,1);

    ePWMparameter_Init(&ePwm4Control_st,EPWM_FRE,PHSA_4,INIT_DUTY,DEAD_TIME);
    ePWMConfig_Init(&ePwm4Config_se,1,1,1,1);

    ePWMparameter_Init(&ePwm5Control_st,EPWM_FRE,PHSA_5,INIT_DUTY,DEAD_TIME);
    ePWMConfig_Init(&ePwm5Config_se,1,1,1,1);

    ePWMparameter_Init(&ePwm6Control_st,EPWM_FRE,PHSA_6,INIT_DUTY,DEAD_TIME);
    ePWMConfig_Init(&ePwm6Config_se,1,1,1,1);

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

//    ePWMx_Init(&EPwm1Regs,&ePwm1Control_st,&ePwm1Config_se);
//    ePWMx_Init(&EPwm2Regs,&ePwm2Control_st,&ePwm2Config_se);

    ePWMx_Init(&EPwm3Regs,&ePwm3Control_st,&ePwm3Config_se);

    ePWMx_Init(&EPwm4Regs,&ePwm4Control_st,&ePwm4Config_se);

    ePWMx_Init(&EPwm5Regs,&ePwm5Control_st,&ePwm5Config_se);

    ePWMx_Init(&EPwm6Regs,&ePwm6Control_st,&ePwm6Config_se);

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}

/**
  *@Function Name: ePWMparameter_Init
  *@Function: 初始化EPWM模块的初始参数
  *@Incoming Parameters: PwmControl_ST *PwmControl_st,
                         uint32_t INVERTER_FRE,
                         uint16_t INVERTER_INIT_PHSA,
                         uint16_t INVERTER_INIT_DUTY,
                         uint16_t INVERTER_LEAD_DEAD_TIME
  *@Return Value: 无
  *@Author:GGber
  *@Date:2020.6.18
  *@Modified Date:
  */
#if RUN_IN_FLASH
#pragma CODE_SECTION(ePWMparameter_Init, "ramfuncs"); // 当从FLASH运行时，将函数移动到RAM中运行，加快运行速度
#endif
void ePWMparameter_Init(PwmControl_ST *PwmControl_st,
                        uint32_t INVERTER_FRE,
                        uint16_t INVERTER_INIT_PHSA,
                        uint16_t INVERTER_INIT_DUTY,
                        uint16_t INVERTER_LEAD_DEAD_TIME){

    PwmControl_st->pwm_prd = (150e6 + INVERTER_FRE / 2) / INVERTER_FRE - 1;
    PwmControl_st->pwm_phsa = INVERTER_INIT_PHSA * ((150e6 + INVERTER_FRE / 2) / INVERTER_FRE - 1) / 360;
    PwmControl_st->pwm_cmp = 150e6 / INVERTER_FRE / 100 * INVERTER_INIT_DUTY;
    PwmControl_st->pwm_lead_dt = INVERTER_LEAD_DEAD_TIME * 15 / 100;
}

/**
  *@Function Name: ePWMConfig_Init
  *@Function: 选择EPWM模块相关功能使能函数
  *@Incoming Parameters: PwmConfig_SE *PwmConfig_se,
                         uint8_t PHS_EN,
                         uint8_t SHDW_LOADB_EN,
                         uint8_t CMPB_EN,
                         uint8_t DB_FULL_EN
  *@Return Value: 无
  *@Author:GGber
  *@Date:2020.6.18
  *@Modified Date:
  */
#if RUN_IN_FLASH
#pragma CODE_SECTION(ePWMConfig_Init, "ramfuncs"); // 当从FLASH运行时，将函数移动到RAM中运行，加快运行速度
#endif
void ePWMConfig_Init(PwmConfig_SE *PwmConfig_se,
                     uint8_t PHS_EN,
                     uint8_t SHDW_LOADB_EN,
                     uint8_t CMPB_EN,
                     uint8_t DB_FULL_EN){

    PwmConfig_se->PHS_EN = PHS_EN;
    PwmConfig_se->SHDW_LOADB_EN = SHDW_LOADB_EN;
    PwmConfig_se->CMPB_EN = CMPB_EN;
    PwmConfig_se->DB_FULL_EN = DB_FULL_EN;
}
/**
  *@Function Name: ePWMx_Init
  *@Function: EPWM模块初始化
  *@Incoming Parameters: volatile struct EPWM_REGS *EPwmxRegs,
                         PwmControl_ST *PwmControl_st,
                         PwmConfig_SE *PwmConfig_se
  *@Return Value: 无
  *@Author:GGber
  *@Date:2020.6.18
  *@Modified Date:
  */
#if RUN_IN_FLASH
#pragma CODE_SECTION(ePWMx_Init, "ramfuncs"); // 当从FLASH运行时，将函数移动到RAM中运行，加快运行速度
#endif
void ePWMx_Init(volatile struct EPWM_REGS *EPwmxRegs,
                PwmControl_ST *PwmControl_st,
                PwmConfig_SE *PwmConfig_se){

    //装载初值
    EPwmxRegs->TBPRD = PwmControl_st->pwm_prd;
    //移相角设置
    EPwmxRegs->TBPHS.half.TBPHS = PwmControl_st->pwm_phsa;
    //
    EPwmxRegs->TBCTR = 0x0000;
    //设置计数模式
    EPwmxRegs->TBCTL.bit.CTRMODE = TB_COUNT_UP;
    //移相使能失能
    if(PwmConfig_se->PHS_EN == 1){

        EPwmxRegs->TBCTL.bit.PHSEN = TB_ENABLE;
        EPwmxRegs->TBCTL.bit.PHSDIR = TB_DOWN;
        EPwmxRegs->TBCTL.bit.PRDLD = TB_SHADOW;
        EPwmxRegs->TBCTL.bit.SWFSYNC = 1;
    }else{

        EPwmxRegs->TBCTL.bit.PHSEN = TB_DISABLE;
    }
    //SYNC信号不串联
    EPwmxRegs->TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    //设置分频
    EPwmxRegs->TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwmxRegs->TBCTL.bit.CLKDIV = TB_DIV1;
    //设置阴影寄存器
    EPwmxRegs->CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwmxRegs->CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    if(PwmConfig_se->SHDW_LOADB_EN == 1){

        EPwmxRegs->CMPCTL.bit.SHDWBMODE = CC_SHADOW;
        EPwmxRegs->CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    }
    //设置比较值
    EPwmxRegs->CMPA.half.CMPA = PwmControl_st->pwm_cmp;
    if(PwmConfig_se->CMPB_EN == 1){

        EPwmxRegs->CMPB = PwmControl_st->pwm_cmp;
    }
    //输出寄存机动作
    EPwmxRegs->AQCTLA.bit.CAU = AQ_CLEAR;
    EPwmxRegs->AQCTLA.bit.ZRO = AQ_SET;
    //死区设置
    if(PwmConfig_se->DB_FULL_EN == 1){
        EPwmxRegs->DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;  //死区使能
    }else{
        EPwmxRegs->DBCTL.bit.OUT_MODE = DB_DISABLE;
    }
    EPwmxRegs->DBCTL.bit.POLSEL = DB_ACTV_HIC;       //EPWMxB翻转极性
    EPwmxRegs->DBCTL.bit.IN_MODE = DBA_ALL;          //EPWMxA作为上升下降沿 延时信号源
    EPwmxRegs->DBRED = PwmControl_st->pwm_lead_dt;   //上升沿死区设置
    EPwmxRegs->DBFED = PwmControl_st->pwm_lead_dt;
}
/**
  *@Function Name: epwm_Mos_Init
  *@Function: EPWM初始化函数
  *@Incoming Parameters: 无
  *@Return Value: 无
  *@Author:GGber
  *@Date:2020.6.18
  *@Modified Date:
  */
void epwm_Mos_Init(void){

    ePWM_EnGpio();
    ePWM_EN();

    EALLOW;
    PieVectTable.EPWM3_INT = &epwm3_isr;        //设置中断服务函数
    EDIS;

    ePWM_Init();

    // 设置中断事件
    EALLOW;
    EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
    EPwm3Regs.ETSEL.bit.INTEN = 1;                // Enable INT
    EPwm3Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event
    EDIS;

    EALLOW;
    PieCtrlRegs.PIEIER3.bit.INTx3 = 1;
    IER |= M_INT3;
    EDIS;
}

/**
  *@Function Name: ePWM_EnGpio
  *@Function: EPWM输出使能引脚
  *@Incoming Parameters: 无
  *@Return Value: 无
  *@Author:GGber
  *@Date:2020.6.18
  *@Modified Date:
  */
void ePWM_EnGpio(void){

    EALLOW;

    GpioCtrlRegs.GPBDIR.bit.GPIO57 = 1;
    GpioCtrlRegs.GPBPUD.bit.GPIO57 = 1;
    GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 0;

    GpioCtrlRegs.GPBDIR.bit.GPIO59 = 1;
    GpioCtrlRegs.GPBPUD.bit.GPIO59 = 1;
    GpioCtrlRegs.GPBMUX2.bit.GPIO59 = 0;

    GpioCtrlRegs.GPCDIR.bit.GPIO70 = 1;
    GpioCtrlRegs.GPCPUD.bit.GPIO70 = 1;
    GpioCtrlRegs.GPCMUX1.bit.GPIO70 = 0;

    GpioCtrlRegs.GPCDIR.bit.GPIO73 = 1;
    GpioCtrlRegs.GPCPUD.bit.GPIO73 = 1;
    GpioCtrlRegs.GPCMUX1.bit.GPIO73 = 0;

    GpioDataRegs.GPBSET.bit.GPIO57 = 1;
    GpioDataRegs.GPBSET.bit.GPIO59 = 1;
    GpioDataRegs.GPCSET.bit.GPIO70 = 1;
    GpioDataRegs.GPCSET.bit.GPIO73 = 1;

    EDIS;
}
/**
  *@Function Name: ePWM_EN
  *@Function: EPWM使能
  *@Incoming Parameters: 无
  *@Return Value: 无
  *@Author:GGber
  *@Date:2020.6.18
  *@Modified Date:
  */
void ePWM_EN(void){

    GpioDataRegs.GPBCLEAR.bit.GPIO57 = 1; //5
    GpioDataRegs.GPBCLEAR.bit.GPIO59 = 1; //3
    GpioDataRegs.GPCCLEAR.bit.GPIO70 = 1;
    GpioDataRegs.GPCCLEAR.bit.GPIO73 = 1; //4          //有问题
}
/**
  *@Function Name: ePWM_DISABLE
  *@Function: EPWM失能
  *@Incoming Parameters: 无
  *@Return Value: 无
  *@Author:GGber
  *@Date:2020.6.18
  *@Modified Date:
  */
void ePWM_DISABLE(void){

    GpioDataRegs.GPBSET.bit.GPIO57 = 1;
    GpioDataRegs.GPBSET.bit.GPIO59 = 1;
    GpioDataRegs.GPCSET.bit.GPIO70 = 1;
    GpioDataRegs.GPCSET.bit.GPIO73 = 1;
}
/**
  *@Function Name: ePWMx_setDuty
  *@Function: EPWMx模块占空比输出设置
  *@Incoming Parameters: volatile struct EPWM_REGS *EPwmxRegs,
                         PwmConfig_SE *PwmConfig_se,
                         uint32_t INVERTER_FRE,
                         uint16_t HALF_BRIDGE_DUTY
  *@Return Value: 无
  *@Author:GGber
  *@Date:2020.6.18
  *@Modified Date:
  */
#if RUN_IN_FLASH
#pragma CODE_SECTION(ePWMx_setDuty, "ramfuncs"); // 当从FLASH运行时，将函数移动到RAM中运行，加快运行速度
#endif
void ePWMx_setDuty(volatile struct EPWM_REGS *EPwmxRegs,
                   PwmConfig_SE *PwmConfig_se,
                   uint32_t INVERTER_FRE,
                   uint16_t HALF_BRIDGE_DUTY){

    EPwmxRegs->CMPA.half.CMPA = (150e6 / INVERTER_FRE) * HALF_BRIDGE_DUTY / 100;
    if(PwmConfig_se->CMPB_EN == 1){

        EPwmxRegs->CMPB = (150e6 / INVERTER_FRE) * HALF_BRIDGE_DUTY / 100;
    }
}
