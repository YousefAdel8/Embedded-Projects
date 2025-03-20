
#include <avr/io.h>
#include "std_macros.h"
void ADC_vinit(void)
{
// 	SET_BIT(ADMUX,REFS0); //configure VREF
// 	SET_BIT(ADMUX,REFS1);
	SET_BIT(ADCSRA,ADEN); // enable ADC
	/* adjust ADC clock*/
	SET_BIT(ADCSRA,ADPS2);
	SET_BIT(ADCSRA,ADPS1);
}
 unsigned short ADC_u16Read(void)
{
	 unsigned short read_val;
	
	SET_BIT(ADCSRA,ADSC);
	while(IS_BIT_CLR(ADCSRA,ADIF));//stay in your position till ADIF become 1
	SET_BIT(ADCSRA,ADIF); // clear ADIF
	read_val=(ADCL);
	read_val|=(ADCH<<8);
	return read_val ;
}
void PWM_init()
{
	
	DDRB |= (1 << PB3); //OC0 as Output
	TCCR0 |= (1 << WGM00) | (1 << WGM01); 
	TCCR0 |= (1 << COM01); 
	TCCR0 |= (1 << CS00); 
}

void PWM_set_duty_cycle_percent(uint8_t percent)
{
	if (percent > 100) percent = 100;
	uint8_t value = (percent * 255) / 100;
	OCR0 = value;
}
void PWM_init_rgb()
{
	
	DDRB |= (1 << PB3); // Red
	DDRD |= (1 << PD5) | (1 << PD6); // Blue and Green

	
	TCCR0 |= (1 << WGM00) | (1 << WGM01); //  Fast PWM
	TCCR0 |= (1 << COM01); 
	TCCR0 |= (1 << CS00); // (No Prescaler)

	
	TCCR1A |= (1 << WGM10) | (1 << WGM11); // Fast PWM 10-bit
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1); 
	TCCR1B |= (1 << CS10); //(No Prescaler)
}

void PWM_set_rgb(uint8_t red_percent, uint8_t green_percent, uint8_t blue_percent)
{
	
	if (red_percent > 100) red_percent = 100;
	if (green_percent > 100) green_percent = 100;
	if (blue_percent > 100) blue_percent = 100;

	
	uint8_t red_value = (red_percent * 255) / 100;
	uint8_t green_value = (green_percent * 255) / 100;
	uint8_t blue_value = (blue_percent * 255) / 100;

	
	OCR0 = red_value;            
	OCR1A = green_value << 2;   
	OCR1B = blue_value << 2;    
}