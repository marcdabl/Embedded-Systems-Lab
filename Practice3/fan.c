/*
 * fan_TC0_ints.c
 *
 *  Created on: 07/10/2016
 *      Author:
 */


#include <avr/io.h>
//#include <avr/iom328p.h>
#include <avr/interrupt.h>

// function to initialize TC0 (Timer/Counter0) and Interrupts
//-----------------------------------------------------------

void init_TC0_ints(){
	TCCR0A = 0x00;			// Normal mode
	TCCR0B |= (1<<CS02); 	// Prescaler = 256
	TIMSK0 |= (1<<TOIE0);	// enable Overflow Interrupts
	SREG |= 0x80;			// Global Interrupt Enable

}
void init_PWM() {
	OCR2A = 0x00; //0%
	TCCR2A |= (1 << COM2A1); //Set non-inverting mode
	TCCR2A |= (1 << WGM21) | (1 << WGM20); // Fast PWM Mode
	TCCR2B |= (1 << CS21); 	// Prescaler = 8
}

// Interrupt Service Routine for TC0 Overflow
//-------------------------------------------

ISR(TIMER0_OVF_vect) {

	static unsigned char i=0;
	i++;
	if (i==244) {
		i = 0;
			int PWMon = OCR2A+15;
			if(PWMon > 255) PWMon = 255;
			OCR2A = PWMon;
	}
}

// Interrupt Service Routine for TC1 Overflow
//-------------------------------------------

// main program
//--------------

int fan(void) {

	// PB5 (connected to LED) is output
	DDRB = 0b00101000;

	// initialize Timer/Counter0 and associated interrupts
	init_TC0_ints();
	init_PWM();

	// forever loop
	while(1); // empty loop!

	return 0;
}


