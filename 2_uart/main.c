#include "uart.h"
#include "gpio.h"
#include <stdio.h>

ssize_t _write(int fd, const void *buf, size_t count){
	char * letter = (char *)(buf);
	for(int i = 0; i < count; i++){
		uart_send(*letter);
		letter++;
	}
	return count;
}

ssize_t _read(int fd, void *buf, size_t count){
	char *str = (char *)(buf);
	char letter;
	do {
		letter = uart_read();
	} while(letter == '\0');
	*str = letter;
	return 1;
}

int main(void) {
    // initialize system
    gpio_init();
    uart_init();

	int light_on = 0;

    int sleep = 0;


	/*
	sleep = 10000;
	while(--sleep);

	iprintf("Skriv inn et heltall\n\r");

	int answered = 0;
	char* first_number;
	char* second_number;
	while (!answered) {
		scanf("%29s", first_number);
		answered = 1;
	}

	answered = 0;
	while (!answered) {
		scanf("%29s", second_number);
		answered = 1;
	}
	int sum = first_number + second_number;

	iprintf("The sum of %d and %d is %d\n\r", first_number, second_number, sum);
	*/

	while(1){

        /* Check if button B is pressed;
		  turn on LED matrix if it is. */
		if(!(GPIO0->IN & (1 << 23))) {
			gpio_lights_on();
            iprintf("The average grade in TTK%d was in %d and %d: %c\n\r", 4235, 2019, 2018, 'C');
            sleep = 10000;
		    while(--sleep);
            gpio_lights_off();
			light_on = 0;

		}
		/* Check if button A is pressed;
		  turn off LED matrix if it is. */
		if(!(GPIO0->IN & (1 << 14))) {
			gpio_lights_on();
            iprintf("AB\n\r");
            sleep = 10000;
		    while(--sleep);
            gpio_lights_off();
			light_on = 0;
		}

		if (uart_read() != '\0') {
			if (light_on) {
				gpio_lights_off();
				light_on = 0;
			} else {
				gpio_lights_on();
				light_on = 1;
			}

		}


		

		sleep = 10000;
		while(--sleep);
	}
}