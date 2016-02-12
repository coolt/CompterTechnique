//
//
//
#include <dos.h>

#define LED_ADDR         0x0700u
#define DIP_SWITCH_ADDR  0x0704u

//Vorwarddeklaration Assembler
extern void OUTWORD(unsigned int outValue, unsigned int outAddr);

//main
void main(void) {
    

    while (1) {
    	OUTWORD(0x55u, LED_ADDR );
    }
}

