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
 * --               for the basic control of the TFT-LCD display
 * --               EAeDIPTFT43-A. The interfaces of the functions
 * --               are described in the header file.
 * --
 * ------------------------------------------------------------------
 */

#include "CMD_LCD.H"

unsigned char initTerminal(void);

/*
 * according to description in header file
 */
unsigned char clearDisplay(void)
{
    unsigned char cmdBuffer[10];
    
    cmdBuffer[0] = 'D';
    cmdBuffer[1] = 'L';
  
    return writeCmdToDisplay(cmdBuffer,2);
}

/*
 * according to description in header file
 */
unsigned char initDisplay(void)
{
    initDisplayInterface();
    (void)initTerminal();
    (void)setDisplayColor(COLOR_BLACK, COLOR_BLACK);
    (void)setFontZoomFactor(1,1);
    (void)clearDisplay();
    return 0; // :TODO: fix return
}

/*
 * Sends an init Terminal command to the display. This initializes and
 * prints the version
 */
unsigned char initTerminal(void)
{
    unsigned char cmdBuffer[10];
    
    cmdBuffer[0] = 'T';
    cmdBuffer[1] = 'I';
  
    return writeCmdToDisplay(cmdBuffer,2);
}    

/* 
 * according to description in header file
 */
unsigned char setDisplayFont(unsigned char fontNumber)
{
    unsigned char cmdBuffer[10];
    
    cmdBuffer[0] = 'Z'; 
    cmdBuffer[1] = 'F';
    cmdBuffer[2] = fontNumber;
  
    return writeCmdToDisplay(cmdBuffer,3);
}

/*
 * according to description in header file
 */
unsigned char printTextOnDisplay(unsigned int xPosition, 
                                 unsigned int yPosition, char text[])
{
    int i;
    
    unsigned char cmdBuffer[255];
  
    cmdBuffer[0] = 'Z'; 
    cmdBuffer[1] = 'L';
    cmdBuffer[2] = xPosition & 0xFF;
    cmdBuffer[3] = (xPosition & 0xFF00) >> 8;
    cmdBuffer[4] = yPosition & 0xFF;
    cmdBuffer[5] = (yPosition & 0xFF00) >> 8;

    for (i = 0; text[i] != 0 && i < 254; i++) {
        cmdBuffer[i + 6] = text[i];
    }

    cmdBuffer[i + 6] = 0;
  
    return writeCmdToDisplay(cmdBuffer, i + 7);
}

/*
 * according to description in header file
 */
unsigned char setFontZoomFactor(unsigned char xZoomFactor, 
                                unsigned char yZoomFactor)
{
    unsigned char cmdBuffer[10];
    
    cmdBuffer[0] = 'Z'; 
    cmdBuffer[1] = 'Z';
    cmdBuffer[2] = xZoomFactor;
    cmdBuffer[3] = yZoomFactor;
    
    return writeCmdToDisplay(cmdBuffer,4);
}

/*
 * according to description in header file
 */
unsigned char setFontColor(unsigned char fontColor, 
                           unsigned char backgroundColor) 
{
    unsigned char cmdBuffer[10];
    
    // accept only values supported by display 
    if (fontColor > 32 || backgroundColor > 32 ){		//|| backgroundColor == 0
        return 1;
    }
    
    cmdBuffer[0] = 'F'; 
    cmdBuffer[1] = 'Z';
    cmdBuffer[2] = fontColor;
    cmdBuffer[3] = backgroundColor;
    
    return writeCmdToDisplay(cmdBuffer,4);
}

/*
 * according to description in header file
 */
unsigned char setDisplayColor(unsigned char fontColor, 
                           unsigned char backgroundColor) 
{
    unsigned char cmdBuffer[10];
    
    // accept only values supported by display 
    if (fontColor > 32 || backgroundColor > 32 ){	//|| backgroundColor == 0
        return 1;
    }
    
    cmdBuffer[0] = 'F'; 
    cmdBuffer[1] = 'D';
    cmdBuffer[2] = fontColor;
    cmdBuffer[3] = backgroundColor;
    
    return writeCmdToDisplay(cmdBuffer,4);
}

/*
 * according to description in header file
 */
unsigned char fillArea(unsigned int left, unsigned int top, 
                       unsigned int right, unsigned int bottom, 
                       unsigned char fillColor) 
{
    unsigned char cmdBuffer[20];

    cmdBuffer[0] = 'R'; 
    cmdBuffer[1] = 'F';
    cmdBuffer[2] = left & 0xFF;
    cmdBuffer[3] = (left & 0xFF00) >> 8;
    cmdBuffer[4] = top & 0xFF;
    cmdBuffer[5] = (top & 0xFF00) >> 8;
    cmdBuffer[6] = right & 0xFF;
    cmdBuffer[7] = (right & 0xFF00) >> 8;
    cmdBuffer[8] = bottom & 0xFF;
    cmdBuffer[9] = (bottom & 0xFF00) >> 8;
    cmdBuffer[10] = fillColor;

    return writeCmdToDisplay(cmdBuffer,11);
}

/*
 * according to description in header file
 */
unsigned char setCursorOnOff(unsigned char onOff) 
{
    unsigned char cmdBuffer[10];

    cmdBuffer[0] = 'T'; 
    cmdBuffer[1] = 'C';
    cmdBuffer[2] = onOff;
  
    return writeCmdToDisplay(cmdBuffer, 3);
}
