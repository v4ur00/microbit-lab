#include "gpiote.h"
#include "gpio.h"

void init_gpiote() {

    // ------------- GPIO -------------------
    // configure ground pins
    GPIO0->PIN_CNF[28] = 1; //Col 1
	GPIO0->PIN_CNF[11] = 1; //Col 2
	GPIO0->PIN_CNF[31] = 1; //Col 3
	GPIO1->PIN_CNF[5] = 1;  //Col 4
	GPIO0->PIN_CNF[30] = 1; //Col 5 

    GPIO0->OUTCLR = (1 << 28) | (1 << 11) | (1 << 31) | (1 << 5) | (1 << 30);

   
   // ------------ GPIOTE ----------------------


    // Set up event on A button (pin 0.14)
    GPIOTE->CONFIG[5] = 0x1 | (0xE << 8) | (0x2 << 16);

     // setup pins as task, no polarity and initial output 1
    GPIOTE->CONFIG[0] = 0x3 | (0x15 << 8) | (0x3 << 16) | (0x1 << 20); // pin 21
    GPIOTE->CONFIG[1] = 0x3 | (0x16 << 8) | (0x3 << 16) | (0x1 << 20); // pin 22
    GPIOTE->CONFIG[2] = 0x3 | (0x0F << 8) | (0x3 << 16) | (0x1 << 20); // pin 15
    GPIOTE->CONFIG[3] = 0x3 | (0x18 << 8) | (0x3 << 16) | (0x1 << 20); // pin 24
    GPIOTE->CONFIG[4] = 0x3 | (0x13 << 8) | (0x3 << 16) | (0x1 << 20); // pin 19


}