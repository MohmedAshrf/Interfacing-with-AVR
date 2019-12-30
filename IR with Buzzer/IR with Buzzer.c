

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	
	PORTE |= (1<<PE5); //pull up Resistor.
	
	DDRE |= (1<<PE7); //Out buzzer
		
    while(1)
    {
		if(!(PINE & 0x20) ){
        PORTE |= (1<<PE7); //buzzer
		_delay_ms(10);
		PORTE &= ~(1<<PE7); //buzzer
		_delay_ms(10);
		}
		
    }
}