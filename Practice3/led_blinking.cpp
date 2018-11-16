/*
 * main.cpp
 *
 *  Created on: 31/08/2016
 *      Author: stornil
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{

	DDRB = 0b00100000; 		// PB5 (connected to LED) is output

	// forever loop
	while(1)
	{
		PORTB |= 0x20; 		// PB5=1 -> LED ON
		_delay_ms(1000);	// wait 1 second
		PORTB &= 0xDF;		// PB5=0 -> LED OFF
		_delay_ms(1000);	// wait 1 second
	}

	return 0;
}
