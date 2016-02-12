/********************************************************
* File:     timer.h
* Purpose:  Rahmen
* Author:   M. Thaler, ZHAW
*********************************************************/
/* wait for next timer interrupt                        */

void waitTimerTic(void);

/********************************************************/
/* initialize timer, set clock 200ms                    */

void initTimer(void);

/********************************************************/
/* start timer                                          */
/* int ticks: number of tick to count down              */

void startTimer(unsigned int ticks);

/********************************************************/
/* get current value of the timer (tick counter)        */

unsigned int getTimerValue(void);

/********************************************************/
