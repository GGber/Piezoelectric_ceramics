/*********************************************************************
* �ļ���: system.c
* Copyright(c): 2020,SDC, All Rights Reserved
* �� ��: DSPϵͳ�ײ����
* ��������: 2020.6.18
* ������: GGber
* �޸ļ�¼:
**********************************************************************/
#include "system.h"


uint16_t led_Task_Count=0;//����LED�������

void cpuTimer0Init( void );
__interrupt void cpu_timer0_isr( void );

/****************************************************************************
 * �������ܣ� �ڴ渴��
 * ��������� װ����ʼ��ַ��װ�ؽ�����ַ��Ŀ���ַ
 * ����: ��
 * �޸ļ�¼:
***************************************************************************/
#if RUN_IN_FLASH
static void memCopy(Uint16 *loadStartAddr, Uint16 *loadEndAddr, Uint16 *destAddr)
{
    while(loadStartAddr < loadEndAddr)
    {
        *destAddr++ = *loadStartAddr++;
    }
}
#endif
/****************************************************************************
 * �������ܣ� ϵͳ��ʼ��
 * ��������� ��
 * ����: ��
 * �޸ļ�¼:
***************************************************************************/
void sys_init( void )
{
    // DSPϵͳ��ʼ��
    InitSysCtrl();               // Initialize System Control:PLL, WatchDog, enable Peripheral Clocks
    InitGpio();                  // Set the GPIO to it's default state
    DINT;                         // Disable CPU interrupts
    InitPieCtrl();               // Initialize PIE control registers to their default state.
    IER = 0x0000;                 // Disable CPU interrupts (enable register)
    IFR = 0x0000;                 // Clear all CPU interrupt flags (flag register)
    InitPieVectTable();          //Initialize the PIE vector table with pointers to the shell Interrupt

    // ��FLASH����ʱ����FLASH�еĴ������RAM������
    #if RUN_IN_FLASH
    memCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);   //Copy time critical code and Flash setup code to RAM
    InitFlash();
    #endif

    // cpu��ʱ����ʼ��  ��ʱ�����һ�Σ���һ���ж�
    cpuTimer0Init();

    // Enable global Interrupts and higher priority real-time debug events:
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM
}

/****************************************************************************
 * �������ܣ� CPU��ʱ��0 ��ʼ��
 * ��������� ��
 * ����: ��
 * �޸ļ�¼:
***************************************************************************/
void cpuTimer0Init(void)
{
    // CPU��ʱ����ʼ��
    InitCpuTimers();                            // Only initialize the Cpu Timers
    ConfigCpuTimer( &CpuTimer0, 150, 1000u );  // (in uSeconds) 1ms
    CpuTimer0Regs.TCR.all = 0x4000;             // Use write-only instruction to set TSS bit = 0

    EALLOW;                       // This is needed to write to EALLOW protected registers
    PieVectTable.TINT0 = &cpu_timer0_isr;   // ��ʱ��0���ж���ڵ�ַ
    EDIS;                         // This is needed to disable write to EALLOW protected registers
    IER |= M_INT1;                          // Enable CPU int1 which is connected to CPU-Timer 0
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;      // Enable TINT0 in the PIE: Group 1 interrupt 7
}

/****************************************************************************
 * �������ܣ� CPU��ʱ��0 �жϺ���
 * ��������� ��
 * ����: ��
 * �޸ļ�¼:
***************************************************************************/
#if RUN_IN_FLASH
#pragma CODE_SECTION(cpu_timer0_isr, "ramfuncs"); // ����FLASH����ʱ���������ƶ���RAM�����У��ӿ������ٶ�
#endif
__interrupt void cpu_timer0_isr(void)
{
    //ɢ���������������
//    fanTaskCtrlCount++;
    //led�����������
    led_Task_Count++;
    //����ͨ���������
    //txTaskCtrlCount++;

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

/****************************************************************************
 * �������ܣ� ϵͳ  Ms����ʱ����
 * ��������� ��
 * ����: ��
 * �޸ļ�¼:
***************************************************************************/
#if RUN_IN_FLASH
#pragma CODE_SECTION(delay_ms, "ramfuncs"); // ����FLASH����ʱ���������ƶ���RAM�����У��ӿ������ٶ�
#endif
void delay_ms(uint16_t ms)
{
    delay_us((uint64_t)1000 * ms);
}

//===========================================================================
// No more.
//===========================================================================
