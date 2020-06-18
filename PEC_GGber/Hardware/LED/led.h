/*********************************************************************
* �ļ���: led.c
* Copyright(c): 2020,SDC, All Rights Reserved
* �� ��: LED�������ļ�
* ��������:2020.6.18
* ������: GGber
* �޸ļ�¼:
**********************************************************************/
#ifndef HARDWARE_LED_LED_H_
#define HARDWARE_LED_LED_H_

typedef enum{
    led1,
    led2,
    led3
}LED_Num;

typedef enum{
    ON,
    OFF,
    TOG
}LED_Sta;

void Led_Init(void);
void Led_Display(LED_Num led_num, LED_Sta led_sta);


#endif /* HARDWARE_LED_LED_H_ */
