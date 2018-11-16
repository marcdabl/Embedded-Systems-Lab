/*
 * fan_TC0_ints.c
 *
 *  Created on: 07/10/2016
 *      Author:
 */


#include <avr/io.h>
//#include <avr/iom328p.h>
#include <avr/interrupt.h>
#include<util/delay.h>

int echo = 0;
unsigned char microseg = 0;

// function to initialize TC0 (Timer/Counter0) and Interrupts
//-----------------------------------------------------------

void initTC1(){
	TCCR1A = 0x00;			// Normal mode
	TCCR1B |= (1<<CS10); 	// Prescaler = 1
	TIMSK1 |= (1<<TOIE1);	// enable Overflow Interrupts
	SREG |= 0x80;			// Global Interrupt Enable

}
void initPWM() {
	OCR2A = 0x00; //0%
	TCCR2A |= (1 << COM2A1); //Set non-inverting mode
	TCCR2A |= (1 << WGM21) | (1 << WGM20); // Fast PWM Mode
	TCCR2B |= (1 << CS21); 	// Prescaler = 8
}

// Interrupt Service Routine for TC0 Overflow
//-------------------------------------------

ISR(TIMER1_OVF_vect) {
	microseg += 16;
	echo = PINB & 0b00010000;
}

// Interrupt Service Routine for TC1 Overflow
//-------------------------------------------

// main program
//--------------

int dist_sensor(void) {

	// PB5 (connected to LED) is output
	DDRB = 0b00101100; //Set as output pin 13(led), pin 11(Fan), pin 10(Trigger)
	PORTB &= 0b11111011; 		// PB2 = 1 (Trigger)

	// initialize Timer/Counter0 and associated interrupts
	initTC1();
	initPWM();

	// forever loop
	while(1) { // empty loop!

		PORTB &= 0b11111011; 		// PB2 = 0 (Trigger)
		_delay_ms(5);	// wait 1 second
		PORTB |= 0b00000100; 		// PB2 = 1 (Trigger)
		_delay_ms(10);	// wait 1 second
		PORTB &= 0b11111011; 		// PB2 = 0 (Trigger)

		PORTB |= 0b00100000;		// PB5 = 1 (Led On)
		microseg = 0;
		while(echo==0 || microseg>100);
		microseg = 0;
		while(echo>0 || microseg>100);
		PORTB &= 0xDF;		// PB5 = 0 (Led Off)
		double dist = microseg/58;
		int PWMon = (dist-2)/400*255;
		OCR2A = PWMon;
	}

	return 0;
}


