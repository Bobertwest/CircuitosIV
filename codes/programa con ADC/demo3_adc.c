/*
 * Demo3_Analog_Pot.c
 *  Analog Input
 * Created: 02/03/2020 19:07:50
 * Author : Pablo Gonzalez Robles
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

unsigned int analogResult = 0;
unsigned int binary_weighted_voltage_low;
unsigned int binary_weighted_voltage_high;


/*
ADC Pre-scaler needs to be set so that the ADC input frequency is between 50 - 200kHz.
Clock   Available pre-scaler values
 1 MHz   8 (125kHz), 16 (62.5kHz)
 
 PB4 
 DDRB &= ~(1<<PB4);
 (0 << MUX3)  |	(0 << MUX2)  |	(1 << MUX1)  |	(0 << MUX0);
PB3
DDRB &= ~(1<<PB3);
(0 << MUX3)  |	(0 << MUX2)  |	(1 << MUX1)  |	(1 << MUX0);

*/
int main(void)
{
	DDRB |= (1<<PB1)|(1<<PB0)|(1<<PB4);   //Set the Data Direction Register to output
	DDRB &= ~(1<<PB2);	//Set the Data Direction Register for the POT to input
		
	ADMUX =
		(0 << REFS1) |  (0 << REFS0) |   // Sets ref. voltage to VCC
		(0 << ADLAR) |				   // 0: right adjust, 1: left adjust
		(0 << MUX3)  |	(0 << MUX2)  |	(0 << MUX1)  |	(1 << MUX0);   //  MUX bits PB4; 0010, PB3
	
	
	ADCSRA =
		(1 << ADEN)  |     // Enable ADC
		(0 << ADSC)  |     // DISABLED Start Conversion (at setup)
		(0 << ADATE)  |     // DISABLED Auto trigger
		(0 << ADIF)  |     //
		(0 << ADIE)  |     // DISABLED ADC interrupt flag
		(0 << ADPS2) | (1 << ADPS1) |  (1 << ADPS0);  // set prescaler to 8
	
	ADCSRB =
		(0<<ADTS2)|		//Free running mode bit 2
		(0<<ADTS1)|		//Free running mode bit 1
		(0<<ADTS0);		//Free running mode bit 0
	
	//DIDR0 |= (1<<ADC2D); // digital input buffer disabled on ADC3 pin
	
    while (1) 
    {
		ADCSRA |= (1 << ADSC);         // start ADC measurement
		while (ADCSRA & (1 << ADSC) ); // wait till conversion complete
		//result = (ADCH<<8)|ADCL; 8 bits from ADCL + 2 bits from ADCH
		binary_weighted_voltage_low = ADCL; 
		binary_weighted_voltage_high = ((unsigned int)(ADCH << 8)); 
		analogResult = binary_weighted_voltage_low | binary_weighted_voltage_high;
		//VCC = 4.8V - 1 unit = 4.6875 mV
		if(analogResult<=426) //value 0 - 426 (0-2.0V)
		{
			PORTB|=(1<<PB0);
			PORTB&=~(1<<PB1);
			PORTB|=(1<<PB4);
			_delay_ms(100);
		}
		else if(analogResult>=448 && analogResult <=853) //value 448 - 853 (2.1 - 4.0 V)
		{
			PORTB|=(1<<PB0);
			PORTB|=(1<<PB1);
			PORTB&=~(1<<PB4);
			_delay_ms(100);

		}
		else if(analogResult>=874) //valor 874 - 1023(4.1 - 4.8 V)
		{
			PORTB&=~(1<<PB0);
			PORTB|=(1<<PB1);
			PORTB|=(1<<PB4);
			_delay_ms(100);
		}
		else
		{
			PORTB &=~((1<<PB1)|(1<<PB0)|(1<<PB4));
		}
    }
}




