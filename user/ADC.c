/*------------------------------------------------------------------*/
/* --- STC MCU Limited ---------------------------------------------*/
/* --- STC12C5Axx Series MCU A/D Conversion Demo -------------------*/
/* --- Mobile: (86)13922805190 -------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ---------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966----------------------*/
/* --- Web: www.STCMCU.com -----------------------------------------*/
/* --- Web: www.GXWMCU.com -----------------------------------------*/
/* If you want to use the program or the program referenced in the  */
/* article, please specify in which data and procedures from STC    */
/*------------------------------------------------------------------*/
/*  Includes  ----------------------------------------------------- */
	#include "STC12C5A60S2.h"
	#include "intrins.h"
	#include "ADC.h"
	#include "PCA.h"

/*  Variable -------------------------------------------------------*/
	extern u16 ADC_value[TIMES];                        //ADC channel NO.
	u8 times=0;
	extern bit idenA;

/*----------------------------
ADC interrupt service routine
----------------------------*/
void adc_isr() interrupt 5 using 3
{
	ADC_CONTR &= !ADC_FLAG;         //Clear ADC interrupt flag
	/*if(P0 & 0x3c) 
	{
		idenA=1;
		pwm(0,0);
	}*/
	if(++times > (TIMES-1)) times=0;
    ADC_value[TIMES]=(ADC_RES << 2) + (ADC_RESL & 0x03);//Get ADC 10-bit result and Send to UART
	ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | 1;
}

void Delay_fix(u16 n);
/*----------------------------
Initial ADC sfr
----------------------------*/
void ADC_Init(void)
{
    P1ASF = 0x02;                   //Set all P1 as analog input port
    ADC_RES = 0;                    //Clear previous result
	IE |= 0x20;                      //Enable ADC interrupt and Open master interrupt switch
                                    //Start A/D conversion
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | 1;
    Delay_fix(2);                       //ADC power-on delay and Start A/D conversion
	
}

/*----------------------------
Software delay function
----------------------------*/
void Delay_fix(u16 n)
{
    u16 x;

    while (n--)
    {
        x = 10000;
        while (x--);
    }
}

