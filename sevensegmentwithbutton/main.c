#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "seven segment.h"
#include "DIO.h"
#include "std_macros.h"
#include "button.h"
int main ()
{
	
	button_vInit('C',0);
	DIO_write('C',0,1);
	seven_seg_vinit('D');
	unsigned char i=0;
    
	while(1)
	{
		if(button_u8read('C',0)==0)
		{
			seven_seg_write('D',i);
			i++;
			if (i==10)
			{
				i=0;
			}
			_delay_ms(100);
			while(button_u8read('C',0)==0)
			{
				_delay_ms(100);
			}
		}
		
		
		
		
	}

	return 0;
}
