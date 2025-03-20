#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "seven segment.h"
#include "DIO.h"
#include "std_macros.h"
#include "button.h"
#include "timer.h"
volatile unsigned char counter=0;

int main ()
{
	timer_CTC_init_interrupt();
	seven_seg_vinit('D');
	DIO_vsetPINDir('A',0,1);
	DIO_vsetPINDir('A',1,1);
	DIO_write('A',0,1);
	DIO_write('A',1,1);
	unsigned char number=0,digit1,digit2;
	while(1)
	{
		digit2=number/10;
		digit1=number%10;
		DIO_write('A',0,0);
		DIO_write('A',1,1);
		seven_seg_write('D',digit1);
		_delay_ms(3);
		DIO_write('A',0,1);
		DIO_write('A',1,0);
		seven_seg_write('D',digit2);
		_delay_ms(3);
		
					if (counter==100)
						{
							counter=0;
							number++;
						}
						if (number==20)
						{
							number=0;
						}
																								// 		}
			
		}

		return 0;
	}
	
	ISR(TIMER0_COMP_vect)
		{
					counter++;
	}
	
	
