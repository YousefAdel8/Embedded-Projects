#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include "DIO.h"
#include "std_macros.h"
#include "keypad_driver.h"
#include <stdbool.h>

bool isDigit(char key);
void printNumber(unsigned long num);

int main ()
{
	unsigned char x, flag1 = 0, flag2 = 0, operator1, operator2, op = 0;
	unsigned long result = 0, firstnum = 0, secondnum = 0;
	keypad_vInit();
	LCD_vInit();
	LCD_clearscreen();
	LCD_vSend_string("Calculator");
	_delay_ms(1000);
	LCD_clearscreen();
	LCD_movecursor(1, 1);
	
	while (1)
	{
		while (flag1 == 0)
		{
			x = keypad_u8check_press();
			if (x != NOTPRESSED)
			{
				if (isDigit(x))
				{
					LCD_vSend_char(x);
					firstnum = firstnum * 10 + (x - '0');
					_delay_ms(250);
					op = 1;
				}
				else if (op == 1)
				{
					if (x != NOTPRESSED)
					{
						if (x == '+')
						{
							operator1 = 0;
							LCD_vSend_char(x);
							_delay_ms(250);
							flag1 = 1;
							flag2 = 0;
							op = 0;
						}
						else if (x == '-')
						{
							operator1 = 1;
							LCD_vSend_char(x);
							_delay_ms(250);
							flag1 = 1;
							flag2 = 0;
							op = 0;
						}
						else if (x == '*')
						{
							operator1 = 2;
							LCD_vSend_char(x);
							_delay_ms(250);
							flag1 = 1;
							flag2 = 0;
							op = 0;
						}
						else if (x == '/')
						{
							operator1 = 3;
							LCD_vSend_char(x);
							_delay_ms(250);
							flag1 = 1;
							flag2 = 0;
							op = 0;
						}
						
						
						
					}
				}
				else
				{
					LCD_clearscreen();
					firstnum = 0;
					secondnum = 0;
					result = 0;
					flag1=0;
					flag2 = 1;
					op=0;
				}
			}
		}
		
		while (flag2 == 0)
		{
			x = keypad_u8check_press();
			if (x != NOTPRESSED)
			{
				if (isDigit(x))
				{
					LCD_vSend_char(x);
					secondnum = secondnum * 10 + (x - '0');
					_delay_ms(250);
					op = 1;
				}
				else if (op == 1)
				{
					if (x != NOTPRESSED)
					{
						
						
						if (x == '=')
						{
							if (operator1 == 0)
							{
								result = firstnum + secondnum;
							}
							else if (operator1 == 1)
							{
								result = firstnum - secondnum;
							}
							else if (operator1 == 2)
							{
								result = firstnum * secondnum;
							}
							else if (operator1 == 3)
							{
								result = firstnum / secondnum;
							}
							LCD_vSend_char(x);
							_delay_ms(250);
							printNumber(result);
							_delay_ms(250);
						}
						
						flag2 = 1;
						
					}
				}
				else
				{
					LCD_clearscreen();
					firstnum = 0;
					secondnum = 0;
					result = 0;
					flag1=0;
					flag2 = 1;
					op=0;
				}
			}
		}
		
		x = keypad_u8check_press();
		if (x != NOTPRESSED && x== 'A')
		{
			LCD_clearscreen();
			firstnum = 0;
			secondnum = 0;
			result = 0;
			flag1=0;
			op=0;
		}
		
		
	}
}

bool isDigit(char key) {
	return (key >= '0' && key <= '9');
}

void printNumber(unsigned long num) {
	char buffer[11];
	int i = 10;
	buffer[i] = '\0';
	
	do {
		buffer[--i] = (num % 10) + '0';
		num /= 10;
	} while (num != 0);
	
	LCD_vSend_string(&buffer[i]);
}
