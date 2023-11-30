#include "pwm.h"

void pwm_DutyCycle(uint8_t timer, uint8_t channel, uint8_t DutyCycle){
  timerStart(timer, TIMER_MODE_PWM, channel, PRESCALER_NONE, DutyCycle);
}

