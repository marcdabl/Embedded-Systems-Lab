/*
 * led_blinking_timer0.c
 *
 *  Created on: 07/10/2016
 *      Author: stornil
 */

#include <avr/io.h>
//#include <avr/iom328p.h>


// function to initialize the Timer/Counter0 (TC0)
//------------------------------------------------

void init_TC0()
{
	TCCR0A = 0x00;			// Normal mode
	TCCR0B |= (1<<CS02);	// Prescaler = 256
}

// delay function (based on TC0)
//------------------------------

void delay()
{
	unsigned int i;
	for (i=1;i<=100;i++)
	{
		TCNT0 = 0;						// init count
		while((TIFR0 & (1<<TOV0))==0);	// wait overflow
		TIFR0 |= (1<<TOV0);				// clear the overflow flag (by writing a '1'!)
	}
}

// main program
//--------------

int led_blinking_TC0(void)
{

	// PB5 (connected to LED) is output
	DDRB = 0b00100000;

	// initialize Timer/Counter0
	init_TC0();

	// forever loop
	while(1)
	{

		PORTB |= 0x20;	// PB5=1 -> LED ON
		delay();		// wait
		PORTB &= 0xDF;	// PB5=0 -> LED OFF
		delay();		// wait

	}

	return 0;
}

