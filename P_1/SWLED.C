#include <dos.h>

#define LED_LOW_ADDR         0x0700u
#define LED_HIGH_ADDR        0x0701u
#define SEG7_ADDR            0x0702u
#define DIP_SWITCH_LOW_ADDR  0x0704u
#define DIP_SWITCH_HIGH_ADDR 0x0705u
#define TURN_SWITCH_ADDR     0x0706u
#define DATA_DISPLAY_ADDR    0x0708u

#define LIGHT_LEFT_LEDS      0x0Fu
#define LIGHT_RIGHT_LEDS     0xF0u


unsigned int wert;

void main(void) {

    while (1) {
        wert=inport(DIP_SWITCH_LOW_ADDR);
        outport(LED_LOW_ADDR,~wert);
    }
}
