/*********************************************************************
* 文件名: system.c
* Copyright(c): 2020,SDC, All Rights Reserved
* 描 述: DSP系统底层相关
* 创建日期: 2020.6.18
* 创建人: GGber
* 修改记录:
**********************************************************************/
#include "system.h"


uint16_t led_Task_Count=0;//定义LED任务计数

void cpuTimer0Init( void );
__interrupt void cpu_timer0_isr( void );

/****************************************************************************
 * 函数功能： 内存复制
 * 输入参数： 装载起始地址；装载结束地址；目标地址
 * 返回: 无
 * 修改记录:
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
 * 函数功能： 系统初始化
 * 输入参数： 无
 * 返回: 无
 * 修改记录:
***************************************************************************/
void sys_init( void )
{
    // DSP系统初始化
    InitSysCtrl();               // Initialize System Control:PLL, WatchDog, enable Peripheral Clocks
    InitGpio();                  // Set the GPIO to it's default state
    DINT;                         // Disable CPU interrupts
    InitPieCtrl();               // Initialize PIE control registers to their default state.
    IER = 0x0000;                 // Disable CPU interrupts (enable register)
    IFR = 0x0000;                 // Clear all CPU interrupt flags (flag register)
    InitPieVectTable();          //Initialize the PIE vector table with pointers to the shell Interrupt

    // 从FLASH运行时，将FLASH中的代码搬移RAM中运行
    #if RUN_IN_FLASH
    memCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);   //Copy time critical code and Flash setup code to RAM
    InitFlash();
    #endif

    // cpu定时器初始化  定时器溢出一次，进一次中断
    cpuTimer0Init();

    // Enable global Interrupts and higher priority real-time debug events:
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM
}

/****************************************************************************
 * 函数功能： CPU定时器0 初始化
 * 输入参数： 无
 * 返回: 无
 * 修改记录:
***************************************************************************/
void cpuTimer0Init(void)
{
    // CPU定时器初始化
    InitCpuTimers();                            // Only initialize the Cpu Timers
    ConfigCpuTimer( &CpuTimer0, 150, 1000u );  // (in uSeconds) 1ms
    CpuTimer0Regs.TCR.all = 0x4000;             // Use write-only instruction to set TSS bit = 0

    EALLOW;                       // This is needed to write to EALLOW protected registers
    PieVectTable.TINT0 = &cpu_timer0_isr;   // 定时器0的中断入口地址
    EDIS;                         // This is needed to disable write to EALLOW protected registers
    IER |= M_INT1;                          // Enable CPU int1 which is connected to CPU-Timer 0
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;      // Enable TINT0 in the PIE: Group 1 interrupt 7
}

/****************************************************************************
 * 函数功能： CPU定时器0 中断函数
 * 输入参数： 无
 * 返回: 无
 * 修改记录:
***************************************************************************/
#if RUN_IN_FLASH
#pragma CODE_SECTION(cpu_timer0_isr, "ramfuncs"); // 当从FLASH运行时，将函数移动到RAM中运行，加快运行速度
#endif
__interrupt void cpu_timer0_isr(void)
{
    //散热器控制任务计数
//    fanTaskCtrlCount++;
    //led控制任务计数
    led_Task_Count++;
    //串行通信任务计数
    //txTaskCtrlCount++;

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

/****************************************************************************
 * 函数功能： 系统  Ms级延时函数
 * 输入参数： 无
 * 返回: 无
 * 修改记录:
***************************************************************************/
#if RUN_IN_FLASH
#pragma CODE_SECTION(delay_ms, "ramfuncs"); // 当从FLASH运行时，将函数移动到RAM中运行，加快运行速度
#endif
void delay_ms(uint16_t ms)
{
    delay_us((uint64_t)1000 * ms);
}

//===========================================================================
// No more.
//===========================================================================
