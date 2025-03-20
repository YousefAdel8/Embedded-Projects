#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "DIO.h"
#include "std_macros.h"
#include "LCD.h"

void DHT11_Request(void);
unsigned char DHT11_Read(void);


int main(void) 
{
	LCD_vInit();
    unsigned char humidity,humidity_decimal,temp,temp_decimal,checksum;
	LCD_vSend_string("temp:");
	LCD_movecursor(2,1);
	LCD_vSend_string("humidity:");
	while (1) 
	{
		DHT11_Request();
		humidity=DHT11_Read();
		humidity_decimal=DHT11_Read();
		temp=DHT11_Read();
		temp_decimal=DHT11_Read();
		checksum=DHT11_Read();
		if (checksum==(humidity+humidity_decimal+temp+temp_decimal))
		{
			LCD_movecursor(1,6);
			LCD_vSend_char((temp/10)+48);
			LCD_vSend_char((temp%10)+48);
			LCD_vSend_char('.');
			LCD_vSend_char((temp_decimal/10)+48);
			LCD_vSend_char((temp_decimal%10)+48);
			LCD_movecursor(2,10);
			LCD_vSend_char((humidity/10)+48);
			LCD_vSend_char((humidity%10)+48);
			LCD_vSend_char('.');
			LCD_vSend_char((humidity_decimal/10)+48);
			LCD_vSend_char((humidity_decimal%10)+48);
			
		}
		else
		{
			LCD_clearscreen();
			LCD_vSend_string("Problem");
		}
		_delay_ms(2000);
	}
}
void DHT11_Request(void)
{
	DIO_vsetPINDir('D',0,1); //output
	DIO_write('D',0,0);  //logic low for 18ms 
	_delay_ms(18);
	DIO_write('D',0,1); //logic low for (20us-40us)
	_delay_us(40);
	
	DIO_vsetPINDir('D',0,0); //input
	while(READ_BIT(PIND,0)==1); //Wait for response
	while(READ_BIT(PIND,0)==0);  //first response(logic low for 80us)
	while(READ_BIT(PIND,0)==1);  //second response(logic high for 80us)
}
unsigned char DHT11_Read(void)
{
	unsigned char data=0;
	for (unsigned char i=0;i<8;i++)
	{
		while (READ_BIT(PIND,0)==0); //wait for 50us logic low
		_delay_us(30); //if it logic high for (26-28)us then bit=0 ,if it high for (70us) then bit=1
		if (READ_BIT(PIND,0)==1)
		{
			data|=(1<<(7-i));
		}
		while (READ_BIT(PIND,0)==1); //wait for all period of logic high
		
	}
	
	return data;
}
