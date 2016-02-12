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
 * -- Description : Contains constants and function prototypes 
 * --               for the basic control functions of the TFT-LCD
 * --               display EAeDIPTFT43-A
 * -- Note        : This header file and its associated implementation 
 * --               contains only a very limited number of commands
 * --               supported by the display. It is not intended to
 * --               be a fully featured device driver
 * --
 * ------------------------------------------------------------------
 */

#include "LCD_IO.H"

/* ------------------------------------------------------------------
 * -- constants
 * ------------------------------------------------------------------
 */

/* 
 * display specific, predefined font numbers according to datasheet
 */
#define FONT_4x6_MONO           (unsigned char) 1
#define FONT_6x8_MONO           (unsigned char) 2
#define FONT_7x12_MONO          (unsigned char) 3
#define FONT_GENEVA10_PROP      (unsigned char) 4
#define FONT_CHICAGO14_PROP     (unsigned char) 5
#define FONT_SWISS30_BOLD_PROP  (unsigned char) 6
#define FONT_BIGZIF50           (unsigned char) 7
#define FONT_BIGZIF100          (unsigned char) 8
 
/* 
 * display specific, predefined color numbers according to datasheet
 */ 
#define COLOR_TRANSPARENT (unsigned char) 0
#define COLOR_BLACK       (unsigned char) 1
#define COLOR_BLUE        (unsigned char) 2
#define COLOR_RED         (unsigned char) 3
#define COLOR_GREEN       (unsigned char) 4
#define COLOR_MAGENTA     (unsigned char) 5
#define COLOR_LIGHT_BLUE  (unsigned char) 6
#define COLOR_YELLOW      (unsigned char) 7
#define COLOR_WHITE       (unsigned char) 8

/* 
 * Turn the cursor on or off
 */ 
#define CURSOR_OFF (unsigned char) 0
#define CURSOR_ON  (unsigned char) 1

/* ------------------------------------------------------------------
 * -- Function prototypes
 * ------------------------------------------------------------------
 */

/* 
 * Clear the display by filling it with its background color
 * Return zero on success; non-zero otherwise
 */
unsigned char clearDisplay(void);

/*
 * The interface to the display is initialized and the display is brought
 * into a defined initial state
 */
unsigned char initDisplay(void);

/* 
 * Set the font on the display to one of the display specific font 
 * numbers as outlined in the enum Fonts.
 * Return zero on success; non-zero otherwise
 */
unsigned char setDisplayFont(unsigned char fontNumber);

/* 
 * Set the zoom factors for a font on the display. The factors in the  
 * range from 1 to 8 can be set individually for x and y directions.
 * Return zero on success; non-zero otherwise
 */
unsigned char setFontZoomFactor(unsigned char xZoomFactor, 
                                unsigned char yZoomFactor);

/* 
 * Set the color of the Font and its background to one of the display  
 * specific colors as outlined in the enum Colors.
 * Return zero on success; non-zero otherwise
 */                                
unsigned char setFontColor(unsigned char fontColor, 
                           unsigned char backgroundColor);

/* 
 * Set the color of the TouchPanel  
 * Return zero on success; non-zero otherwise
 */                           
unsigned char  setTouchPanelColor(unsigned char normalEdgeInside,
                                  unsigned char normalEdgeOutside,
                                  unsigned char normalFill,
				  unsigned char selectEdgeInside,
                                  unsigned char selectEdgeOutside,
                                  unsigned char selectFill);


/* 
 * Set the Displaycolor of the font and its background.  
 * specific colors as outlined in the enum Colors.
 * Return zero on success; non-zero otherwise
 */  
unsigned char setDisplayColor(unsigned char fontColor, 
                              unsigned char backgroundColor);

/*
 * Print the zero terminated string specified by text[] at the coordinates
 * specified by xPosition and yPosition. At most 254 characters can be 
 * printed.
 * Return zero on success; non-zero otherwise
 */
unsigned char printTextOnDisplay(unsigned int xPosition, 
                                 unsigned int yPosition, char text[]);
                                 
/*
 * Fill the area specified by the top-left corner and the bottom-right
 * corner with the specified color from the enum Colors
 * Return zero on success; non-zero otherwise
 */                           
unsigned char fillArea(unsigned int left, unsigned int top, 
                       unsigned int right, unsigned int bottom, 
                       unsigned char fillColor);
    
/*
 * Turn the cursor on (CURSOR_ON) or off (CURSOR_OFF)
 * Return zero on success; non-zero otherwise
 */   
unsigned char setCursorOnOff(unsigned char onOff);
