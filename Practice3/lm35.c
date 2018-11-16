/*
 * lm35.c
 *
 *  Created on: 22/09/2016
 *      Author: stornil
 */

#include <avr/io.h>
#include <util/delay.h>

// function to initialize the ADC
//-------------------------------

void init_adc()
{
	ADMUX = (1<<REFS0);					// Vref = AVcc = 5V;
	ADCSRA = (1<<ADEN)|(7<<ADPS0);		// ADC enabled; Prescaler=128!
}

// function to obtain a measurement using the ADC
//-----------------------------------------------

unsigned int read_adc(unsigned int channel)
{
	unsigned char adch,adcl;
	unsigned int adc;

	// select input channel (0-7)
	channel = channel & 0b00000111;
	ADMUX |= channel;

	// start single conversion
	ADCSRA |= (1<<ADSC);

	// wait for conversion to complete (ADIF=1)
	while((ADCSRA & (1<<ADIF))==0);

	// clear ADIF by writing '1' to it
	ADCSRA |= (1<<ADIF);

	// return ADC value
	adcl = ADCL;
	adch = ADCH;
	adc = (adch<<8)|adcl;
	return(adc);
}

// main program
//-------------

int lm35()
{
	// variables
	unsigned int adc_value;
	float millivolts;
	float celsius;

	// PB5 (connected to LED) is output
	DDRB = (1<<PB5);

   // initialize ADC
   init_adc();

   // infinite loop
   while(1)
   {

      // obtain a measurement from channel 0
      adc_value = read_adc(0);

      // convert to degrees Celsius
      millivolts = (adc_value/1024.0)*5000;   // 10 bit ADC; Vref=5V
      celsius = millivolts/10;                // 10mV / �C

      // timed loop
      _delay_ms(750);	// wait 1 second

      // LED blink
      PORTB |= (1<<PB5);
      _delay_ms(250);
      PORTB &= ~(1<<PB5);

   }
   return 0;
}

