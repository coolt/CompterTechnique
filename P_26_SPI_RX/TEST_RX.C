/* ------------------------------------------------------------------

 * ------------------------------------------------------------------
 */

#include <dos.h>
#include "spi.h"

#define ACK_CHAR            0x06u
#define DC1_CHAR            0x11u
#define ESC_CHAR            0x1Bu
#define LENGTH              0x03u
#define CHECKSUM            0xCCu
#define COLOR				0x0Au

#define HEXPORT_ADDR        0x708u
#define SEG7_ADDR           0x0702u
#define LETTER_F            0x8Eu
#define LETTER_P            0x8Cu

#define KEYS_ADDR           0x0706u
#define KEY_MASK            0x0Fu

void displayResult(unsigned char response);
void waitForKeyPress(void);

void main(void) {

    unsigned char responseChar;

    //Default-Werte
    outportb(HEXPORT_ADDR, 0xFF);
    outport(SEG7_ADDR, LETTER_F);

    initSPI();

    while (1) {

        // Esc, T, I = Senden an Display
        sendCharToSPI(DC1_CHAR);
        sendCharToSPI(LENGTH);
        sendCharToSPI(ESC_CHAR);
        sendCharToSPI('T');
        sendCharToSPI('I');
        sendCharToSPI(CHECKSUM);

        responseChar = receiveCharFromSPI();
        displayResult(responseChar);
        waitForKeyPress();
    }
}

/*
 * Outputs the received character on the HEXPORT and checks whether it matches
 * the acknowledge character of the display. If it does then show a 'P' other-
 * wise show an 'F'
 */
void displayResult(unsigned char responseChar) {

    outportb(HEXPORT_ADDR, responseChar);

    if (responseChar == ACK_CHAR) {
        // test pass
        outport(SEG7_ADDR, LETTER_P);
    } else {
        // test failed
        outport(SEG7_ADDR, LETTER_F);
    }
}

/*
 * Wait for any of the 4 keys to be pressed and released again
 */
void waitForKeyPress(void) {
    while ( (inportb(KEYS_ADDR) & KEY_MASK) == KEY_MASK);   // wait for press
    while ( (inportb(KEYS_ADDR) & KEY_MASK) != KEY_MASK);   // wait for release
}
