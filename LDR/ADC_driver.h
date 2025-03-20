


#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_
void ADC_vinit(void);
 unsigned short ADC_u16Read(void);
 void PWM_init();
void PWM_set_duty_cycle_percent(uint8_t percent);
void PWM_init_rgb();
void PWM_set_rgb(uint8_t red_percent, uint8_t green_percent, uint8_t blue_percent);

#endif /* ADC_DRIVER_H_ */