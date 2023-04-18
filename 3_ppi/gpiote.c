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

   
   // ------------ GPIOTE ----------------------


    // Set up event on A button (pin 0.14)
    GPIOTE->CONFIG[5] = 0x1 | (0xE << 8) | (0x2 << 16);

     // setup pins as task, no polarity and initial output 0
    GPIOTE->CONFIG[0] = 0x3 | (0x1C << 8) | (0x3 << 16) |(0x1 << 20); // pin 28
    GPIOTE->CONFIG[1] = 0x3 | (0xB << 8) | (0x3 << 16) | (0x1 << 20); // pin 11
    GPIOTE->CONFIG[2] = 0x3 | (0x1F << 8) | (0x3 << 16) | (0x1 << 20); // pin 31
    GPIOTE->CONFIG[3] = 0x3 | (0x5 << 8) | (0x1 << 13) | (0x3 << 16) | (0x1 << 20); // pin 5
    GPIOTE->CONFIG[4] = 0x3 | (0x1E << 8) | (0x3 << 16) | (0x1 << 20); // pin 30




}