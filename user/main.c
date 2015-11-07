/*  ÏàÆËÐ¡³µ - ÆËÛòºÅ --------------------------------- *
 *  Includes  ----------------------------------------- */
	#include <STC12C5A60S2.h>
	#include "stdtype.h"
	#include "UART.h"
	#include "ADC.h"
	#include "PCA.h"
	#include "HC-SR04.h"
	#include "intrins.h"

/*  Global variables ---------------------------------- */
	u8 count;
	bit busy;
	u16 ADC_value[TIMES];
	s8 a,b,c,d;	   
	u8 count_temp=0;
	sbit IN4=P2^2;
	sbit IN3=P2^3;
	sbit IN2=P2^4;
	sbit IN1=P2^5;
	bit idenA=0;
	volatile bit edge;
	extern long int distance=0;               //¾àÀë±äÁ¿
	u8 duty;

			
/*  Function protype  --------------------------------- */
/*void Delay(int c)		//@22.1184MHz
{
	while(c--)
	{
		unsigned char i, j;
		i = 22;
		j = 128;
		do
		{
			while (--j);
		} while (--i);
	}
}
*/
void Delay_1(u16 a)		//@22.1184MHz
{
	while(a--)
	{
			unsigned char i, j, k;
	
		_nop_();
		_nop_();
		_nop_();
		i = 2;
		j = 82;
		k = 104;
		do
		{
			do
			{
				while (--k);
			} while (--j);
		} while (--i);
	}
}


void separate(u32 num)
{
	a=(u8)(num >> 24);
	b=(u8)(num >> 16);
	c=(u8)(num >> 8);
	d=(u8)num;
}

void ins()
{
	IN1=0;
	IN2=1;
	IN3=1;
	IN4=0;
}

void turnl(u16 a)
{
	IN1=0;
	IN2=1;
	IN3=0;
	IN4=1;
	Delay_1(a);
}
void turnr(u16 a)
{
	IN1=1;
	IN2=0;
	IN3=1;
	IN4=0;
	Delay_1(a);
}

void back(u16 a)
{
	IN1=1;
	IN2=0;
	IN3=0;
	IN4=1;
	idenA=0;
	Delay_1(a);
}

int main(void)
{
	UART_Init();
	ADC_Init();
	pwm_init();
	pwm(255,255);

	while(1)
	{	
		ins();
		pwm(255,255);
		if( P0 & 0x3c) 
		{
			back(90);//¼ì²â±ßÔµ
			turnl(180);
		}
		//if(distance < 100) pwm(255,255);
		if(++count_temp > (TIMES-1)) count_temp = 0;
		separate(distance);
		SendData(a);
		SendData(b);
		SendData(c);
		SendData(d);
		//duty=255;
	}
}
/*
/*----------------------------
UART interrupt service routine
----------------------------*/
void Uart_Isr() interrupt 4 using 1
{
    if (RI)
    {
        RI = 0;             //Clear receive interrupt flag
        //bit9 = RB8;         //P2.2 show parity bit
    }
    if (TI)
    {
        TI = 0;             //Clear transmit interrupt flag
        busy = 0;           //Clear transmit busy flag
    }
}
/*
void TIM0() interrupt 1 using 2
{
	TF0 = 0;
	TL0 = 0xcd;
	TH0 = 0xf8;
	count++;
	if(count == 5)//³¬Éù²¨»ØÉùÂö¿í×î¶à18ms
	{
		TR0 =0;
		TL0 = 0xcd;
		TH0 = 0xf8;
		count = 0;
	}
}*/
