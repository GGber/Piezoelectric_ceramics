/*********************************************************************
* 文件名: sci.c
* Copyright(c): 2020,SDC, All Rights Reserved
* 描 述: sci通信底层驱动
* 创建日期:2020.6.18
* 创建人: GGber
* 修改记录:
**********************************************************************/
#include "sci.h"

__interrupt void SCIa_RxFIFOInt(void);
__interrupt void SCIb_RxFIFOInt(void);
__interrupt void SCIc_RxFIFOInt(void);

/**
  *@Function Name: SCIa_Init
  *@Function: SCIx初始化函数
  *@Incoming Parameters: uint32_t SCIA_BAUDRATE
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
void SCIa_Init(uint32_t SCIA_BAUDRATE){

    InitSciaGpio();

    EALLOW;

    SciaRegs.SCICCR.bit.STOPBITS = 0;
    SciaRegs.SCICCR.bit.PARITYENA = 0;
    SciaRegs.SCICCR.bit.LOOPBKENA = 0;
    SciaRegs.SCICCR.bit.ADDRIDLE_MODE = 0;
    SciaRegs.SCICCR.bit.SCICHAR = 7;

    SciaRegs.SCICTL1.bit.SWRESET = 1;
    SciaRegs.SCICTL1.bit.RXENA = 1;
    SciaRegs.SCICTL1.bit.TXENA = 1;

    SciaRegs.SCICTL2.bit.RXBKINTENA = 1;

    SciaRegs.SCIHBAUD = (37500000 / SCIA_BAUDRATE / 8 - 1) >> 8;
    SciaRegs.SCILBAUD = (37500000 / SCIA_BAUDRATE / 8 - 1) & 0xFF;

    SciaRegs.SCIFFTX.bit.TXFIFOXRESET = 1;
    SciaRegs.SCIFFTX.bit.SCIRST = 1;
    SciaRegs.SCIFFTX.bit.SCIFFENA = 1;

    SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;
    SciaRegs.SCIFFRX.bit.RXFFIL = 1;
    SciaRegs.SCIFFRX.bit.RXFFIENA = 1;

    PieVectTable.SCIRXINTA = &SCIa_RxFIFOInt;

    EDIS;

    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
    PieCtrlRegs.PIEIER9.bit.INTx1 = 1;

    IER |= M_INT9;
    EINT;
}
/**
  *@Function Name: SCIa_RxFIFOInt
  *@Function: SCIx接收中断入口函数
  *@Incoming Parameters: 无
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
#if RUN_IN_FLASH
#pragma CODE_SECTION(SCIa_RxFIFOInt, "ramfuncs" ); // 当从FLASH运行时，将函数移动到RAM中运行，加快运行速度
#endif
__interrupt void SCIa_RxFIFOInt(void){


    SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
    SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;
    PieCtrlRegs.PIEACK.bit.ACK9 = 1;
}
/**
  *@Function Name: SCIa_sendOneByte
  *@Function: SCIx发送一个字节
  *@Incoming Parameters: uint8_t dat
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
#if RUN_IN_FLASH
#pragma CODE_SECTION(SCIa_sendOneByte, "ramfuncs" ); // 当从FLASH运行时，将函数移动到RAM中运行，加快运行速度
#endif
void SCIa_sendOneByte(uint8_t dat){

    while(SciaRegs.SCICTL2.bit.TXEMPTY != 1);
    SciaRegs.SCITXBUF = dat;
}
/**
  *@Function Name: SCIa_sendBuff
  *@Function: SCIx发送数组指针
  *@Incoming Parameters: uint8_t *buff, uint8_t len
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
#if RUN_IN_FLASH
#pragma CODE_SECTION(SCIa_sendBuff, "ramfuncs" ); // 当从FLASH运行时，将函数移动到RAM中运行，加快运行速度
#endif
void SCIa_sendBuff(uint8_t *buff, uint8_t len){

    while(len){
        SCIa_sendOneByte(*buff);
        buff++;
        len--;
    }
}
/**
  *@Function Name: SCIb_Init
  *@Function: SCIx初始化函数
  *@Incoming Parameters: uint32_t SCIB_BAUDRATE
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
void SCIb_Init(uint32_t SCIB_BAUDRATE){

    InitScibGpio();

    EALLOW;

    ScibRegs.SCICCR.bit.STOPBITS = 0;
    ScibRegs.SCICCR.bit.PARITYENA = 0;
    ScibRegs.SCICCR.bit.LOOPBKENA = 0;
    ScibRegs.SCICCR.bit.ADDRIDLE_MODE = 0;
    ScibRegs.SCICCR.bit.SCICHAR = 7;

    ScibRegs.SCICTL1.bit.SWRESET = 1;
    ScibRegs.SCICTL1.bit.RXENA = 1;
    ScibRegs.SCICTL1.bit.TXENA = 1;

    ScibRegs.SCICTL2.bit.RXBKINTENA = 1;

    ScibRegs.SCIHBAUD = (37500000 / SCIB_BAUDRATE / 8 - 1) >> 8;
    ScibRegs.SCILBAUD = (37500000 / SCIB_BAUDRATE / 8 - 1) & 0xFF;

    ScibRegs.SCIFFTX.bit.TXFIFOXRESET = 1;
    ScibRegs.SCIFFTX.bit.TXFFIL = 0;
    ScibRegs.SCIFFTX.bit.SCIRST = 1;
    ScibRegs.SCIFFTX.bit.SCIFFENA = 1;

    ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;
    ScibRegs.SCIFFRX.bit.RXFFIL = 1;
    ScibRegs.SCIFFRX.bit.RXFFIENA = 1;

    PieVectTable.SCIRXINTB = &SCIb_RxFIFOInt;

    EDIS;

    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
    PieCtrlRegs.PIEIER9.bit.INTx3 = 1;

    IER |= M_INT9;
    EINT;
}
/**
  *@Function Name: SCIb_RxFIFOInt
  *@Function: SCIx接收中断入口函数
  *@Incoming Parameters: 无
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
#if RUN_IN_FLASH
#pragma CODE_SECTION(SCIb_sendOneByte, "ramfuncs" ); // 当从FLASH运行时，将函数移动到RAM中运行，加快运行速度
#endif
__interrupt void SCIb_RxFIFOInt(void){

    static uint8_t rev = 0x00;

    rev = ScibRegs.SCIRXBUF.bit.RXDT;

    ScibRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
    ScibRegs.SCIFFRX.bit.RXFFINTCLR=1;
    PieCtrlRegs.PIEACK.bit.ACK9 = 1;
}
/**
  *@Function Name: SCIb_sendOneByte
  *@Function: SCIx发送一个字节数据
  *@Incoming Parameters: uint8_t dat
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
#if RUN_IN_FLASH
#pragma CODE_SECTION(SCIb_sendOneByte, "ramfuncs" ); // 当从FLASH运行时，将函数移动到RAM中运行，加快运行速度
#endif
void SCIb_sendOneByte(uint8_t dat){

    while(ScibRegs.SCICTL2.bit.TXEMPTY != 1);
    ScibRegs.SCITXBUF = dat;
}
/**
  *@Function Name: SCIb_sendBuff
  *@Function: SCIx发送数组指针
  *@Incoming Parameters: uint8_t *buff, uint8_t len
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
#if RUN_IN_FLASH
#pragma CODE_SECTION(SCIb_sendBuff, "ramfuncs" ); // 当从FLASH运行时，将函数移动到RAM中运行，加快运行速度
#endif
void SCIb_sendBuff(uint8_t *buff, uint8_t len){

    while(len){
        SCIb_sendOneByte(*buff);
        buff++;
        len--;
    }
}
/**
  *@Function Name: SCIc_Init
  *@Function: SCIx初始化
  *@Incoming Parameters: uint32_t SCIA_BAUDRATE
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
void SCIc_Init(uint32_t SCIC_BAUDRATE){

    InitScicGpio();

    EALLOW;

    ScicRegs.SCICCR.bit.STOPBITS = 0;
    ScicRegs.SCICCR.bit.PARITYENA = 0;
    ScicRegs.SCICCR.bit.LOOPBKENA = 0;
    ScicRegs.SCICCR.bit.ADDRIDLE_MODE = 0;
    ScicRegs.SCICCR.bit.SCICHAR = 7;

    ScicRegs.SCICTL1.bit.SWRESET = 1;
    ScicRegs.SCICTL1.bit.RXENA = 1;
    ScicRegs.SCICTL1.bit.TXENA = 1;

    ScicRegs.SCICTL2.bit.RXBKINTENA = 1;

    ScicRegs.SCIHBAUD = (37500000 / SCIC_BAUDRATE / 8 - 1) >> 8;
    ScicRegs.SCILBAUD = (37500000 / SCIC_BAUDRATE / 8 - 1) & 0xFF;

    ScicRegs.SCIFFTX.bit.TXFIFOXRESET = 1;
    ScicRegs.SCIFFTX.bit.TXFFIL = 0;
    ScicRegs.SCIFFTX.bit.SCIRST = 1;
    ScicRegs.SCIFFTX.bit.SCIFFENA = 1;

    ScicRegs.SCIFFRX.bit.RXFIFORESET = 1;
    ScicRegs.SCIFFRX.bit.RXFFIL = 1;
    ScicRegs.SCIFFRX.bit.RXFFIENA = 1;

    PieVectTable.SCIRXINTC = &SCIc_RxFIFOInt;

    EDIS;

    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
    PieCtrlRegs.PIEIER8.bit.INTx5 = 1;

    IER |= M_INT8;
    EINT;
}
/**
  *@Function Name: SCIc_RxFIFOInt
  *@Function: SCIx接收中断入口函数
  *@Incoming Parameters: 无
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
#if RUN_IN_FLASH
#pragma CODE_SECTION(SCIc_RxFIFOInt, "ramfuncs" ); // 当从FLASH运行时，将函数移动到RAM中运行，加快运行速度
#endif
__interrupt void SCIc_RxFIFOInt(void){

    SCIc_sendOneByte(ScicRegs.SCIRXBUF.bit.RXDT);

    ScicRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
    ScicRegs.SCIFFRX.bit.RXFFINTCLR=1;
    PieCtrlRegs.PIEACK.bit.ACK8 = 1;
}
/**
  *@Function Name: SCIc_sendOneByte
  *@Function: SCIx发送一个字节
  *@Incoming Parameters: uint8_t dat
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
#if RUN_IN_FLASH
#pragma CODE_SECTION(SCIc_sendOneByte, "ramfuncs" ); // 当从FLASH运行时，将函数移动到RAM中运行，加快运行速度
#endif
void SCIc_sendOneByte(uint8_t dat){

    while(ScicRegs.SCICTL2.bit.TXEMPTY != 1);
    ScicRegs.SCITXBUF = dat;
}
/**
  *@Function Name: SCIc_sendBuff
  *@Function: SCIx发送数组指针
  *@Incoming Parameters: uint8_t *buff, uint8_t len
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
#if RUN_IN_FLASH
#pragma CODE_SECTION(SCIc_sendBuff, "ramfuncs" ); // 当从FLASH运行时，将函数移动到RAM中运行，加快运行速度
#endif
void SCIc_sendBuff(uint8_t *buff, uint8_t len){

    while(len){
        SCIc_sendOneByte(*buff);
        buff++;
        len--;
    }
}


