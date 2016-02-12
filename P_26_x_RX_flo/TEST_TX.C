/* ------------------------------------------------------------------
 * --
 * -- Project     : CT2 lab - SPI Display
 * -- Description : Main program
 * --
 * --               Used to verify the sending of characters in the
 * --               SPI driver.
 * --
 * --               Send out the character read from the dip_switches
 * --               on port 0x0704. Wait for a key press on port 0x0706
 * --               and restart.
 * --
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
        byte = inportb(SWITCH_LOW);
        sendCharToSPI(byte);
        outportb(LED_LOW, byte);
        waitForKeyPress();
    }
}

/*
 * Wait for any of the 4 keys to be pressed and released again
 */
void waitForKeyPress(void) {
    while ( (inportb(KEYS_ADDR) & KEY_MASK) == KEY_MASK);   // wait for press
    while ( (inportb(KEYS_ADDR) & KEY_MASK) != KEY_MASK);   // wait for release
}
