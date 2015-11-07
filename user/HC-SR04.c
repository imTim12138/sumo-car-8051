/******************************************************************************/
/* 项目名称  : TX-1C扩展板 超声波测距                                         */
/* 主控芯片  : STC89C52                                                       */
/* 文件名称  : UltraSonic                                                     */
/* 文件功能  : 超声波模块操作                                                 */
/* 文件版权  : 北京海克智动科技有限公司                                       */
/* 文件版本  :                                                                */
/******************************************************************************/
/**********************************包含头文件**********************************/
#include <STC12C5A60S2.h>

/************************************宏定义************************************/
#define VELOCITY_30C	3495       //30摄氏度时的声速，声速V= 331.5 + 0.6*温度； 
#define VELOCITY_23C	3453       //23摄氏度时的声速，声速V= 331.5 + 0.6*温度； 
/************************************位定义************************************/
sbit INPUT  = P2^0;                //回声接收端口
sbit OUTPUT = P2^1;                //超声触发端口　
/********************************定义变量和数组********************************/
long int distance=0;               //距离变量
uchar count;
/***********************************函数声明***********************************/
extern void delay(uint x);
/******************************************************************************/
/* 函数名称  : Delay_xMs                                                      */
/* 函数描述  : 延时函数                                                       */
/* 输入参数  : x                                                              */
/* 参数描述  : 延时时间                                                       */
/* 返回值    : 无                                                             */
/******************************************************************************/
void Delay_xMs(unsigned int x)
{
    unsigned int i,j;
    for(i = 0;i < x;i++ )
    {
        for(j = 0;j < 3;j++ )
        {
            ;
        }
    }
}
/******************************************************************************/
/* 函数名称  : delayt                                                         */
/* 函数描述  : 延时函数                                                       */
/* 输入参数  : x                                                              */
/* 参数描述  : 延时时间数据                                                   */
/* 返回值    : 无                                                             */
/******************************************************************************/	
void delayt(uint x)
{
    uchar j;
    while(x-- > 0)
    {
  	    for(j = 0;j < 255;j++)
        {
            ;
        }
    }
}
/******************************************************************************/
/* 函数名称  : Init_MCU                                                       */
/* 函数描述  : 初始化单片机函数                                               */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */
/* 返回值    : 无                                                             */
/******************************************************************************/
void Init_MCU(void)
{
	TMOD = 0x01;	  //定时器0初始化,设置为16位自动重装模式
 	TL0 = 0xcd;
	TH0 = 0xf8;	      //1ms
    ET0 = 1;	      //开定时器0
	EA = 1;		      //总中断使能
}
/******************************************************************************/
/* 函数名称  : Init_Parameter                                                 */
/* 函数描述  : 初始化参数和IO口函数                                           */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */
/* 返回值    : 无                                                             */
/******************************************************************************/
void Init_Parameter(void)
{
	 OUTPUT =1;
	 INPUT = 1;
	 count = 0;
	 distance = 0;
}
/******************************************************************************/
/* 函数名称  : Trig_SuperSonic                                                */
/* 函数描述  : 发出声波函数                                                   */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */
/* 返回值    : 无                                                             */
/******************************************************************************/
void Trig_SuperSonic(void)//出发声波
{
	 OUTPUT = 1;
	 delayt(1);
	 OUTPUT = 0;
}
/******************************************************************************/
/* 函数名称  : Measure_Distance                                               */
/* 函数描述  : 计算距离函数                                                   */
/* 输入参数  : 无                                                             */
/* 参数描述  : 无                                                             */
/* 返回值    : 无                                                             */
/******************************************************************************/
void Measure_Distance(void)
{
	uchar l;
	uint h,y;
	TR0 = 1;
	while(INPUT)
    {
        ;
    }	
	TR0 = 0;
	l = TL0;
	h = TH0;
	y = (h << 8) + l;
	y = y - 0xf8cd;//us部分
	distance = y + 1000 * count;//计算总时间
	TL0 = 0xcd;
	TH0 = 0xf8;
	delayt(30);
	distance = VELOCITY_30C * distance / 20000;
}
void UltraSonic_Init(void)
{
	Init_MCU();
	Init_Parameter();
}
void GetDistance()
{
	Trig_SuperSonic();         //触发超声波发射
	while(INPUT == 0)		   //等待回声
	{
	;
	}
	Measure_Distance();        //计算脉宽并转换为距离
	Init_Parameter();          // 参数重新初始化
	delayt(100);               //延时，两次发射之间要至少有10ms间隔
}
