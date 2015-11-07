#ifndef UART_H
#define UART_H
/*  Includes  ------------------------------------------ */
	#include "stdtype.h"

/*  Macros --------------------------------------------- */
	#define FOSC 22118400L
	#define BAUD 9600           //UART baudrate
	//select parity
	#define PARITYBIT NONE_PARITY

/*  Func declare --------------------------------------- */
	void SendData(s8 dat);
	//void SendString(s8 *s);
	void UART_Init(void);

/*  Typedef  ------------------------------------------- */


#endif /* Preventing weight definition */	   