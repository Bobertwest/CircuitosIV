*
 * Demo1_Blink_PB0.c
 *
 * Created: 15/02/2020 14:16:12
 * Author : Pablo Gonzalez Robles
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB = 0b00000011;          // Set PB0 to be output
	
    while (1) 
    {
		//Hard blinking
		/*
		PORTB = 0b00000011;    // Set PB0 HIGH
		_delay_ms(1000);
		PORTB = 0b00000000;    // set PB0 LOW
		_delay_ms(1000);
		*/
		
		//Bitwise blinking
		
		PORTB |=(1<< PB0);
		_delay_ms(250);
		PORTB &= ~(1 << PB0);
		_delay_ms(250);
		
		
		//Toggle led
		/*
		PORTB ^= (1 << PB0);
		_delay_ms(100);
		*/
    }
}

