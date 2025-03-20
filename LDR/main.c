#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "ADC_driver.h"
#include "LED.h"


int main(void) {
	unsigned short x;
	ADC_vinit();
	 LED_vInit('B',2);
	while (1) {
		
		x=((ADC_u16Read()* 5.0) / 1024.0);
        
		if (x > 3.2) {
			LED_vTurnOn('B',2);
			} else {
			LED_vTurnOff('B',2);
		}

		_delay_ms(500);
	}
}

