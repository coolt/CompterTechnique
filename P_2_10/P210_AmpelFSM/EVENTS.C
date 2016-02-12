/*******************************************************************************
* File:     events.c
* Purpose:  Rahmen
* Author:   M. Thaler, ZHAW
*******************************************************************************/

#include <dos.h>
#include "events.h"
#include "timer.h"

# define PORT_ADDR 707h

/******************************************************************************/

unsigned int getRightKeyEvent() { // Rückgabewert 1, wenn gedrückt, sonst 0

	static unsigned char lastKey = 0;
	unsigned char currentKey;
	unsigned int res = 0;

	currentKey= inportb(unsigned int PORT_ADDR);

	res = (currentKey && KEYPRESSED_R);

	return res;

}

/******************************************************************************/

unsigned int getTimerEvent() {

}

/******************************************************************************/


