#define SS_HIGH PORTB|=(1<<4)
#define SS_LOW PORTB&=~(1<<4)

#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <string.h>
#include "lcdConfig.c"


void SPI_SLAV_Config()
{
	SPCR |= (1<<SPE)|(1<<SPIE)|(1<<SPR0)|(1<<SPR1);            //enable SPI, enable slave mode, Select SCKL = f/128
	DDRB |= (1<<DDB6);                               //Set MISO as output
}


uint8_t flag = 0;
char* str;
int main(void)
{
	str = malloc(13*sizeof(char));
	lcd_init();
	SPI_SLAV_Config();
	sei();
	while (1)
	{
		while(flag<13);
		lcd_gotoxy(1,1);
		lcd_print(str);
		flag = 0;
	}
}

ISR(SPI_STC_vect)
{
	if(flag<13)
	{
		str[flag]=SPDR;
		flag++;
	}
}

