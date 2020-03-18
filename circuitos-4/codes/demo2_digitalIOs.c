/*
 * Demo2_Digital_IOs.c
 *
 * Created: 16/02/2020 18:48:53
 * Author : Pablo Gonzalez Robles
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB |= (1<<PB1);   //Set the Data Direction Register to output
    DDRB &= ~(1<<PB3);	//Set the Data Direction Register for the switch to input
	
	PORTB=
		(0 << PB1) | //Output LOW state (Sink)
		(1<<PB3);	//Enable the pull-up resistor for the switch
		
    while (1) 
    {
		if (PINB & (1<<PB3))
		{
			PORTB|=(1<<PB1);
			_delay_ms(100);	
		}
		
		else
		{
			PORTB &=~(1<<PB1);
			_delay_ms(100);
		}

    }
}

