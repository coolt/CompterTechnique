/******************************************************************************/
/* Purpose: Provides Interrupt Driven Timer Functionality                     */
/* File:    clock.h                                                           */
/* Author:  M. Thaler, ZHAW	                                                         */
/******************************************************************************/

/******************************************************************************/
/* register ISR in vector tabl eat interrupt iNr                              */

void registerISR(unsigned int iNr, void interrupt far (*isr)(void));

/******************************************************************************/
/* set clock: clock period = (100us * scale ) * Count                         */

void setClock(unsigned int scale, unsigned int Count);


/******************************************************************************/
/* start the clock and enable interrupts                                      */

void startClock(void);

/******************************************************************************/
/* stop Clock                                                                 */

void stopClock(void);

/******************************************************************************/
/* wait for next timer interrupt                                              */

#define WaitClockEvent() asm HLT

/******************************************************************************/
/* Reset Clock                                                                */

void resetClock(void);

/******************************************************************************/
