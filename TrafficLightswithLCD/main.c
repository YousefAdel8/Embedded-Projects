#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include "DIO.h"
#include "std_macros.h"
#include "LED.h"
#include "timer.h"

volatile unsigned int counter=0;


int main ()
{
	LED_vInit('D',0); //Green
	LED_vInit('D',1); //Yellow
	LED_vInit('D',2); //Red
	timer_CTC_init_interrupt();
	LCD_vInit();    
	LCD_vSend_cmd(0x0C); //clear cursor
	unsigned char green=10,yellow=5,red=7;
	
	while(1)
	{
		green=10;
		yellow=5;
		red=7;
		
		LCD_clearscreen();
		LCD_vSend_string(" Remaining Time");
		LCD_movecursor(2,7);
		LCD_vSend_string("10");
		LED_vTurnOn('D',0);
		_delay_ms(1000);
		
		while(green>0)
		{
			
			if (counter>=100)
			{
				counter=0;
				green--;
				LCD_movecursor(2,7);
				LCD_vSend_char(32);
				if (green==10)
				{
					LCD_movecursor(2,7);
					LCD_vSend_char(48+green);
					LCD_vSend_char(48+green%10);
					
				} 
				else
				{
					LCD_movecursor(2,7);
					LCD_vSend_char(48+green);
					LCD_vSend_char(32);
				}
				
				
				
			}
		}
		_delay_ms(500);
		LED_vTurnOn('D',1);
		LED_vTurnOff('D',0);
		LCD_clearscreen();
		LCD_vSend_string(" Remaining Time");
		LCD_movecursor(2,7);
		LCD_vSend_string("5");
		LCD_vSend_char(32);
		_delay_ms(1000);
		while(yellow>0)
		{
			
			if (counter>=100)
			{
				counter=0;
				yellow--;
				LCD_movecursor(2,7);
				LCD_vSend_char(32);
				LCD_movecursor(2,7);
				LCD_vSend_char(48+yellow);
				LCD_vSend_char(32);
				
			}
			
			
		}
		_delay_ms(500);
		LED_vTurnOn('D',2);
		LED_vTurnOff('D',1);
		LCD_clearscreen();
		LCD_vSend_string(" Remaining Time");
		LCD_movecursor(2,7);
		LCD_vSend_string("7");
		_delay_ms(1000);
		while(red>0)
		{
			
			
			if (counter>=100)
			{
				counter=0;
				red--;
				LCD_movecursor(2,7);
				LCD_vSend_char(32);
				LCD_movecursor(2,7);
				LCD_vSend_char(48+red);
				LCD_vSend_char(32);
				
				
			}
			
			
		}
		_delay_ms(500);
		LED_vTurnOff('D',2);
		
	}
	
	
		
	
	
		
}
	
ISR(TIMER0_COMP_vect)
{
	counter++;
}