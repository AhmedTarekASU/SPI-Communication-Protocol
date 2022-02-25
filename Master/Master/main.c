#define SS_HIGH PORTB|=(1<<4)
#define SS_LOW PORTB&=~(1<<4)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void SPI_MSTR_Config()
{
	SPCR |= (1<<SPE)|(1<<SPIE)|(1<<MSTR)|(1<<SPR0)|(1<<SPR1); //enable SPI, enable master mode, select sckl = f/128
	DDRB |= (1<<DDB4)|(1<<DDB5)|(1<<DDB7);          //Set MOSI, SS, SCK as output pins
	SS_HIGH;                                        //Set SS pin to HIGH
}


uint8_t SPI_Rotate(uint8_t x)
{
	SPDR = x;
	while(!(SPSR&(1<<SPIF)));
	uint8_t y = SPDR;
	return y;
}

int main(void)
{
	SPI_MSTR_Config();
	DDRA=0xFF;
	char* str = "SPI Initiated";
	char Trash;
	_delay_ms(5);
	while (1)
	{
		int i = 0;
		SS_LOW;
		_delay_us(2);
		while(i<13)
		{
			Trash = SPI_Rotate(str[i]);
			_delay_us(100);
			i++;
		}
		SS_HIGH;
		_delay_us(1000);
	}
	return 0;
}

