/*  Includes  ----------------------------------------- */
	#include <STC12C5A60S2.h>
	#include "TIM.h"

/*  Function protype  --------------------------------- */
void TIM0Init(void)		//100微秒@22.1184MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x5C;		//设置定时初值
	TH0 = 0xF7;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}
