/* ------------------------------------------------------------------
 * -- Praktikum 206
 * -- Project     : CT2 lab - SPI Display
 * -- Description : Contains the implementations of the functions
 * --               to intialize the SPI and to write and read bytes
 * --               to/from the SPI
 * --
 * --
 * --	2013_04_06 Florian Mühlethaler & Claudia Griesser
 * --   Implementation von SPI Daten senden.
 *
 * --	2013_04_13 Florian Mühlethaler & Claudia Griesser
 * --	Implementation von SPI Daten empfangen.
 * ------------------------------------------------------------------
 */

#include <dos.h>
#include "SPI.h"

#define OUTPORT_ADDR        0x0703u
#define INPORT_ADDR         0x0707u
#define MASK_DATEN			0x01u
#define MASK_SCLK			0x40u
#define MASK_IDLE			0x80u

/* ------------------------------------------------------------------
 * -- Function implementations
 * ------------------------------------------------------------------
 */
 
/*
 * according to description in header file
 */
void initSPI(void)
{
    outportb(OUTPORT_ADDR, 0x80); // SS=1 / CLOCK=0 / MOSI=0
}

/*
 * according to description in header file
 */
void sendCharToSPI(unsigned char value)
{
    // --------- start of section to be implemented by students ---------
	unsigned char out = 0x00; 				// interne Variable / SS=0 / SCLK=0 / MOSI  = 0
	int i;

	for(i=7; i>=0; i--){				// 8 Bit übertragen
		out = MASK_DATEN & (value >> i);	// SS=0 / SCLK=0 / MOSI = Bit i
		outportb(OUTPORT_ADDR, out);		// Ausgabe Bit
		out = out | MASK_SCLK; 				// SS=0 / SCLK=1 / (MOSI = Bit i)
		outportb(OUTPORT_ADDR, out);		// Ausgabe Bit
	}

	//--- Datenausgabe beenden ---
	out = MASK_IDLE;						// SS=1 / SCLK=0 / MOSI=0
	outportb(OUTPORT_ADDR, out);			// Ausgabe Bit


    
    // --------- end of section to be implemented by students ---------- 
}

/*
 * according to description in header file
 */
unsigned char receiveCharFromSPI(void)
{
    // --------- start of section to be implemented by students ---------
		unsigned char out = 0x00; 				// interne Variable / SS=0 / SCLK=0 / MOSI  = 0
		unsigned char in = 0x00;				// Eingangsdaten von Slave
		unsigned char tmp = 0x00;
		int i;


		for(i=7; i>=0; i--){				// 8 Bit empfangen
			out = out & ~MASK_SCLK;				// SS=0 / SCLK=0 / MOSI =toggling
			outportb(OUTPORT_ADDR, out);		// Ausgabe Byte
			out = out ^ MASK_SCLK; 				// SS=0 / SCLK=toggeln (auf 1) / (MOSI = Bit i)
			outportb(OUTPORT_ADDR, out);		// Ausgabe Byte
			tmp = inportb(INPORT_ADDR);			// Daten von MISO einlesen
			in = in | ((tmp & MASK_DATEN) << i);	// Bit zu Datenbyte dazunehmen
		}

		//--- Datenausgabe beenden ---
		out = MASK_IDLE;						// SS=1 / SCLK=0 / MOSI=0
		outportb(OUTPORT_ADDR, out);			// Ausgabe Bit

		return in; 								// Daten an Aufrufer zurück geben


    
    // --------- end of section to be implemented by students ---------
}
