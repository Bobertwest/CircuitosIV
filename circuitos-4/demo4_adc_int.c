/*
 * Demo3_Analog_Pot.c
 *  CW turn off pot
 * Created: 17/02/2020 10:27:30
 * Author : Pablo Gonzalez Robles
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned int analogResult = 0;

int main(void)
{
	DDRB |= (1<<PB1)|(1<<PB0);   //Set the Data Direction Register to output
	DDRB &= ~(1<<PB4);	//Set the Data Direction Register for the POT to input
		
	ADMUX =
		(0 << REFS1) |  (0 << REFS0) |   // Sets ref. voltage to VCC
		(0 << ADLAR) |				     // 0: right adjust, 1: left adjust
		(0 << MUX3)  |				     //  MUX bit 3
		(0 << MUX2)  |				     //  MUX bit 2
		(1 << MUX1)  |				     //  MUX bit 1
		(0 << MUX0);                     //  MUX bit 0
	
	
	ADCSRA =
		(1 << ADEN)  |     // Enable ADC
		(1 << ADSC)  |     // Start Conversion
		(1 << ADATE)  |     // Enable Auto trigger
		(0 << ADIF)  |     //
		(1 << ADIE)  |     //ADC interrupt flag
		(0 << ADPS2) | (1 << ADPS1) |  (1 << ADPS0);  // set prescaler to 8
	
	ADCSRB =
		(0<<ADTS2)|		//Free running mode bit 2
		(0<<ADTS1)|		//Free running mode bit 1
		(0<<ADTS0);		//Free running mode bit 0
	
	sei(); //enable interrupts
	
    while (1) 
    {
		
		//VCC = 4.8V - 1 unit = 4.6875 mV
		if(analogResult<=200) //value 0-100 (0-0.94V)
		{
			PORTB|=(1<<PB0);
			PORTB&=~(1<<PB1);
			_delay_ms(100);
		}
		else if(analogResult>=900) //value 900-1023 (4.22 - 4.8 V)
		{
			PORTB&=~(1<<PB0);
			PORTB|=(1<<PB1);
			_delay_ms(100);
		}
		else
		{
			PORTB &=~((1<<PB1)|(1<<PB0));
		}
    }
}


ISR(ADC_vect) //interrupt function
{
	//The ADC generates a 10-bit result 
	//which can be found in the ADC Result Registers, ADCH and ADCL
	unsigned int binary_weighted_voltage_low = ADCL; //Read 8 low bits first (important)
	unsigned int binary_weighted_voltage_high = ((unsigned int)(ADCH << 8)); //Read 2 high bits, then multiply by 256
	analogResult = binary_weighted_voltage_low | binary_weighted_voltage_high;
}
