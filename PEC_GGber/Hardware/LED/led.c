/*********************************************************************
* 文件名: led.c
* Copyright(c): 2020,SDC, All Rights Reserved
* 描 述: LED灯驱动文件
* 创建日期:2020.6.18
* 创建人: GGber
* 修改记录:
**********************************************************************/
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#include "led.h"

/**
  *@Function Name: Led_Init
  *@Function: LED驱动引脚初始化
  *@Incoming Parameters: 无
  *@Return Value: 无
  *@Author: sang
  *@Date: 2019.07.25
  *@Modified Date:
  */
void Led_Init(void){

    EALLOW;

    GpioCtrlRegs.GPBDIR.bit.GPIO41 = 1;
    GpioCtrlRegs.GPBPUD.bit.GPIO41 = 1;
    GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 0;

    GpioCtrlRegs.GPBDIR.bit.GPIO44 = 1;
    GpioCtrlRegs.GPBPUD.bit.GPIO44 = 1;
    GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;

    GpioCtrlRegs.GPCDIR.bit.GPIO80 = 1;
    GpioCtrlRegs.GPCPUD.bit.GPIO80 = 1;
    GpioCtrlRegs.GPCMUX2.bit.GPIO80 = 0;

    GpioDataRegs.GPBSET.bit.GPIO41 = 1;
    GpioDataRegs.GPBSET.bit.GPIO44 = 1;
    GpioDataRegs.GPCSET.bit.GPIO80 = 1;

    EDIS;
}
/**
  *@Function Name: Led_Display
  *@Function: LED显示
  *@Incoming Parameters: LED_Num led_num, LED_Sta led_sta
  *@Return Value: 无
  *@Author: sang
  *@Date: 2019.07.25
  *@Modified Date:
  */
#if RUN_IN_FLASH
#pragma CODE_SECTION(Led_Display, "ramfuncs"); // 当从FLASH运行时，将函数移动到RAM中运行，加快运行速度
#endif
void Led_Display(LED_Num led_num, LED_Sta led_sta){
    switch(led_num){
        case led1:{
            switch(led_sta){
                case ON:{
                    GpioDataRegs.GPBCLEAR.bit.GPIO41 = 1;
                    break;
                }
                case OFF:{
                    GpioDataRegs.GPBSET.bit.GPIO41 = 1;
                    break;
                }
                case TOG:{
                    GpioDataRegs.GPBTOGGLE.bit.GPIO41 = 1;
                    break;
                }
            }
            break;
        }
        case led2:{
            switch(led_sta){
                case ON:{
                    GpioDataRegs.GPBCLEAR.bit.GPIO44 = 1;
                    break;
                }
                case OFF:{
                    GpioDataRegs.GPBSET.bit.GPIO44 = 1;
                    break;
                }
                case TOG:{
                    GpioDataRegs.GPBTOGGLE.bit.GPIO44 = 1;
                    break;
                }
            }
            break;
        }
        case led3:{
            switch(led_sta){
                case ON:{
                    GpioDataRegs.GPCCLEAR.bit.GPIO80 = 1;
                    break;
                }
                case OFF:{
                    GpioDataRegs.GPCSET.bit.GPIO80 = 1;
                    break;
                }
                case TOG:{
                    GpioDataRegs.GPCTOGGLE.bit.GPIO80 = 1;
                    break;
                }
            }
            break;
        }
        default:{
            GpioDataRegs.GPBSET.bit.GPIO41 = 1;
            GpioDataRegs.GPBSET.bit.GPIO44 = 1;
            GpioDataRegs.GPCSET.bit.GPIO80 = 1;
            break;
        }
    }
}

