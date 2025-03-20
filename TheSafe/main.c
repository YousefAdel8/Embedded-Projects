#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include "EEPROM.h"
#include "keypad_driver.h"
#include <stdbool.h>


bool isDigit(char key);

int main ()
{
	unsigned char pass[4],x,address=0x21,flag=0,Tries=3;
	
	keypad_vInit();
	LCD_vInit();
	LCD_clearscreen();
	
	while (1)
	{
		   if (EEPROM_read(0x20) == 0xff)
		   {
			   LCD_vSend_string("Enter Pass:");
			   _delay_ms(200);
			   LCD_movecursor(2, 5);

			   for (unsigned char i = 0; i < 4;) 
			   {
				   x = keypad_u8check_press();
				   if (x != NOTPRESSED)
				   {
					   if (isDigit(x))
					   {
						   LCD_vSend_char(x);
						   EEPROM_write(address + i, x); 
						   _delay_ms(500);
						   --i;
						   LCD_movecursor(2,i+6);
						   LCD_vSend_char('*');
						   i++;
						   _delay_ms(250);
						   i++;
					   }
					   else if (x == '-')
					   {
						   if (i > 0) 
						   {
							   i--;
							   LCD_movecursor(2, 5 + i);
							   LCD_vSend_char(' ');
							   LCD_movecursor(2, 5 + i);
							   _delay_ms(250);
						   }
					   }
				   }
			   }

			   EEPROM_write(0x20, 0x00); 
			   
			 
		   }
		   
		   
		   
		   
		   
			else if (flag==0)
			
			{
				LCD_clearscreen();

				LCD_vSend_string("Pass check:");
				LCD_movecursor(2,5);
				 for (unsigned char i = 0; i < 4;)
				 {
					 x = keypad_u8check_press();
					 if (x != NOTPRESSED)
					 {
						 if (isDigit(x))
						 {
							 LCD_vSend_char(x);
							 pass[i]=x;
							 _delay_ms(500);
							 --i;
							 LCD_movecursor(2,i+6);
							 LCD_vSend_char('*');
							 i++;
							 _delay_ms(250);
							 i++;
						 }
						 else if (x == '-')
						 {
							 if (i > 0)
							 {
								 i--;
								 LCD_movecursor(2, 5 + i);
								 LCD_vSend_char(' ');
								 LCD_movecursor(2, 5 + i);
								 _delay_ms(250);
							 }
						 }
					 }
				}
					
				LCD_clearscreen();
				if (EEPROM_read(0x21)==pass[0]&&EEPROM_read(0x22)==pass[1]&&EEPROM_read(0x23)==pass[2]&&EEPROM_read(0x24)==pass[3])
				{
					LCD_vSend_string("Correct Pass");
					_delay_ms(500);
					LCD_clearscreen();
					LCD_vSend_string("Safe Is Opened");
					flag=1;
				} 
				else
				{
					
					
					if (Tries==1)
					{
						LCD_clearscreen();
						LCD_vSend_string("Safe Is Closed");
						flag=1;
					}
					else
					{
						LCD_vSend_string("Wrong Pass");
						_delay_ms(500);
						LCD_clearscreen();
						Tries--;
						LCD_vSend_string("Tries:");
						LCD_vSend_char(Tries+48);
						_delay_ms(1000);
					}
				}
				
				
			
				
	  }
		
		
	}
}

bool isDigit(char key) {
	return (key >= '0' && key <= '9');
}


