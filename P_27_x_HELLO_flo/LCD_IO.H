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
 * -- Description : Contains the prototypes and interface descriptions 
 * --               of the functions to write and read frames from and 
 * --               to the TFT-LCD display EAeDIPTFT43-A.
 * --
 * ------------------------------------------------------------------
 */

/*
 * The function brings the display interface to a defined state. After
 * the execution the display is ready for communication, i.e. writing to
 * or reading from.
 */
void initDisplayInterface(void);

/*
 * The function triggers a readout of the display buffer and stores the 
 * received data in the string pointed to by readBuffer.
 * The function returns the number of characters read; returns zero in 
 * case of an error
 */
unsigned char readDisplayBuffer(unsigned char *readBuffer);

/*
 * The function receives a command buffer in the form of a character string.
 * It adds the required protocol overhead and uses the SPI to write the
 * complete frame to the display. Afterwards it waits for the acknowledge
 * character from the display.
 *
 * The transmitted frame on the SPI consists of the required control characters
 * (DC1, len and ESC) followed by the contents of the specified command buffer
 * and the checksum (bcc).
 *
 * The function returns zero if the operation is successful, i.e. if an 
 * acknowledge character is received from the display; It returns
 * one otherwise, i.e. if no acknowledge character is received from the display
 */
unsigned char writeCmdToDisplay(const unsigned char *cmdBuffer,
                                unsigned char length);
