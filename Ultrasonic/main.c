#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "seven segment.h"
#include "DIO.h"
#include "std_macros.h"
#include "keypad_driver.h"
#include "timer.h"
#include "LCD.h"



int main ()
{
	LCD_vInit();
	unsigned short a,b,high,distance;
	DIO_vsetPINDir('D',7,1);
	
	
	while (1)
	{
		TCCR1A=0;
		TIFR=(1<<ICF1); //clear ICF
		DIO_write('D',7,1);
		_delay_us(50);
		DIO_write('D',7,0);
		TCCR1B=0xC1;
		while ((TIFR&(1<<ICF1))==0);
		a=ICR1;
		TIFR=(1<<ICF1); //clear ICF
		TCCR1B=0x81;
		while ((TIFR&(1<<ICF1))==0);
		b=ICR1;
		TIFR=(1<<ICF1);
		TCNT1=0;
		TCCR1B=0;
		high=b-a;
		distance=((high*34600)/(F_CPU*2));
		
			
			if (distance>=80)
			{
				LCD_clearscreen();
				LCD_vSend_string("No Object");
				_delay_ms(500);
			}
			else
			{
				LCD_clearscreen();
				LCD_vSend_string("Distance=");
				LCD_vSend_char((distance/10)+48);
				LCD_vSend_char((distance%10)+48);
				_delay_ms(500);
			}
			_delay_ms(500);
			
		
		
		
	
	}
	
}

	
	


