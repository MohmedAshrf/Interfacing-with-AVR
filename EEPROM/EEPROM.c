#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
unsigned char EEPROM_read(unsigned int uiAddress);
 void EEPROM_write(unsigned int uiAddress, unsigned char ucData);
int main(void)
{
	DDRF |= (1<<PF1);
	PORTF |= (1<<PF1);
	DDRA |= 0XFF;

char Data;
	Data= EEPROM_read(0x0000);
	PORTA = Data;
    while(1)
    {
		Data++;
	PORTA = Data;
	_delay_ms(1000);
		EEPROM_write(0x0000,Data);
		
    }
}
unsigned char EEPROM_read(unsigned int uiAddress)
{
	
	while(EECR & (1<<EEWE));//EEWE: Write Enable
	//EECR : Control Register
	EEAR = uiAddress;
	
	EECR |= (1<<EERE); //EERE : Read Enable
	
	return EEDR; //EEDR : Data Register
}
void
 EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{

while(EECR & (1<<EEWE));
EEAR = uiAddress;
EEDR = ucData;
/* 
Write logical one to EEMWE */
EECR |= (1<<EEMWE);
/* Start eeprom write by setting EEWE */
EECR |= (1<<EEWE);
}