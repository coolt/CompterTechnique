///////////////////////////////////////////////////////////////////////////
// Course:      CT1
// Description: Praktikum 12
//             Wenn die Taste 0 gedrückt ist, liest dads Programm die Adresse ein.
//             Gleichzeitig wird die Grösse blockiert (?) and fillPattern vom  Drehschalter
//             Danach wird die externe Funktion FILLMEM aufgerufen.
//              
// Author:      A.Ruest/ZHAW
// Date:        11/2011
//////////////////////////////////////////////////////////////////////////

#include <dos.h>

#define LED_LOW_ADDR         0x0700u
#define LED_HIGH_ADDR        0x0701u
#define SEG7_ADDR            0x0702u
#define DIP_SWITCH_LOW_ADDR  0x0704u
#define DIP_SWITCH_HIGH_ADDR 0x0705u
#define KEYS_ADDR            0x0706u
#define DATA_DISPLAY_ADDR    0x0708u

#define KEY0_MASK            0x01u

//Deklarationen
extern unsigned char 		//externe Funktion, muss in Assembler implementiert werden
        FILLMEM(unsigned int startAddress, unsigned int blockSize, 
                unsigned int fillPattern);

unsigned char key0StrokeDetected(void);
unsigned int readSwitches(void);

//main
void main(void) {
    unsigned int startAddress, blockSize, fillPattern;
    outport(DATA_DISPLAY_ADDR,0);

    while (1) {
        startAddress = readSwitches();
        blockSize = readSwitches();
        fillPattern = readSwitches();
        FILLMEM(startAddress, blockSize, fillPattern);
    }
} //Ende main

// Methode readSwitches: 	Returns the value on the dip switches in the moment
//               			that key0 is pressed
unsigned int readSwitches(void) {
    unsigned int readValue;
    
    while (!key0StrokeDetected());
    readValue = inport(DIP_SWITCH_LOW_ADDR);
    outport(DATA_DISPLAY_ADDR,readValue);
    return readValue;
}    
        
// Methode key0StrokeDetected: Returns true if key 0 has been newly pressed
//                     			i.e. if the bit value transitions from 1 to 0
unsigned char key0StrokeDetected(void) {
    static unsigned char lastKeysVal = 0xFFu;
    unsigned char keysVal;
    unsigned char bitsWithOneToZero;
    
    keysVal = inportb(KEYS_ADDR);
    bitsWithOneToZero = lastKeysVal & ~keysVal;
    lastKeysVal = keysVal;
    return bitsWithOneToZero & KEY0_MASK;
    }
