#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include "DIO.h"
#include "std_macros.h"


int main ()
{
	LCD_vInit();
	
	 LCD_vSend_char('Y'); 
	 _delay_ms(500);
	 LCD_vSend_char('o'); 
	 _delay_ms(500);
	 LCD_vSend_char('u'); 
	 _delay_ms(500);
	 LCD_vSend_char('s'); 
	 _delay_ms(500);
	 LCD_vSend_char('e'); 
	 _delay_ms(500);
	 LCD_vSend_char('f'); 
	 _delay_ms(500);
	 LCD_vSend_char(32); 
	 _delay_ms(500);
	 LCD_vSend_char('A'); 
	 _delay_ms(500);
	 LCD_vSend_char('d');
	 _delay_ms(500);
	 LCD_vSend_char('e');
	  _delay_ms(500);
	 LCD_vSend_char('l'); 
	 _delay_ms(500);
	
	
	
	_delay_ms(500);
	LCD_movecursor(2,1);
	LCD_vSend_cmd(64);
	unsigned char name0x12[] = { 0B00000, 0B00000, 0B01000, 0B01000, 0B01111, 0B00000, 0B00000, 0B00000 };
	unsigned char name0x13[] = { 0B01000, 0B00000, 0B11101, 0B10101, 0B11111, 0B00000, 0B00000, 0B00000 };
	unsigned char name0x14[] = { 0B00000, 0B00000, 0B01010, 0B01010, 0B11110, 0B00000, 0B00000, 0B00000 };
	unsigned char name0x15[] = { 0B00000, 0B00000, 0B11101, 0B10101, 0B11111, 0B00100, 0B01011, 0B11000 };
	unsigned char name0x7[] = { 0B00000, 0B00000, 0B00001, 0B00001, 0B00111, 0B00000, 0B00000, 0B00000 };
	unsigned char name0x6[] = { 0B00001, 0B00001, 0B00001, 0B01001, 0B01001, 0B01111, 0B00000, 0B00000 };
	unsigned char name0x8[] = { 0B00100, 0B00100, 0B00100, 0B00100, 0B00111, 0B00000, 0B00000, 0B00000 };
	unsigned char name0x9[] = { 0B00000, 0B01111, 0B01000, 0B01000, 0B11111, 0B00000, 0B00000, 0B00000 };

		
		
		
	for (unsigned char i=0;i<=7;i++)
	{
		LCD_vSend_char(name0x15[i]);
		
	}
	for (unsigned char i=0;i<=7;i++)
	{
		LCD_vSend_char(name0x14[i]);
		
	}
	for (unsigned char i=0;i<=7;i++)
	{
		LCD_vSend_char(name0x13[i]);
		
	}
	for (unsigned char i=0;i<=7;i++)
	{
		LCD_vSend_char(name0x12[i]);
		
	}
	for (unsigned char i=0;i<=7;i++)
	{
		LCD_vSend_char(name0x9[i]);
		
	}
	for (unsigned char i=0;i<=7;i++)
	{
		LCD_vSend_char(name0x8[i]);
		
	}
	for (unsigned char i=0;i<=7;i++)
	{
		LCD_vSend_char(name0x7[i]);
		
	}
	for (unsigned char i=0;i<=7;i++)
	{
		LCD_vSend_char(name0x6[i]);
		
	}
	
	LCD_movecursor(2,16);
	LCD_vSend_char(0);
	_delay_ms(500);
	LCD_movecursor(2,15);
	LCD_vSend_char(1);
	_delay_ms(500);
	LCD_movecursor(2,14);
	LCD_vSend_char(2);
	_delay_ms(500);
	LCD_movecursor(2,13);
	LCD_vSend_char(3);
	_delay_ms(500);
	LCD_movecursor(2,11);
	LCD_vSend_char(4);
	_delay_ms(500);
	LCD_movecursor(2,10);
	LCD_vSend_char(5);
	_delay_ms(500);
	LCD_movecursor(2,9);
	LCD_vSend_char(6);
	_delay_ms(500);
	LCD_movecursor(2,8);
	LCD_vSend_char(7);
	_delay_ms(500);
	LCD_movecursor(2,7);
	
		
}
	
