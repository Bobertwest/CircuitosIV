/*
 * Codigo con boton.c
 *
 * Created: 03/10/2020 7:36:21 p. m.
 * Author : rober
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB = 0b00000110;

    /* Replace with your application code */
    while (1)
    {
		if (PINB & (1<<PB3));
		{
			PORTB = 0b0000110;
		}
		
		else{
			PORTB = 0b0000000;	
		}
		
    }
}