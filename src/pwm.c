#include "pwm.h"

void pwm_Setup(){
  PWM_PD6.timer = 0; PWM_PD6.channel = 0; PWM_PD6.pin = 6; PWM_PD6.ddr = &DDRD;
  PWM_PD5.timer = 0; PWM_PD5.channel = 1; PWM_PD5.pin = 5; PWM_PD5.ddr = &DDRD;
  PWM_PB1.timer = 1; PWM_PB1.channel = 0; PWM_PB1.pin = 1; PWM_PB1.ddr = &DDRB;
  PWM_PB2.timer = 1; PWM_PB2.channel = 1; PWM_PB2.pin = 2; PWM_PB2.ddr = &DDRB;
  PWM_PB3.timer = 2; PWM_PB3.channel = 0; PWM_PB3.pin = 3; PWM_PB3.ddr = &DDRB;
  PWM_PD3.timer = 2; PWM_PD3.channel = 1; PWM_PD3.pin = 3; PWM_PD3.ddr = &DDRD;
}

void pwm_Init(struct PWM_PIN pwmPin){
  dio_SetDirection(pwmPin.ddr, pwmPin.pin, DIO_OUTPUT);
  pwm_DutyCycle(pwmPin, 0);
}

void pwm_DutyCycle(struct PWM_PIN pwmPin, uint16_t dutyCycle){
  timerStart(pwmPin.timer, TIMER_MODE_PWM, pwmPin.channel, PRESCALER_NONE, dutyCycle);
}

