/*
 * Primer Codigo.c
 *
 * Created: 03/03/2020 8:17:55 p. m.
 * Author : rober
 */ 

#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>

int main(void)
{
    /* Replace with your application code */
	DDRB = 0b00000011;
    while (1) 
    {
		PORTB = 0b00000011;
		_delay_ms(2000);
		PORTB = 0b00000000;
		_delay_ms(2000);
    }
}



