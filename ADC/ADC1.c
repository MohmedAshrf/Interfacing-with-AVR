#include <avr/io.h>

int main(void)
{
	ADMUX |= (1<<REFS0); // AREF, Internal V ref turned off  
	ADMUX |= (1<<REFS1); // AREF, Internal V ref turned off
	ADMUX |= (1<<ADLAR); // 1 :- MSB at ADCH
	// default selecting AD0
	ADCSRA |= (1<<ADEN); // Enable ADC
	ADCSRA |= (1<<ADSC); // Start convention (Just one time and then it goes low)
	ADCSRA |= (1<<ADFR); // continue conventionalizing (set ADSC to be high again )
	
	DDRF |= (1<<PF1); // direction
	PORTF |= (1<<PF1); //enable
	
	DDRA |= 0xFF;
	
	 
    while(1)
    {
		PORTA = ADCH ;
		
		
    }
}
/***********************
signaL MUST BE IN THe range of 5 to 0 volt.
ADC:
8 bit or less or more
more bits is better (not optional)
less scope is better
fast clock is better
better for low quantization

AREF : hardware pin to select the max scale of voltage
ADLAR : 0 :- MSB at ADCL
		1 :- MSB at ADCH
 
we can make interrupt on ADC by using this register ADCSRA -> ADIF
we can enable interrupt on ADC by using this register ADCSRA -> ADIE


**************************/