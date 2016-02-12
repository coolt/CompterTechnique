/******************************************************************************/
/* Purpose: Provides Interrupt Driven Timer Functionality                     */
/* File:    clock.c                                                           */
/* Author:  M. Thaler, ZHAW                                                         */
/******************************************************************************/

#define EOI_    0FF22h                      /* end of interrupt               */
#define TCUCON  0FF32h                      /* timer control register         */

#define T0CNT   0FF50h                      /* timer 0 count register         */
#define T0CMPA  0FF52h                      /* timer 0 compare register A     */
#define T0CMPB  0FF54h                      /* timer 0 compare register B     */
#define T0CON   0FF56h                      /* timer 0 control register       */

#define T1CNT   0FF58h                      /* timer 1 count register         */
#define T1CMPA  0FF5Ah                      /* timer 1 compare register A     */
#define T1CMPB  0FF5Ch                      /* timer 1 compare register B     */
#define T1CON   0FF5Eh                      /* timer 1 control register       */

#define T2CNT   0FF60h                      /* timer 2 count register         */
#define T2CMPA  0FF62h                      /* timer 2 compare register A     */
#define T2CON   0FF66h                      /* timer 2 control register       */

#define TIME_BASE 25                        /* time base set to 100us         */
#define MAX_SCALE 0XFFFF / TIME_BASE        /* TIME_BASE                      */


/******************************************************************************/
/* set clock: clock period = (100us * scale ) * Count                         */

void setClock(unsigned int scale, unsigned int Count) {

    unsigned int tmp;

    if (Count == 0)
        return;        /* do noting, if clock period is set 0   */

    asm    CLI;        /* disable interrupts during set up      */

    if (scale > MAX_SCALE)
        tmp = MAX_SCALE;
    else
        tmp = scale * TIME_BASE;

    /* timer 0 setup ---------------------------------------------------------*/
    
    asm    MOV     DX,   T0CNT          ; /* reset timer 0 count reg        */
    asm    XOR     AX,   AX             ;
    asm    OUT     [DX], AX             ;
    
    asm    MOV     DX,   T0CMPA         ; /* set timer 0 compare reg        */
    asm    MOV     AX,   Count          ; /* set Count (Delay)              */
    asm    OUT     [DX], AX             ;

    asm    MOV     DX,   T0CON          ; /* set timer control reg          */
    asm    MOV     AX,   0E009h         ; /* enable interrupt,prescaler     */
    asm    OUT     [DX], AX             ; /* and run continous              */

    /* setup timer 2 as pre-scaler -------------------------------------------*/

    asm    MOV     DX,   T2CNT          ; /* reset timer 2 count reg        */
    asm    XOR     AX,   AX             ;
    asm    OUT     [DX], AX             ;
    
    asm    MOV     DX,   T2CMPA         ; /* set timer 2 compare reg        */
    asm    MOV     AX,   tmp            ; /* set prescale value             */
    asm    OUT     [DX], AX             ;
 
    asm    MOV     DX,   T2CON          ; /* set timer 2 control reg        */
    asm    MOV     AX,   0C001h         ; /* (disable interrupts)           */
    asm    OUT     [DX], AX             ;
}

/******************************************************************************/
/* start the clock and enable interrupts                                      */

void startClock(void) {

    /* enable timer interrupts -----------------------------------------------*/
    
    asm    MOV  DX,   TCUCON            ; /* enable timer interrupt         */
    asm    XOR  AX,   AX                ;
    asm    OUT  [DX], AL                ;
    asm    MOV  DX,   EOI_              ; /* reset pending interrupts       */ 
    asm    MOV  AX,   8000h             ;
    asm    OUT  [DX], AX                ;
    asm    STI                          ; /* enable interrupts              */    
}


/******************************************************************************/
/* Stop Clock                                                                 */

void stopClock(void) {
    asm    MOV    DX,   T0CON           ;
    asm    MOV    AX,   40h             ; /* disable timer 0 interrupts     */
    asm    OUT    [DX], AX              ; 
    asm    MOV    DX,   T2CON           ; /* disable timer 2                */
    asm    OUT    [DX], AX              ;
    asm    MOV    DX,   EOI_            ; /* clear pending interrupts       */
    asm    MOV    AX,   8000h           ;
    asm    OUT    [DX], AL              ;
}

/******************************************************************************/
/* reset Clock                                                                */

void resetClock(void) {
    asm    MOV     DX,   T0CNT          ; /* timer 0 count register         */
    asm    MOV     CX,   T2CNT          ; /* timer 2 count register         */
    asm    XOR     AX,   AX             ;
    asm    CLI                          ; /* disable interrupt              */
    asm    OUT     [DX], AL             ; /* reset timer 0 count reg        */
    asm    XCHG    DX,   CX             ; /* exchange address               */
    asm    OUT     [DX], AL             ; /* reset timer 0 count reg        */
    asm    STI                          ;
}
/******************************************************************************/
