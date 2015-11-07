/*------------------------------------------------------------------*/
/* --- STC MCU Limited ---------------------------------------------*/
/* --- STC12C5Axx Series MCU UART (8-bit/9-bit)Demo ----------------*/
/* --- Mobile: (86)13922805190 -------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ---------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966----------------------*/
/* --- Web: www.STCMCU.com -----------------------------------------*/
/* --- Web: www.GXWMCU.com -----------------------------------------*/
/* If you want to use the program or the program referenced in the  */
/* article, please specify in which data and procedures from STC    */
/*------------------------------------------------------------------*/
/*  Includes  ----------------------------------------------------- */
	#include <STC12C5A60S2.h>
	#include "UART.h"
	#include "intrins.h"

/*  Variable -------------------------------------------------------*/
	sbit bit9 = P1^2;           //P2.2 show UART data bit9
	extern bit busy;

void UART_Init(void)//9600bps@22.1184MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xB8;		//设定定时初值
	TH1 = 0xB8;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	ES = 1;                 //Enable UART interrupt
    EA = 1;                 //Open master interrupt switch
}

/*----------------------------
Send a u8 data to UART
Input: dat (data to be sent)
Output:None
----------------------------*/
void SendData(s8 dat)
{
    while (busy);           //Wait for the completion of the previous data is sent
    busy = 1;
    SBUF = dat;             //Send data to UART buffer
}

/*----------------------------
Send a string to UART
Input: s (address of string)
Output:None
----------------------------*/
/*
void SendString(s8 *s)
{
    while (*s)              //Check the end of the string
    {
        SendData(*s++);     //Send current char and increment string ptr
    }
}*/

