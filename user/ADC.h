#ifndef ADC_H
#define ADC_H
/*  Includes  ------------------------------------------ */
	#include "stdtype.h"

/*  Macros --------------------------------------------- */
	/*Define ADC operation const for ADC_CONTR*/
	#define TIMES	3U
	#define ADC_POWER   0x80            //ADC power control bit
	#define ADC_FLAG    0x10            //ADC complete flag
	#define ADC_START   0x08            //ADC start control bit
	#define ADC_SPEEDLL 0x00            //420 clocks
	#define ADC_SPEEDL  0x20            //280 clocks
	#define ADC_SPEEDH  0x40            //140 clocks
	#define ADC_SPEEDHH 0x60            //70 clocks

/*  Func declare  -------------------------------------- */
	void ADC_Init(void);

#endif /* Preventing weight definition */