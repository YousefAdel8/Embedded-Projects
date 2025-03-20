#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include "DIO.h"
#include "std_macros.h"
#include "keypad_driver.h"
#include <stdbool.h>


int main ()
{
	unsigned char x,flag=0;
	keypad_vInit();
	LCD_vInit();
	LCD_clearscreen();
	LCD_vSend_string("3+?=8");
	while (1)
	{
		
		if(flag==0)
		{
			x = keypad_u8check_press();
			if (x != NOTPRESSED)
			{
				if (x=='5')
				{
					LCD_clearscreen();
					LCD_vSend_string("Well Done");
					flag=1;
				}
				else
				{
					LCD_clearscreen();
					LCD_vSend_string("Wrong Answer");
					LCD_movecursor(2,1);
					LCD_vSend_string("Try Again");
					_delay_ms(500);
					LCD_clearscreen();
					LCD_vSend_string("3+?=8");
				}
			}
		}
		
	}
}




