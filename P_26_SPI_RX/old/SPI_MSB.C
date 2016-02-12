

#include <dos.h>
#include "SPI.h"

#define OUTPORT_ADDR        0x0703u
#define INPORT_ADDR         0x0707u


//Inizialiserungsfunktion
void initSPI(void)
{
    outportb(OUTPORT_ADDR, 0x80); // SS=1 / CLOCK=0 / MOSI=0
}

//Funktion Char senden
void sendCharToSPI(unsigned char value)
{	int i = 0;
	unsigned char copy = value;
	unsigned char out;		// Variable für Ausgabe


	//SS ist bereits auf 1 inizialisert durch init

	//Start: SS auf 0
	outportb(OUTPORT_ADDR, 0x00); // SS=0 / CLOCK=0 / MOSI=0

	//Bit auf MOSI-Kanal // SS=0 / CLOCK = 0 / MOSI = Wert MSB Variable
	for(i = 0; i < 8; i++){

		//MSB extrahieren
		copy = copy & 0x80;

		//Bit auf MOSI ausgeben
		if (copy = 0){
			outportb(OUTPORT_ADDR, 0x00); 	//SS=0 / CLOCK = 0 / MOSI = 0
		}
		else outportb(OUTPORT_ADDR, 0x01);	//SS=0 / CLOCK = 0 / MOSI = 1

		//Clock steigend, MOSI muss bleiben

		outportb(OUTPORT_ADDR, 0x01);		//SS=0 / CLOCK = 1 / MOSI = 1

		//etwas warten
	}

	//Ende: SS auf 1
	initSPI(void);



}




void main(){

	unsigned char a;
	a = 0x55;		//0101 0101

	//Inizialisierung eines Sendevorgangs (SS wird auf 1 gesetzt)
	initSPI();

	//Endlosschlaufe, Ausgabe Char
	for(;;){
		sendCharToSPI('a');
	}

}
