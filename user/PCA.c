#include <STC12C5A60S2.h>
#include "intrins.h"
#include "PCA.h"
typedef unsigned char BYTE;
typedef unsigned int WORD;

/*Declare SFR associated with the PCA 
sfr CCON        =   0xD8;           //PCA control register
sbit CCF0       =   CCON^0;         //PCA module-0 interrupt flag
sbit CCF1       =   CCON^1;         //PCA module-1 interrupt flag
sbit CR         =   CCON^6;         //PCA timer run control bit
sbit CF         =   CCON^7;         //PCA timer overflow flag
sfr CMOD        =   0xD9;           //PCA mode register
sfr CL          =   0xE9;           //PCA base timer LOW
sfr CH          =   0xF9;           //PCA base timer HIGH
sfr CCAPM0      =   0xDA;           //PCA module-0 mode register
sfr CCAP0L      =   0xEA;           //PCA module-0 capture register LOW
sfr CCAP0H      =   0xFA;           //PCA module-0 capture register HIGH
sfr CCAPM1      =   0xDB;           //PCA module-1 mode register
sfr CCAP1L      =   0xEB;           //PCA module-1 capture register LOW
sfr CCAP1H      =   0xFB;           //PCA module-1 capture register HIGH
sfr PCA_PWM0     =   0xf2;
sfr PCA_PWM1     =   0xf3;*/

void pwm_init(void)
{
                                    //Clear all module interrupt flag 清除所有模块中断标志
    CMOD = 0x0a;                    //Set PCA timer clock source as Fosc/2	  PCA 源设置为系统时钟的一半
                                    //Disable PCA timer overflow interrupt 禁用PCA溢出中断
    CCAPM1 = 0x42;                  //PCA module-1 work in 8-bit PWM mode and no PCA interrupt
	CCAPM0 = 0x42;                  //PCA module-0 work in 8-bit PWM mode and no PCA interrupt 允许比较器运行 允许CEX1脚8位PWM脉宽输出 没有中断
}
void pwm(int a,int b)
{
	CCON =0;                       //Initial PCA control register	初始化控制寄存器
                                     //PCA timer stop running  PCA定时器停止
                                    //Clear CF flag			 清除CF标志                                                    
	CL = 0;                         
    CH = 0;
    CCAP0H = CCAP0L =255-a;         //PWM0 port output a/256 duty cycle square wave
    CCAP1H = CCAP1L =255-b;         //PWM1 port output b/256 duty cycle square wave=
    CR = 1;                         //PCA timer start run  PCA计数器开始计数
}
