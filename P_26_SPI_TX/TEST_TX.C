/* ------------------------------------------------------------------
 * ------------------------------------------------------------------
 */

#include <dos.h>
#include "spi.h"

#define SWITCH_LOW          0x0704u
#define LED_LOW             0x0700u
#define KEYS_ADDR           0x0706u
#define KEY_MASK            0x0Fu

void waitForKeyPress(void);

void main(void) {

    unsigned char byte;

    initSPI();

    while (1) {

    	// Wert über Switch eingeben (704)
        byte = inportb(SWITCH_LOW);
        sendCharToSPI(byte);

        // Ausgabe an LED
        outportb(LED_LOW, byte);
        waitForKeyPress();
    }
}


// Wait for any of the 4 keys to be pressed and released again

void waitForKeyPress(void) {
    while ( (inportb(KEYS_ADDR) & KEY_MASK) == KEY_MASK);   // wait for press
    while ( (inportb(KEYS_ADDR) & KEY_MASK) != KEY_MASK);   // wait for release
}
