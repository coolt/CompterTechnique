/* ------------------------------------------------------------------
 * Vorgabe: Hardwaremässig ist Modus 0 verdrahtet
 * Datenübernahme bei erster STEIGENDER Flanke
 * ------------------------------------------------------------------
 */

#include <dos.h>
#include "SPI.h"		// Anstelle der Vorwarddeklaration dieser Funktionen, die öffentlich sein sollen
						// Nur Funktionen, die andere Programmteile auch benutzen wollen

#define MISO_IDX	0 	//Daten vom Display
#define MOSI_IDX	0
#define CLK_IDX		6
#define SS_IDX		7

#define OUTPORT_ADDR	0x0703u 	// Bus
#define INPORT_ADDR		0x0707u		// Bus
#define INIT_MASK	0x80  			// Inaktiver Status (SS ist '1'), sonsta alles auf 0


// -- Function


void initSPI(){
	outportb(OUTPORT_ADDR, INIT_MASK);
}


void sendCharToSPI(unsigned char value){
	int idx = 7; 						// index Shift-Variabel extrahieren der Bits
	unsigned char data = 0;

	// Value bitweise von MSB zu LSB extrahieren in Variable data
	// Parallel dazu über die Variable data die Steuersignale setzen

	for(idx = 7; idx >= 0; idx--) {
		data = ((value >> idx) & 0x01); // Shiften um Index und Bit extrahieren
		data &=~ (1 << CLK_IDX); 		// Clock auf 0 (Toggling Edge)
		data &=~ (1 << SS_IDX); 		// SS auf 0 = Start Kommunikation
		outportb(OUTPORT_ADDR, data); 	// Ausgabe Start Kommunikation

		data |= (0x01 << CLK_IDX); 		// Verodern => CLK auf 1 setzen (Sampling Edge: Datenübernahme!!)
		outportb(OUTPORT_ADDR, data);	// Augabe Bit

	}

	data = 0x80; 						// CLK einschlafen, SS auf 1 bis es wieder los geht
	outportb(OUTPORT_ADDR, data);
}


unsigned char receiveCharFromSPI(){
	int idx = 7; 						// Index-Shift Variable
	unsigned char r = 0;
	unsigned char data = 0;
	unsigned int tmp;
	
	//Start Kommunikation steuern
	data &=~ (1 << CLK_IDX); 			// Clk auf 0
	data &=~ (1 << SS_IDX); 			// SS auf 0 = Start Kommunikation
	outportb(OUTPORT_ADDR, data);		// Ausgabe Start Kommunikation


	for(idx = 7; idx >=0; idx--) {
		data &=~ (1 << CLK_IDX); 		// Clock auf 0 (Toggling Edge)
		outportb(OUTPORT_ADDR, data);	// Ausgabe

		tmp = inportb(INPORT_ADDR); 	// Antwort einlesen (Byte)

		data |= (1 << CLK_IDX); 		// Clock auf 1 => Datenübernahme
		outportb(OUTPORT_ADDR, data);	// Ausgabe Toggling Edge

		// Die acht Bits in der Variable r zu einem Byte schrittweise zusammenfügen

		r|=((tmp & 0x01) << idx);		// Aus tmp Bitweise Daten in r schreiben
	}

	data &=~ (0x01 << CLK_IDX); 		// Clk einschlafen
	outportb(OUTPORT_ADDR, data);

	return r;
}
