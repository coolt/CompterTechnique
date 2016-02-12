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
 * -- Description : Main program used as a sandbox to experiment with
 * --               the display commands.
 * --               The programm does not check the return values of
 * --               the display functions.
 * --
 * ------------------------------------------------------------------
 */

#include "CMD_LCD.H"
#include <dos.h>

void main(void) {

    initDisplay();
    (void)setFontZoomFactor(3,2);
    (void)setFontColor(COLOR_GREEN, COLOR_TRANSPARENT);
    (void)setDisplayFont(FONT_SWISS30_BOLD_PROP);
    (void)printTextOnDisplay(50, 25, "3:0");
    (void)fillArea(50, 80, 435, 82, COLOR_GREEN);       // draw line
    (void)setCursorOnOff(CURSOR_OFF);

    while (1) {
    }
}
