/*********************************************************************
* 文件名: fan_epwm.c
* Copyright(c): 2020,SDC, All Rights Reserved
* 描 述: DSP内部adc底层驱动
* 创建日期:2020.6.18
* 创建人: GGber
* 修改记录:
**********************************************************************/
#include "dsp_adc.h"
/**
  *@Function Name: adc_isr
  *@Function: ADC中断
  *@Incoming Parameters: 无
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
#if RUN_IN_FLASH
#pragma CODE_SECTION(adc_isr, "ramfuncs")
#endif

uint16_t adc_val[2];//存储转化后的结果

__interrupt void adc_isr(void);


__interrupt void adc_isr(void){

    adc_val[0] = AdcRegs.ADCRESULT0>>4;
    adc_val[1] = AdcRegs.ADCRESULT1>>4;

    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         // Reset SEQ1
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       // Clear INT SEQ1 bit
    PieCtrlRegs.PIEACK.bit.ACK1 = 1;
}
/**
  *@Function Name: ADC_Init
  *@Function: DSP内部ADC初始化
  *@Incoming Parameters: 无
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
void ADC_Init(void){

    #if (CPU_FRQ_150MHZ)     // Default - 150 MHz SYSCLKOUT
        #define ADC_MODCLK 0x3 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 150/(2*3)   = 25.0 MHz
    #endif
    #if (CPU_FRQ_100MHZ)
        #define ADC_MODCLK 0x2 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 100/(2*2)   = 25.0 MHz
    #endif

    EALLOW;
    SysCtrlRegs.HISPCP.all = ADC_MODCLK;
    EDIS;

    EALLOW;
    AdcRegs.ADCTRL1.bit.ACQ_PS = 1;
    AdcRegs.ADCTRL1.bit.CONT_RUN = 1;
    AdcRegs.ADCTRL1.bit.SEQ_OVRD = 0;
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 0;

//    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;

    AdcRegs.ADCTRL3.bit.ADCBGRFDN = 3;
    AdcRegs.ADCTRL3.bit.ADCPWDN = 1;
    AdcRegs.ADCTRL3.bit.ADCCLKPS = 0;
    AdcRegs.ADCTRL3.bit.SMODE_SEL = 0;

    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 1;

    AdcRegs.ADCREFSEL.bit.REF_SEL = 1;    //参考电压选择  0内部参考电压  1外部参考电压

    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x8;

    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;

    EDIS;

//    EALLOW;
//    PieCtrlRegs.PIEIER1.bit.INTx6 = 1;
//    IER |= M_INT1; // Enable CPU Interrupt 1
//    EINT;
//    EDIS;
}
/**
  *@Function Name: ADC_StarCnv
  *@Function: ADC软件触发转换
  *@Incoming Parameters: 无
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
void ADC_StarCnv(void){

    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;
}
/**
  *@Function Name: ADC_getValue
  *@Function: ADC得到采集数值
  *@Incoming Parameters: 无
  *@Return Value: 无
  *@Author: GGber
  *@Date: 2020.6.18
  *@Modified Date:
  */
#if RUN_IN_FLASH
#pragma CODE_SECTION(ADC_getValue, "ramfuncs")
#endif
void ADC_getValue(void){

    if(AdcRegs.ADCST.bit.INT_SEQ1 == 1){

        adc_val[0] = AdcRegs.ADCRESULT0>>4;
        adc_val[1] = AdcRegs.ADCRESULT1>>4;

        AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;
        AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
    } else {
        ADC_StarCnv();
    }
}





