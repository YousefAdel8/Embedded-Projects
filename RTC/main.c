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
#include <stdbool.h>


void display(unsigned char s1,unsigned char s2,unsigned char m1,unsigned char m2,unsigned char h1,unsigned char h2);
bool isDigit(unsigned char key);

volatile unsigned char counter=0,s=0,m=0,h=0;;

int main ()
{
	timer_CTC_init_interrupt();
	LCD_vInit();
	seven_seg_vinit('B');
	keypad_vInit();
	DIO_vsetPINDir('C',0,1);
	DIO_vsetPINDir('C',1,1);
	DIO_vsetPINDir('C',2,1);
	DIO_vsetPINDir('C',3,1);
	DIO_vsetPINDir('C',4,1);
	DIO_vsetPINDir('C',5,1);
	DIO_write('C',0,1);
	DIO_write('C',1,1);
	DIO_write('C',2,1);
	DIO_write('C',3,1);
	DIO_write('C',4,1);
	DIO_write('C',5,1);
	LCD_vSend_string("press 1 to");
	LCD_movecursor(2,1);
	LCD_vSend_string("set clock");
	unsigned char x,h_modified,m_modified,s_modified,digit1,digit2,flag=0,flagh=0,flagm=0,Flags=0;
	
	while (1)
	{
		
		x=keypad_u8check_press();
		if (x=='1')
		{
			
			flag=0;
			flagh=0;
			flagm=0;
			Flags=0;
			//hours
			while(flagh==0&&flag==0)
			{
				LCD_clearscreen();
				LCD_vSend_string("hours=--");
				LCD_movecursor(1,7);
				_delay_ms(500);
				do
				{
					digit1=keypad_u8check_press();
					display(0,0,0,0,0,0);
				} while (digit1==NOTPRESSED);
				LCD_vSend_char(digit1);
				_delay_ms(250);
				
				do
				{
					digit2=keypad_u8check_press();
					display(0,0,0,0,0,0);
				} while (digit2==NOTPRESSED);
				LCD_vSend_char(digit2);
				_delay_ms(250);
				
				h_modified=(digit1-48)*10+(digit2-48);
				flagh=1;
				
				if(h_modified==24)
				{
					h=0;
				}
				
				
				else if(h_modified>24)
				{
					LCD_clearscreen();
					LCD_vSend_string("Wrong Input");
					LCD_movecursor(2,1);
					LCD_vSend_string("Press 1 Again");
					_delay_ms(1000);
					
					
					flag=1;
				}
				else
				{
					h=h_modified;
				}
			}
			
			   
			   //Mins
			   
			   while(flag==0&&flagh==1&&flagm==0)
			   {
				   LCD_clearscreen();
				   LCD_vSend_string("minutes=--");
				   LCD_movecursor(1,9);
				   _delay_ms(500);
				   do
				   {
					   digit1=keypad_u8check_press();
					   display(0,0,0,0,h%10,h/10);
				   } while (digit1==NOTPRESSED);
				   LCD_vSend_char(digit1);
				   _delay_ms(250);
				   
				   do
				   {
					   digit2=keypad_u8check_press();
					   display(0,0,0,0,h%10,h/10);
					   
				   } while (digit2==NOTPRESSED);
				   LCD_vSend_char(digit2);
				   _delay_ms(250);
				   m_modified=(digit1-48)*10+(digit2-48);
				   flagm=1;
				   
				   
				   if (m_modified>60)
				   {
					   LCD_clearscreen();
					   LCD_vSend_string("Wrong Input");
					   LCD_movecursor(2,1);
					   LCD_vSend_string("Press 1 Again");
					   _delay_ms(1000);
					   flag=1;
					   
				   }
				   else
				   {
					   m=m_modified;
				   }
				   
				   
				   
			   }
			   
			   
			   //Seconds
			   
			   
			   while(flag==0&&flagm==1&&Flags==0)
			   {
				   LCD_clearscreen();
				   LCD_vSend_string("Seconds=--");
				   LCD_movecursor(1,9);
				   _delay_ms(500);
				   do
				   {
					   digit1=keypad_u8check_press();
					   display(0,0,m%10,m/10,h%10,h/10);
				   } while (digit1==NOTPRESSED);
				   LCD_vSend_char(digit1);
				   _delay_ms(250);
				   
				   do
				   {
					   digit2=keypad_u8check_press();
					   display(0,0,m%10,m/10,h%10,h/10);
				   } while (digit2==NOTPRESSED);
				   LCD_vSend_char(digit2);
				   _delay_ms(250);
				   s_modified=(digit1-48)*10+(digit2-48);
				   Flags=1;
				  
				   if (s_modified>59)
				   {
					   LCD_clearscreen();
					   LCD_vSend_string("Wrong Input");
					   LCD_movecursor(2,1);
					   LCD_vSend_string("Press 1 Again");
					   _delay_ms(1000);
					   flag=1;
				   }
				   else
				   {
					   s=s_modified;
				   }
				   
				   
			   }
			   LCD_clearscreen();
			   LCD_vSend_string("press 1 to");
			   LCD_movecursor(2,1);
			   LCD_vSend_string("set clock");
		}
				
			
		
		display(s%10,s/10,m%10,m/10,h%10,h/10);
		
		
		
	}
}
ISR(TIMER0_COMP_vect)
{
	counter++;
	if (counter==100)
	{
		s++;
		counter=0;
	}
	
	
	if (s==60)
	{
		s=0;
		m++;
	}
	if (m==60)
	{
		m=0;
		h++;
	}
	if (h==24)
	{
		h=0;
	}
	
}
void display(unsigned char s1,unsigned char s2,unsigned char m1,unsigned char m2,unsigned char h1,unsigned char h2)
{
	DIO_write('C',0,0);
	DIO_write('C',1,1);
	DIO_write('C',2,1);
	DIO_write('C',3,1);
	DIO_write('C',4,1);
	DIO_write('C',5,1);
	seven_seg_write('B',s1);
	_delay_ms(3);
	
	DIO_write('C',0,1);
	DIO_write('C',1,0);
	DIO_write('C',2,1);
	DIO_write('C',3,1);
	DIO_write('C',4,1);
	DIO_write('C',5,1);
	seven_seg_write('B',s2);
	_delay_ms(3);
	
	DIO_write('C',0,1);
	DIO_write('C',1,1);
	DIO_write('C',2,0);
	DIO_write('C',3,1);
	DIO_write('C',4,1);
	DIO_write('C',5,1);
	seven_seg_write('B',m1);
	_delay_ms(3);
	
	DIO_write('C',0,1);
	DIO_write('C',1,1);
	DIO_write('C',2,1);
	DIO_write('C',3,0);
	DIO_write('C',4,1);
	DIO_write('C',5,1);
	seven_seg_write('B',m2);
	_delay_ms(3);
	
	DIO_write('C',0,1);
	DIO_write('C',1,1);
	DIO_write('C',2,1);
	DIO_write('C',3,1);
	DIO_write('C',4,0);
	DIO_write('C',5,1);
	seven_seg_write('B',h1);
	_delay_ms(3);
	
	DIO_write('C',0,1);
	DIO_write('C',1,1);
	DIO_write('C',2,1);
	DIO_write('C',3,1);
	DIO_write('C',4,1);
	DIO_write('C',5,0);
	seven_seg_write('B',h2);
	_delay_ms(3);
}
bool isDigit(unsigned char key) 
{
	return (key >= '0' && key <= '9');
}



