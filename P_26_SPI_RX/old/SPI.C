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
 * --               to intialize the SPI and to write and read bytes
 * --               to/from the SPI
 * --
 * ------------------------------------------------------------------
 */

#include <dos.h>
#include "SPI.h"
#include <stdio.h>
#include <util/delay.h>

#define OUTPORT_ADDR        0x0703u
#define INPORT_ADDR         0x0707u

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
	unsigned char out = 0x00;
	unsigned char copy;
	unsigned char mask_bit = 0x01;
//	unsigned char mask_mosi = 0xFE;
	unsigned char mask_clock = 0x40;
	unsigned char mask_clock_0 = 0xBF;
	int i;

	// Start: SS down
	outportb(OUTPORT_ADDR, out);

	//Einzelne Bits der Variable über Shiften auslesen ! Beginn mit MSB

		for(i = 7; i <=0; i--) {

			copy = value >> i;
			copy = copy & mask_bit;

			//Ausgabe
			out = copy | mask_clock; // SS = 0, Clk = 1, extrahiertes Bit bleibt
			outportb(OUTPORT_ADDR, out);

			delay_ms (100);

			// Flanke Clock nach unten ziehen (erst hier, damit genügend Zeit zwischen hinaufsetzen und hinabsetzn
			out = out  & mask_clock_0;
			outportb(OUTPORT_ADDR, out);

			}

		//SS wieder auf 1
		initSPI();
    // --------- end of section to be implemented by students ----------
}

/*
 * according to description in header file
 */
unsigned char receiveCharFromSPI(void)
{
    // --------- start of section to be implemented by students ---------

	return 0;

    // --------- end of section to be implemented by students ---------
}

void main(){

	//Inizialisierung
	initSPI();

	//Endlosschlaufe, Ausgabe Char
	for(;;){
		sendCharToSPI('a');
	}

}

// Wenn Bit = 0, dann auf MOSI ausgeben
//			if(!copy){
//				out = out & mask_mosi;
//			}
//			else out = out | mask_bit;


// Ausgabe
//			outportb(OUTPORT_ADDR, out);

// bei steigendem clock
//			out = out | mask_clock;
//			outportb(OUTPORT_ADDR, out);
