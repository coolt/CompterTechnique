/* ------------------------------------------------------------------
 * --  _____       ______  _____                                    -
 * -- |_   _|     |  ____|/ ____|                                   -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems    -
 * --   | | | '_ \|  __|  \___ \   Zuercher Hochschule Winterthur   -
 * --  _| |_| | | | |____ ____) |  (University of Applied Sciences) -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland     -
 * ------------------------------------------------------------------
 * --
 * -- Project     : CT2 lab - SPI Display
 * -- Description : Main program used to verify the SPI driver, i.e.
 * --               the sending and receiving of characters
 * --               Send the sequence of characters that is defined to
 * --               initialize the display and check the acknowledge
 * --               character
 * --
 * ------------------------------------------------------------------
 */

#include <dos.h>
#include "spi.h"

#define ACK_CHAR            0x06u
#define DC1_CHAR            0x11u
#define ESC_CHAR            0x1Bu
#define LENGTH              0x03u
#define CHECKSUM            0xCCu

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

    outportb(HEXPORT_ADDR,0xFF);
    outport(SEG7_ADDR, LETTER_F);   // default is fail

    initSPI();

    while (1) {
        // send command characters to reset display
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
