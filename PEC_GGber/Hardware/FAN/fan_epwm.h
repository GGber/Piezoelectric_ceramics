/*********************************************************************
* 文件名: fan_epwm.h
* Copyright(c): 2020,SDC, All Rights Reserved
* 描 述: epwm驱动风扇底层驱动
* 创建日期:2020.6.18
* 创建人: GGber
* 修改记录:
**********************************************************************/

#ifndef HARDWARE_FAN_FAN_EPWM_H_
#define HARDWARE_FAN_FAN_EPWM_H_

#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "stdint.h"
#include "system.h"
#include "epwm.h"

#define FAN_FRE     (20e3)  //风扇频率
#define FAN_DUTY    (70u)   //风扇占空比


void fanEpwm_Init(void);
void fanControl(void);

#endif /* HARDWARE_FAN_FAN_EPWM_H_ */
