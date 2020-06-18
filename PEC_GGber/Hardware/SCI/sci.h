/*********************************************************************
* 文件名: sci.h
* Copyright(c): 2020,SDC, All Rights Reserved
* 描 述: sci通信底层驱动
* 创建日期:2020.6.18
* 创建人: GGber
* 修改记录:
**********************************************************************/

#ifndef HARDWARE_SCI_SCI_H_
#define HARDWARE_SCI_SCI_H_

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "stdint.h"
#include "system.h"

void SCIa_Init(uint32_t SCIA_BAUDRATE);
void SCIa_sendOneByte(uint8_t dat);
void SCIa_sendBuff(uint8_t *buff, uint8_t len);

void SCIb_Init(uint32_t SCIB_BAUDRATE);
void SCIb_sendOneByte(uint8_t dat);
void SCIb_sendBuff(uint8_t *buff, uint8_t len);

void SCIc_Init(uint32_t SCIC_BAUDRATE);
void SCIc_sendOneByte(uint8_t dat);
void SCIc_sendBuff(uint8_t *buff, uint8_t len);

#endif /* HARDWARE_SCI_SCI_H_ */
