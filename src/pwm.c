#include "pwm.h"

void pwm_Init(struct PWM_PIN pwmPin){
  dio_SetDirection(pwmPin.ddr, pwmPin.pin, DIO_OUTPUT);
  pwm_DutyCycle(pwmPin, 0);
}

void pwm_DutyCycle(struct PWM_PIN pwmPin, uint16_t dutyCycle){
  timerStart(pwmPin.timer, TIMER_MODE_PWM, pwmPin.channel, PRESCALER_NONE, dutyCycle);
}

