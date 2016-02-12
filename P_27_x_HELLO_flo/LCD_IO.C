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
 * -- Description : Contains the implementations of the functions
 * --               to write and read frames from and to the TFT-LCD 
 * --               display EAeDIPTFT43-A.
 * --
 * ------------------------------------------------------------------
 */

#include <dos.h>
#include "SPI.H"
#include "LCD_IO.H"

#define ACK_CHAR            0x06u
#define NAK_CHAR			0x15u
#define DC1_CHAR            0x11u
#define DC2_CHAR            0x12u
#define ESC_CHAR            0x1Bu
#define ONE_CHAR            0x01u
#define OUTPORT_ADDR        0x0703u
#define INPORT_ADDR         0x0707u

#define NOTHING_RECEIVED   0

enum Boolean {FALSE = 0, TRUE = 1};
enum ReturnValues {SUCCESS = 0, ERRORCODE = 1};

/* ------------------------------------------------------------------
 * -- Function prototypes
 * ------------------------------------------------------------------
 */
void sendReadDisplayBufferRequest(void);
unsigned char displayHasDataToSend(void);

/* ------------------------------------------------------------------
 * -- Function implementations
 * ------------------------------------------------------------------
 */

/*
 * according to description in header file
 */
void initDisplayInterface(void)
{
    initSPI();
}

/*
 * according to description in header file
 */
unsigned char readDisplayBuffer(unsigned char *readBuffer) 
{

    // --------- start of section to be implemented by students ---------
    

    
    // --------- end of section to be implemented by students ---------- 
}

/*
 * according to description in header file
 */
unsigned char writeCmdToDisplay(const unsigned char *cmdBuffer,
                                unsigned char length)
{

    // --------- start of section to be implemented by students ---------
    
	// Variablen
	unsigned char bcc= 0;		// Checksumme
	unsigned char i = 0;
    unsigned char charFromDisp = 0;		// Char von Display
	unsigned char ret;				// temp für Switch-Case

	// Sende-Vorgang
	sendCharToSPI(DC1_CHAR); 	// Sende Start-Sequenz
    bcc += DC1_CHAR;			// bcc Checksumme
	sendCharToSPI(length + 1);		// Länge mitschicken (da - 1 + 1 =0, belassen... )
	bcc += (length + 1);				// bcc Checksumme
	sendCharToSPI(ESC_CHAR);	// ESC-Zeichen senden
	bcc += ESC_CHAR;			// bcc Checksumme

    for( i = 0; i < length; i++ ){		// nur bis length-1, weil /0 Zeichen nicht mit soll
    	sendCharToSPI(cmdBuffer[i]); 	// Zeichen an Position i senden
    	bcc += cmdBuffer[i];			// bcc Checksumme
    }


    sendCharToSPI(bcc);			// Checksumme senden

    // Prüfen auf Acknowledge
    charFromDisp = receiveCharFromSPI();

    if(charFromDisp = ACK_CHAR){
    	ret = SUCCESS;
    }
    else {
    	ret = ERRORCODE;
    }

    return ret; // Auswertung zurückgeben


    
    // --------- end of section to be implemented by students ---------- 
}

/*
 * The function checks the SBUF pin of the display. It returns TRUE if the pin 
 * indicates that the display has data to send; FALSE otherwise
 */
unsigned char displayHasDataToSend(void) 
{
    return ((inportb(INPORT_ADDR) & 0x80) == 0x80) ? FALSE : TRUE;
}
    
/*
 * Assemble and send a packet to trigger the reading of the display buffer
 * Uses the sequence "<DC2>, 0x01, 0x53, checksum" according to datasheet
 */
void sendReadDisplayBufferRequest() 
{
    // --------- start of section to be implemented by students ---------


  
    // --------- end of section to be implemented by students ---------- 
}
