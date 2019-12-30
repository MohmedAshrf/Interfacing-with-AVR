#define F_CPU 8000000UL
#include <avr/io.h>
#include "util/delay.h"
#include <avr/interrupt.h>

int main(void)
{
	sei(); // enable the global interrupt.//SREG |= (1<<SRE); // enable the global interrupt.

	DDRF |= (1<<PF1); // make PF1 as an output.
	PORTF |= (1<<PF1); //Enable the LEDs by make PF1 high.
	
	DDRA = 0xFF; //make all LEDs as an output.
	PORTA |= 0x00; // close all LEDs.
	
	DDRD &= ~ 0x03; // make PD0 and PD1 as Inputs.
	PORTD |=(1<<PD0); //pull up resistor to PD0.
	PORTD |=(1<<PD1); //pull up resistor to PD1.
	
	EIMSK |= (1<<INT0); //make PD0 an interrupt.
	EIMSK |= (1<<INT1); //make PD1 an interrupt.
	EICRA |= 0x00;		 //make INT0 and INT1 as interrupt at the falling edge. (1010)
	
	while(1)
	{
		_delay_ms(100);
		PORTA |= 0xff; // open all LEDs.
		_delay_ms(100);
	}
}
ISR(INT0_vect){
	int i;
	PORTA &= ~ 0xff;		  //set all LEDs to be off.
	for(i =0;i<=5;i++ ){
		PORTA |= (1<<i);      //set the current LED to be on.
		PORTA |= (1<<(i+2));  //set the current+2 LED to be on.
		_delay_ms(100);
		PORTA &= ~(1<<i);	  //set the current LED to be off.
		PORTA &= ~(1<<(i+2)); //set the current+2 LED to be off.
		_delay_ms(100);
	}
}
ISR(INT1_vect){
	int i;
	PORTA &= ~ 0xff;		  //set all LEDs to be off.
	for(i =5;i>=0;i-- ){
		PORTA |= (1<<i);      //set the current LED to be on.
		PORTA |= (1<<(i+2));  //set the current+2 LED to be on.
		_delay_ms(100);
		PORTA &= ~(1<<i);	  //set the current LED to be off.
		PORTA &= ~(1<<(i+2)); //set the current+2 LED to be off.
		_delay_ms(100);
	}
}