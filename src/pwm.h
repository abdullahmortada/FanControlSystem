#ifndef __PWM__
#define __PWM__

#include "timer.h"

#define PWM_PD6 0,0
#define PWM_PD5 0,1
#define PWM_PB1 1,0
#define PWM_PB2 1,1
#define PWM_PB3 2,0
#define PWM_PD3 2,2

void pwm_DutyCycle(uint8_t timer, uint8_t channel, uint8_t DutyCycle);

#endif
