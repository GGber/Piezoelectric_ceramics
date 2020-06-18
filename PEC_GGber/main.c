#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "system.h"
#include "led.h"
#include "mcbsp.h"
#include "epwm.h"
#include "fan_epwm.h"
#include "dsp_adc.h"
#include "sci.h"


/**
 * main.c
 */
int main(void)
{
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

        if(led_Task_Count>=200){
            Led_Display(led1, TOG);
            led_Task_Count = 0;
        }
    }

	return 0;
}
