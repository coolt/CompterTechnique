/*******************************************************************************
* File:     events.h
* Purpose:  Rahmen
* Author:   M. Thaler, ZHAW
*******************************************************************************/

#define NOEVENT       0u
#define RESET         1u
#define KEYPRESSED_R  2u
#define TIMEOUT       3u

/******************************************************************************/
/* check if there is key event    (key pressed)                               */

unsigned int getRightKeyEvent(void);

/******************************************************************************/
/* check if there is timer event (time out)                                   */

unsigned int getTimerEvent(void);

/******************************************************************************/

