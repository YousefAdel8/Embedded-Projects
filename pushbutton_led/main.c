#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "LED.h"
#include "std_macros.h"
#include "DIO.h"
#include "button.h"
int main ()
{
	LED_vInit('D',6);
	button_vInit('D',5);
    DIO_write('D',5,1);
	
	

	while(1)
	{
		if (button_u8read('D',5)==0)
		{
			LED_vToggle('D',6);
			_delay_ms(100);
			while(button_u8read('D',5)==0)
			{
				_delay_ms(100);
			}
		}
		
		
		
		
	}

	return 0;
}
