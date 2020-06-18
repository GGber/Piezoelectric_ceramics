/*********************************************************************
* 文件名: system.h
* Copyright(c): 2020,SDC, All Rights Reserved
* 描 述: 系统任务头文件
* 创建日期:2020.6.18
* 创建人: GGber
* 修改记录:
**********************************************************************/

#ifndef HARDWARE_SYSTEM_SYSTEM_H_
#define HARDWARE_SYSTEM_SYSTEM_H_

#ifdef __cplusplus
extern "C"
{
#endif

//头文件正文内容
#include <stdint.h>
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define RUN_IN_FLASH  1          // 1代表从FLASH运行，将程序搬移到RAM中运行,提高运行速度;

#define delay_us(us)    DELAY_US(us)    // us软件延时函数

void sys_init();
void delay_ms(uint16_t ms);             // ms软件延时函数

extern uint16_t led_Task_Count;

#ifdef __cplusplus
}
#endif


#endif /* HARDWARE_SYSTEM_SYSTEM_H_ */
