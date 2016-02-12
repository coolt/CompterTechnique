/* ------------------------------------------------------------------
 * ------------------------------------------------------------------
 */

#include <dos.h>
#include "SPI.H"
#include "LCD_IO.H"

#define ACK_CHAR            0x06u
#define DC1_CHAR            0x11u
#define DC2_CHAR            0x12u
#define ESC_CHAR            0x1Bu
#define ONE_CHAR            0x01u
#define OUTPORT_ADDR        0x0703u
#define INPORT_ADDR         0x0707u
#define COLOR         		0x0Au
#define CHECKSUM            0xC4u // = DC1, lenght, ESC, D, F, Color
#define NOTHING_RECEIVED   0

enum Boolean {FALSE = 0, TRUE = 1};
enum ReturnValues {SUCCESS = 0, ERRORCODE = 1};

/* ------------------------------------------------------------------
 * -- Function prototypes
 * ------------------------------------------------------------------
 */
void sendReadDisplayBufferRequest();
unsigned char displayHasDataToSend();


// Function implementations

void initDisplayInterface(){
    initSPI();
}

unsigned char readDisplayBuffer(unsigned char *readBuffer){   // noch präzise IMPLEMENTIEREN
	unsigned char c;
    return c;
}


unsigned char writeCmdToDisplay(const unsigned char *cmdBuffer, unsigned char length){

	    unsigned char char_Displ = 0;
		unsigned char ret;				// temp für Switch-Case
		unsigned char check = 0;		// Checksumme kontinuierlich bilden
		unsigned char i = 0;

		// Kommunikationsstruktur: DC1, Length, Data: Esc_Char, Chequsumme
		// Jedes mal parallel Chequsumme bilden
		sendCharToSPI(DC1_CHAR);
		check = check + DC1_CHAR;

		sendCharToSPI(length + 1);		// sendCharToSPI(4);
		check = check + (length + 1);

		sendCharToSPI(ESC_CHAR);		// sendCharToSPI('D');
		check = check + ESC_CHAR;

										// sendCharToSPI('F');

										// sendCharToSPI(COLOR);

	    for( i = 0; i < length; i++ ){
	    	sendCharToSPI(cmdBuffer[i]);
	    	check = check + cmdBuffer[i];
	    	}

	    // Checksumme übermitteln
	    sendCharToSPI(check);

	    // Prüfen auf Acknowledge
	    char_Displ = receiveCharFromSPI();

	    if(char_Displ = ACK_CHAR){
	    	ret = SUCCESS;
	    	}
	    else {
	    	ret = ERRORCODE;
	    	}

	    return ret; // Auswertung zurückgeben

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

}
