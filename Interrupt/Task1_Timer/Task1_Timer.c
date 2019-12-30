#include <avr/io.h>
#include <avr/interrupt.h> //to use interrupts

void delay_sec(int);
void delayOVE(int);
void delayCTC(int);
volatile int count=50; //volatile because this variable is transfered between multiple functions.

int main(void)
{
	sei();	//SREG |= (1<<8);
			//enable the global interrupt.
	
	//TCCR0 |= (1<<CS01); //Timer/Counter Control Register first 3 bits are re-scaler 010 -> /8
	//TIMSK |= (1<<TOIE0); //Timer/Counter Interrupt Mask Register the Overflow interrupt is enabled.
	//we did those previous two lines in the function so no need to it here
	
	DDRF |= (1<<PF1); // make PF1 as an output.
	PORTF |= (1<<PF1); //Enable the LEDs by make PF1 high.
		
	DDRA |= 0xFF; //make all LEDs as an output.
	PORTA |= 0x00; // close all LEDs.
		
	DDRB |= (1<<PB4); //make LED D10 as an output.
	PORTB |= (1<<PB4); //make LED D10 on.
	
    while(1)
    {
		PORTA |= 0xff;
		delayCTC(1);
		PORTA &=~ 0xff;
		delayCTC(1);
	}
}
void delay_sec(int sec){
	int count=3906*sec; //
	TCCR0 |= (1<<CS01); //Timer clock/8 = 1*10^6
	while(count){
		while(!(TIFR & (1<<TOV0) )); //!(in case of overflow this condition is true) //we want it to be wait until overflow is happened
		count--;
		TIFR |= (1<<TOV0); //this statement clears the flag.
	}
}
void delayOVE(int sec){
		TCCR0 |= (1<<CS01); //Timer/Counter Control Register first 3 bits are re-scaler 010 -> /8
		TIMSK |= (1<<TOIE0); //Timer/Counter Interrupt Mask Register the Overflow interrupt is enabled
		while(count);
		count=3906*sec;
	
}
void delayCTC(int sec){
	TCCR0 |= (1<<CS01)|(1<<CS00)|(1<<CS02);  //Timer/Counter Control Register first 3 bits are re-scaler 111 -> /1024
	TCCR0 |= (1<<WGM01); //Convert Timer to be in CTC mode
	TCCR0 |= (1<<COM00); //Toggle State.
	OCR0 = 255;			 //Output Compare Match.
	TIMSK |= (1<<OCIE0); //Timer/Counter Interrupt Mask Register Compare Match interrupt is enabled.
	
	while(count);
	count=50*sec;
	
}
ISR(TIMER0_OVF_vect){
	count--;
}
ISR(TIMER0_COMP_vect){
	count--;
}
/************************************************************************/
/* Timer Operation Modes:
-CTC:   Clear Timer On Compare Match.
		top value is OCR0 according to my set.

-Fast PWM
-PWM
-Normal                                                                   */
/************************************************************************/