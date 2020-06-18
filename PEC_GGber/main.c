#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "system.h"
#include "led.h"
#include "mcbsp.h"
#include "epwm.h"
#include "fan_epwm.h"
#include "dsp_adc.h"
#include "sci.h"
#include "con_pid.h"

/**
 * main.c
 */
void main(void)
{
    static uint32_t signal_eror_count=0;

    sys_init();         //System Init

    Led_Init();         //LED Init

    McBSP_Init();       //McBSP simulation SPI Init

    adas3022_Init();    //Adas3022 Init

    epwm_Mos_Init();    //MOS_EPWM  Init

    fanEpwm_Init();     //Fan_epwm  Init

    ADC_Init();         //DSP_adc  Init

    SCIb_Init(115200);  //scib_232  Init

    while(1)
    {

        switch(adasFlag)
        {
            case ADAS_OK:
                if(adas_sensor_origin_data.signal<15&adas_sensor_origin_data.signal>-5)
                    signal_eror_count++; else  signal_eror_count=0;
                if(signal_eror_count>=100000)
                {
                    ePWM_DISABLE();
                    adasFlag=ADAS_ERROR;
                    signal_eror_count=100000;
                }else{
                    ePWM_EN();
                    signal_eror_count=0;
                }
                break;

            case ADAS_ERROR:
                adasFlag=ADAS_FREE;
//                ePWM_DISABLE();
                break;

            case ADAS_FREE:
                adas3022_StartWork(); break;

            default:
                adasFlag=ADAS_FREE; break;
        }

        if(led_Task_Count>=200){
            Led_Display(led1, TOG);
            led_Task_Count = 0;
        }

        delay_us(1);

    }
}
