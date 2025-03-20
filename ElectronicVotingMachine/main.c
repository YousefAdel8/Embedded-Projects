#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include "DIO.h"
#include "std_macros.h"
#include "button.h"

int main ()
{
	LCD_vInit();
	LCD_vSend_cmd(0x0C);

	button_vInit('D',0); //A
	DIO_vconnectpullup('D',0,1); 
	button_vInit('D',1); //B
	DIO_vconnectpullup('D',1,1);
	button_vInit('D',2); //C
	DIO_vconnectpullup('D',2,1); 
	button_vInit('D',3); //D
	DIO_vconnectpullup('D',3,1);
	button_vInit('D',4); //RESET
	DIO_vconnectpullup('D',4,1);
	
	unsigned char a=0,b=0,c=0,d=0;
	unsigned char digita1,digita2,digitb1,digitb2,digitc1,digitc2,digitd1,digitd2;
	
	
	
	LCD_vSend_char('A');
	_delay_ms(100);
	LCD_vSend_char(':');
	_delay_ms(100);
	LCD_movecursor(1,8);
	LCD_vSend_char('B');
	_delay_ms(100);
	LCD_vSend_char(':');
	_delay_ms(100);
	LCD_movecursor(2,1);
	LCD_vSend_char('C');
	_delay_ms(100);
	LCD_vSend_char(':');
	_delay_ms(100);
	LCD_movecursor(2,8);
	LCD_vSend_char('D');
	_delay_ms(100);
	LCD_vSend_char(':'); 
	_delay_ms(100);
	while(1)
	{
		if (button_u8read('D',0)==0)
		{
			_delay_ms(30);
			if (button_u8read('D',0)==0)
			{
				a++;
				
				while(button_u8read('D',0)==0);
				_delay_ms(100);
			}
			
		}
		if (button_u8read('D',1)==0)
		{
			_delay_ms(30);
			if (button_u8read('D',1)==0)
			{
				b++;
				
				while(button_u8read('D',1)==0);
				_delay_ms(100);
			}
			
		}
		if (button_u8read('D',2)==0)
		{
			_delay_ms(30);
			if (button_u8read('D',2)==0)
			{
				c++;
				
				while(button_u8read('D',2)==0);
				_delay_ms(100);
			}
			
		}
		if (button_u8read('D',3)==0)
		{
			_delay_ms(30);
			if (button_u8read('D',3)==0)
			{
				d++;
				
				while(button_u8read('D',3)==0);
				_delay_ms(100);
			}
			
		}
		if (button_u8read('D',4)==0)
		{
			_delay_ms(30);
			if (button_u8read('D',4)==0)
			{
				a=0;
				b=0;
				c=0;
				d=0;
				
				while(button_u8read('D',4)==0);
				_delay_ms(30);
			}
			
		}
		
		if (a==100)
		{
			a=0;
		}
		if (b==100)
		{
			b=0;
		}
		if (c==100)
		{
			c=0;
		}
		if (d==100)
		{
			d=0;
		}
		
		
		digita1=a/10;
		digita2=a%10;
		digitb1=b/10;
		digitb2=b%10;
		digitc1=c/10;
		digitc2=c%10;
		digitd1=d/10;
		digitd2=d%10;
		if (a<=9)
		{
			LCD_movecursor(1,3);
			LCD_vSend_char(48+digita2);
			LCD_vSend_char(' ');
		} 
		else
		{
			LCD_movecursor(1,3);
			LCD_vSend_char(48+digita1);
			LCD_vSend_char(48+digita2);
		}
		if (b<=9)
		{
			LCD_movecursor(1,10);
			LCD_vSend_char(48+digitb2);
			LCD_vSend_char(' ');
		}
		else
		{
			LCD_movecursor(1,10);
			LCD_vSend_char(48+digitb1);
			LCD_vSend_char(48+digitb2);
		}
		if (c<=9)
		{
			LCD_movecursor(2,3);
			LCD_vSend_char(48+digitc2);
			LCD_vSend_char(' ');
		}
		else
		{
			LCD_movecursor(2,3);
			LCD_vSend_char(48+digitc1);
			LCD_vSend_char(48+digitc2);
		}
		if (d<=9)
		{
			LCD_movecursor(2,10);
			LCD_vSend_char(48+digitd2);
			LCD_vSend_char(' ');
		}
		else
		{
			LCD_movecursor(2,10);
			LCD_vSend_char(48+digitd1);
			LCD_vSend_char(48+digitd2);
		}
		
		
		
		
		
		
		
	 
	 
	 
	 
	 
	 	
		
		
	}
	
	
	
	
		
}
	
