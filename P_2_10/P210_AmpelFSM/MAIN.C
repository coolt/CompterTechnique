/*******************************************************************************
* File:      main.c
* Author:    M. Thaler, ZHAW
*******************************************************************************/

#include "fsm.h"
#include "events.h"
#include "timer.h"

/******************************************************************************/

#define MAX_EVENTS 2

/******************************************************************************/

void main(void) {

    unsigned int j;
    unsigned int anEvent[MAX_EVENTS];

    initTimer();                /* initialize timer */
    FSM(RESET);                 /* initialize fsm   */

    while (1) {

        /* wait for next timer interrupt */
        waitTimerTic(); 
     
       /* evaluate all events */
        anEvent[0] = getRightKeyEvent();
        anEvent[1] = getTimerEvent();

        /* for all events call fsm */
        for (j = 0; j < MAX_EVENTS; j++) {
            if (anEvent[j] != NOEVENT) {
               FSM(anEvent[j]);
               anEvent[j] = NOEVENT;
            }
        }
    } 
}
/******************************************************************************/
