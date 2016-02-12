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
 * --               of the functions to intialize the SPI and to write
 * --               and to read bytes to/from the SPI
 * --
 * ------------------------------------------------------------------
 */

/* ------------------------------------------------------------------
 * -- Function prototypes
 * ------------------------------------------------------------------
 */
 
/*
 * set default outputs for CPOL = 0, CPHA = 0 and  DORD = 0
 */
void initSPI(void);

/*
 * Send the character given by the parameter value out on the SPI
 */
void sendCharToSPI(unsigned char value);

/*
 * Receive a character on the SPI
 */
unsigned char receiveCharFromSPI(void);
