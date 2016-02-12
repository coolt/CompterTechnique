/*******************************************************************************
* File:     timer.c
* Purpose:  Timer Funktionen
* Author:   M. Thaler, ZHAW
*******************************************************************************/

#include "clock.h"
#include <dos.h>

#define EOI_    0xFF22          /* interrupt contr. addr.: EOI */
#define EISR    0x8000          /* EOI value */

/******************************************************************************/
/* local functions                                                            */

void registerISR(unsigned int iNr, void interrupt far (*isr)(void)) {
    unsigned long far *vector;
    (unsigned long)vector = 4*iNr;
    *vector = (unsigned long far)isr;
}

/*----------------------------------------------------------------------------*/

void signalEOI(void) {
    outport(EOI_, EISR);        /* set end of interrupt */
}

/* end local functions                                                        */
/******************************************************************************/
/* module global variables                                                    */
                               
int downCounter=0;              /* static value counter, init = 0  */

/******************************************************************************/
/*----------------------------------------------------------------------------*/

void waitTimerTic(void) {
    asm HLT;
}

/*----------------------------------------------------------------------------*/

void interrupt far timerISR(void) {
    if (downCounter > 0)
        downCounter--;
    signalEOI();
}

/*----------------------------------------------------------------------------*/

void startTimer(unsigned int ticks) {
    downCounter = ticks;
}

/*----------------------------------------------------------------------------*/

unsigned int getTimerValue(void) {
    return downCounter;
}

/*----------------------------------------------------------------------------*/

void initTimer(void) {
    registerISR(8, timerISR);    /* register ISR i vector table */
    setClock(50,40);             /* set clock to 200ms */
    startClock();                /* start clock */
}

/*----------------------------------------------------------------------------*/
