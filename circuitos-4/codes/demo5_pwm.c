/*
 * Demo5_PWM.c
 *
 * Created: 16/03/2020 20:18:19
 * Author : Pablo Gonzalez Robles
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// For 8MHz clock: 61.2kHz period (16.25ms) of which half is on and half is off

int main(void)
{
	
	DDRB = (1<<DDB0) ; // make OC0A (PB0) & OC1A (PB1) PWM output pin	
	
	TCCR0A = 
			(1<<COM0A1) | (1<<COM0B0) |
			(1<<WGM00);  // 001
	// PWM, Phase Correct
	TCCR0B = (1<<CS02) | (0<<CS01) | (0<<CS00);   // clkI/O/256(from prescaler)
	// not used // TIMSK1=0B00000010;    //enable output compare interrupt for OCR1A
    float duty = 20; //in %
	float value = duty/100.0*255.0;
	OCR0A = (int)value;          // set duty cycle (0.5*256)
	
    while (1) 
    {
    }
}

