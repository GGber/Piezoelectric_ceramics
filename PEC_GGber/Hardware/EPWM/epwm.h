/*********************************************************************
* 文件名: epwm.h
* Copyright(c): 2020,SDC, All Rights Reserved
* 描 述: epwm驱动mos管底层驱动
* 创建日期:2020.6.18
* 创建人: GGber
* 修改记录:
**********************************************************************/
#ifndef HARDWARE_EPWM_EPWM_H_
#define HARDWARE_EPWM_EPWM_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "stdint.h"
#include "system.h"

/*半桥pwm频率100kHZ*/
#define EPWM_FRE  (100e3)
/*半桥输出移相角*/
#define PHSA_3    (0)
#define PHSA_4    (90)  //测试修改90->180
#define PHSA_5    (180)
#define PHSA_6    (90)
/*死区时间*/
#define DEAD_TIME (200)
/*初始化占空比*/
#define INIT_DUTY (50)

/*EPWM参考值宏定义*/
#define ARRAY_MOUNT_VALUE      ( 256u )         // SPWM生成的数组个数。  注：  DDS产生的波形中，取32位累加器的高8位作为有效值
#define LOSE_RANGE_VALUE       ( 0.1f )         // 丢失占空比，输出为(1-2*LoseRangeValue)*sin(wt)
#define DDS_FREOUT             ( 500u )         // Sine正弦波输出频率初始化
#define COS_ARRAY_MAX          ( 2000u)         // 所有的数据总长度，不能大于cmd文件中配置的.ebss分配的大小

/*EPWM属性设置结构体*/
struct PWM_CONTROL_STRUCT{

    uint32_t pwm_prd;       // Reload value
    uint16_t pwm_lead_dt;   // Dead time of lead lead
    uint16_t pwm_lag_dt;    // Dead time of lag lead
    uint16_t pwm_cmp;       // PWM compare value
    uint16_t pwm_phsa;      // PWM phase-shifted angle
};
typedef struct PWM_CONTROL_STRUCT PwmControl_ST;

/*EPWM功能使能结构体*/
struct PWM_CONFIG_SELECT{

    uint8_t PHS_EN;        //移相失能使能
    uint8_t SHDW_LOADB_EN; //阴影寄存器B使能失能
    uint8_t CMPB_EN;       //互补B使能失能
    uint8_t DB_FULL_EN;    //死区使能失能
};
typedef struct PWM_CONFIG_SELECT PwmConfig_SE;

/*EPWM 参考值定义*/
struct EPWM_nature
{
    uint16_t ReloadValue;              // SPWM中的重装值
    uint16_t ArrayMountValue;          // SPWM生成的数组个数
    float LoseRangeValue;              // 丢失占空比范围（由于IO口和MOSFET的上升下降沿延时原因，PWM在0%和100%附近会失真，丢弃不使用）
    uint16_t CosArray[COS_ARRAY_MAX];  // 生成的SPWM数组
    uint32_t DDSFreOut;                // DDS输出频率
    uint32_t DDSFw;                    // DDS频率控制字
    uint32_t Index;                    // 经典查表索引值
    volatile uint32_t DDSCount;        // DDS累加器
};

typedef struct EPWM_nature EPWM_nature_ref;
extern EPWM_nature_ref EPWM_nature_com; //EPWM 参考值全局变量

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
