#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "LED.h"
#include "DIO.h"
#include "std_macros.h"


int main(void) 
{
    
	DIO_vsetPINDir('B', 3, 0); 
	LED_vInit('B', 2); //led and buzzer

	while (1) 
	{
		unsigned int sensor_Read = READ_BIT(PINB, 3);  // 0 means you clapped
		if (sensor_Read == 0) 
		{
			LED_vTurnOn('B', 2);
		}
		else
		{
			LED_vTurnOff('B', 2);
		}

	}
}


