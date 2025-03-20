#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "seven segment.h"
#include "DIO.h"
#include "button.h"

int main ()
{
	button_vInit('C', 0);
	DIO_write('C', 0, 1);
	seven_seg_vinit('D');
	DIO_vsetPINDir('A', 0, 1);
	DIO_vsetPINDir('A', 1, 1);
	DIO_write('A', 0, 1);
	DIO_write('A', 1, 1);
	unsigned char number = 0, digit1, digit2;
	
	while (1)
	{
		digit2 = number / 10;
		digit1 = number % 10;
		
		DIO_write('A', 0, 0);
		DIO_write('A', 1, 1);
		seven_seg_write('D', digit1);
		_delay_ms(3);
		DIO_write('A', 0, 1);
		DIO_write('A', 1, 0);
		seven_seg_write('D', digit2);
		_delay_ms(3);

		
		if (button_u8read('C', 0) == 0)
		{
			DIO_write('A', 0, 0);
			DIO_write('A', 1, 1);
			seven_seg_write('D', digit1);
			_delay_ms(3);
			DIO_write('A', 0, 1);
			DIO_write('A', 1, 0);
			seven_seg_write('D', digit2);
			_delay_ms(3);
			DIO_write('A', 0, 0);
			DIO_write('A', 1, 1);
			seven_seg_write('D', digit1);
			_delay_ms(3);
			DIO_write('A', 0, 1);
			DIO_write('A', 1, 0);
			seven_seg_write('D', digit2);
			_delay_ms(3);
			if (button_u8read('C', 0) == 0)
			{
				
				number++;
				if (number == 100)
				{
					number = 0;
				}

				
				while (button_u8read('C', 0) == 0)
				{
					DIO_write('A', 0, 0);
		            DIO_write('A', 1, 1);
		            seven_seg_write('D', digit1);
		            _delay_ms(3);
		            DIO_write('A', 0, 1);
		            DIO_write('A', 1, 0);
		            seven_seg_write('D', digit2);
		            _delay_ms(3);
				}
				
			}
		}
	}

	return 0;
}
