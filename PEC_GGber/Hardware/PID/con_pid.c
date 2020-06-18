/*********************************************************************
* 文件名: con_pid.c
* Copyright(c): 2020,SDC, All Rights Reserved
* 描 述: 控制系统pid调节
* 创建日期:2020.6.18
* 创建人: GGber
* 修改记录:
**********************************************************************/
#include "con_pid.h"

float OUTPUT_V_EXPECT = 1.0f;

void systemControl(void){

    float cmp_val;
//
//    if(adasFlag == 2){
//        sensor_update();
//        adasFlag = 1;
//    }
//
//
#if OUTPUT_GAIN_LOOP
//    cmp_val = (int32_t)SPwm_st.ReloadValue*BASELINE;
//    cmp_val += (int32_t)SPwm_st.ReloadValue/2 * sensor.sigal * GAIN / ((int32_t)INPUT_TOTAL_V/2*1000) * OUTPUT_V_EXPECT;

    //计算模拟ADC采集值   65-3435
//    sensor.sigal = (int)(0.019 * 3500 + (1 - 2 * 0.019) * 3500 * 0.5f * (1 + sinf(i * 2 * 3.1415926f / 200)) + 0.5f);
//    i++;
//    if(i>=200){
//        i=0;
//    }

    cmp_val = (EPWM_nature_com.ReloadValue>>1);
    cmp_val *= 1 + ((int32_t)adas_sensor_origin_data.sigal<<8) * (1e-6) * (OUTPUT_V_EXPECT);//计算装载值

    if(cmp_val<0){
        cmp_val = 0;
    }else if(cmp_val>EPWM_nature_com.ReloadValue){
        cmp_val = EPWM_nature_com.ReloadValue;
    }

    EPwm3Regs.CMPA.half.CMPA = (uint16_t)(EPWM_nature_com.ReloadValue - cmp_val);//重新设置装载值
    EPwm4Regs.CMPA.half.CMPA = (uint16_t)(EPWM_nature_com.ReloadValue - cmp_val);
    EPwm5Regs.CMPA.half.CMPA = (uint16_t)(EPWM_nature_com.ReloadValue - cmp_val);
    EPwm6Regs.CMPA.half.CMPA = (uint16_t)(cmp_val);
#elif SPWM_OUTPUT
    SPwm_st.DDSCount += SPwm_st.DDSFw*2;
    EPwm3Regs.CMPA.half.CMPA = SPwm_st.CosArray[SPwm_st.DDSCount>>24]; //取高8位
//    SPwm_st.DDSCount += SPwm_st.DDSFw;
//    EPwm3Regs.CMPB = SPwm_st.CosArray[SPwm_st.DDSCount>>24];
#endif
}



