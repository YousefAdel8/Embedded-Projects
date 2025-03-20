#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "LED.h"
#include "DIO.h"
#include "std_macros.h"
#define DEBOUNCE_DELAY 50
#define DETECTION_DELAY 400
uint32_t delay(void);
int main(void) {
	uint8_t clap = 0;
	uint32_t detection_range_start = 0;
	uint32_t detection_range = 0;
	uint8_t sensor_state = 0;
	DIO_vsetPINDir('B',3,0);
	LED_vInit('B',2);
	while (1) {
		sensor_state=READ_BIT(PINB,3);
		
		if (sensor_state == 0) {
			if (clap == 0) {
				detection_range_start = detection_range = delay();
				clap++;
				} else if (clap > 0 && (delay() - detection_range >= DEBOUNCE_DELAY)) {
				detection_range = delay();
				clap++;
			}
		}

		if (delay() - detection_range_start >= DETECTION_DELAY) {
			if (clap == 2) {
				LED_vToggle('B',2);
			}
			clap = 0;
		}
	}
}

uint32_t delay(void) {
	static uint32_t counter = 0;
	_delay_ms(1);
	counter++;
	return counter;
}


