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
	LED_vInit('D',0);
	LED_vInit('D',1);
	LED_vInit('D',2);
	LED_vInit('D',3);
	LED_vInit('D',4);
    LED_vInit('D',5);
    LED_vInit('D',6);
	LED_vInit('D',7);
	button_vInit('C',0);
	DIO_write('C',0,1);
	
	
    unsigned char i=0,flag=0;
	while(1)
	{
		if(button_u8read('C',0)==0)
		{
			
			if (i==8)
			{
				flag=1;
			}
			if (flag==0)
			{
				LED_vToggle('D',i);
				i++;
			}
			
				
			
			
			if (flag==1)
			{
				i--;
				LED_vToggle('D',i);
				if (i==0)
				{
					flag=0;
				}
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
