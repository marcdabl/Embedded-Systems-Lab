
/* blinking_led.c
 *
 *  Created on: Nov 5, 2018
 *      Author: Embedded Group:
 *      - Asensio, Javi
 *      - Conceiçao, Jose Pedro
 *      - Dalmasso, Marc
 */

#include<avr/io.h>
#include<util/delay.h>

int blinking_led(void) {

	DDRB = 0b00100000;

	// forever loop
	while(1) {
		PORTB |= 0x20; 		// PB5 = 1 -> LED ON
							//PORTB |= 0b00100000;
		_delay_ms(1000);	// wait 1 second
		PORTB &= 0xDF;		// PB5 = 0 -> LED OFF
							//PORTB &= 0b11011111;
		_delay_ms(1000);	// wait 1 second
	}

	return 0;
}
