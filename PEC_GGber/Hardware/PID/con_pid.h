/*********************************************************************
* 文件名: con_pid.h
* Copyright(c): 2020,SDC, All Rights Reserved
* 描 述: 控制系统pid调节
* 创建日期:2020.6.18
* 创建人: GGber
* 修改记录:
**********************************************************************/

#ifndef HARDWARE_PID_CON_PID_H_
#define HARDWARE_PID_CON_PID_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "stdint.h"
#include "system.h"
#include "epwm.h"
#include "mcbsp.h"

#define OUTPUT_GAIN_LOOP    1     //开环增益模式
#define SPWM_OUTPUT         0     //SPWM模式

#define ADAS_FREE           2u     //ADAS空闲
#define ADAS_OK             1u     //转换成功
#define ADAS_ERROR          0u     //转换失败

extern uint16_t adasFlag;         //SIGNAL转换标志

#endif /* HARDWARE_PID_CON_PID_H_ */
