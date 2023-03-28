#include "uart.h"
#include "gpio.h"

int main(void) {
    // initialize system
    gpio_init();
    uart_init();

    int sleep = 0;
	while(1){

        /* Check if button B is pressed;
		 * turn on LED matrix if it is. */
		if(!(GPIO0->IN & (1 << 23))) {
			gpio_lights_on();
            uart_send('B');
            sleep = 10000;
		    while(--sleep);
            gpio_lights_off();

		}
		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */
		if(!(GPIO0->IN & (1 << 14))) {
			gpio_lights_on();
            uart_send('A');
            sleep = 10000;
		    while(--sleep);
            gpio_lights_off();
		}
		

		sleep = 10000;
		while(--sleep);
	}
}