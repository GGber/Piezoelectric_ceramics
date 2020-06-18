/*********************************************************************
* 文件名: mcbsp.c
* Copyright(c): 2020,SDC, All Rights Reserved
* 描 述: adas3022驱动文件
* 创建日期:2020.6.18
* 创建人: GGber
* 修改记录:
**********************************************************************/
#include "mcbsp.h"


/*
 * **********************************************************************************************************
 * ****************************************ADAD3022_底层驱动代码******************************************************************
 * **********************************************************************************************************
 * */

__interrupt void Mcbsp_SPI_RxINTB_ISR(void);

/**
  *@Function Name: McBSP_Init
  *@Function: McBSP初始化SPI模式
  *@Incoming Parameters: 无
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
void McBSP_Init(void){

    EALLOW;
    PieVectTable.MRINTB = &Mcbsp_SPI_RxINTB_ISR;
    EDIS;

    InitMcbspGpio();
    InitMcbsp();

    EALLOW;
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;  // Enable the PIE block
    PieCtrlRegs.PIEIER6.bit.INTx3 = 1;  // Enable PIE Group 6, INT 3  RX
    IER |= 0x20;    // Enable CPU INT6
    EINT;           // Enable Global Interrupts
    EDIS;
}
/**
  *@Function Name: McBSP_write
  *@Function: McBSP写数据
  *@Incoming Parameters: uint16_t dat
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
void McBSP_write(uint16_t dat){

    while(McbspbRegs.SPCR2.bit.XRDY == 0);
    McbspbRegs.DXR1.all = dat;
}
/**
  *@Function Name: Mcbsp_read
  *@Function: McBSP读数据
  *@Incoming Parameters: 无
  *@Return Value: McbspbRegs.DRR1.all 寄存器数据
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
uint16_t Mcbsp_read(void){

    while(McbspbRegs.SPCR1.bit.RRDY == 0);
    return McbspbRegs.DRR1.all;
}

/**
  *@Function Name: McBSP_write_no
  *@Function: McBSP写数据 不等待数据
  *@Incoming Parameters: uint16_t dat
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
void McBSP_write_no(uint16_t dat){

    McbspbRegs.DXR1.all = dat;
}
/**
  *@Function Name: Mcbsp_SPI_RxINTB_ISR
  *@Function: McBSP接收中断函数
  *@Incoming Parameters: 无
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
#if RUN_IN_FLASH
#pragma CODE_SECTION(Mcbsp_SPI_RxINTB_ISR, "ramfuncs")
#endif
__interrupt void Mcbsp_SPI_RxINTB_ISR(void){

//    uint16_t val;
//    val = McbspbRegs.DRR1.all;
//    adas3022_getValue(val);

    PieCtrlRegs.PIEACK.bit.ACK6 = 1;


}


/*
 * **********************************************************************************************************
 * ****************************************ADAS3022_API接口代码******************************************************************
 * **********************************************************************************************************
 * */

SENSOR adas_sensor_origin_data;//定义Adas采集到的传感器值 ( 初值 )
/**
  *@Function Name: adas3022_Init
  *@Function: ADAS3022初始化
  *@Incoming Parameters: 无
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
void adas3022_Init(void){

    adas3022_ResetGpioInit();

    adas3022_WREG(CFG_OVERWRITE|INX_7|COM_DIFF|PGIA_20V48|MUX_AFE|SEQ_DISABLE|TEMP_DISABLE|REFN_ENABLE|CMS_NORMAL|CHPA_NORMAL);
    adas3022_WREG(0x0000);
    adas3022_WREG(0x0000);

    delay_ms(10);
}
/**
  *@Function Name: adas3022_StartWork
  *@Function: ADAS3022开始工作
  *@Incoming Parameters: 无
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */

#if RUN_IN_FLASH
#pragma CODE_SECTION(adas3022_StartWork, "ramfuncs")
#endif

void adas3022_StartWork(void){

    delay_us(1);
    adas3022_WREG(CFG_OVERWRITE|INX_7|COM_DIFF|PGIA_20V48|MUX_AFE|SEQ_DISABLE|TEMP_DISABLE|REFN_ENABLE|CMS_NORMAL|CHPA_NORMAL);
    //adas3022_getValue(Mcbsp_read());
    //adas3022_WREG(0x0000);
#ifdef IOC
    currentAD = Mcbsp_read();
#else
    adas_sensor_origin_data.sigal = Mcbsp_read();
#endif
}


/**
  *@Function Name: adas3022_WREG
  *@Function: ADAS3022写寄存器
  *@Incoming Parameters: uint16_t regVal
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
void adas3022_WREG(uint16_t regVal){

    McBSP_write(regVal);
}
/**
  *@Function Name: adas3022_StarCnv
  *@Function: ADAS3022开始转化
  *@Incoming Parameters: 无
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
void adas3022_StarCnv(void){

    McBSP_write_no(0x0000);
}

/**
  *@Function Name: adas3022_ResetGpioInit
  *@Function: ADAS3022复位引脚初始化
  *@Incoming Parameters: 无
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
void adas3022_ResetGpioInit(void){          //复位引脚初始化

    EALLOW;
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;
    EDIS;

    GpioDataRegs.GPASET.bit.GPIO0 = 1;
}
/**
  *@Function Name: adas3022_Reset
  *@Function: ADAS3022复位
  *@Incoming Parameters: 无
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
void adas3022_Reset(void){

    GpioDataRegs.GPASET.bit.GPIO0 = 1;
    delay_us(10);
    GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
    delay_us(10);
}


