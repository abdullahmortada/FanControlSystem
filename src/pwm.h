#ifndef __PWM__
#define __PWM__

#include "dio.h"
#include "timer.h"

struct PWM_PIN{
  uint8_t timer;
  uint8_t channel;
  uint8_t pin;
  volatile uint8_t* ddr;
};

static struct PWM_PIN PWM_PD6 = {0,0,6,DDRD};
static struct PWM_PIN PWM_PD5 = {0,1,5,DDRD};
static struct PWM_PIN PWM_PB1 = {1,0,1,DDRB};
static struct PWM_PIN PWM_PB2 = {1,1,2,DDRB};
static struct PWM_PIN PWM_PB3 = {2,0,3,DDRB};
static struct PWM_PIN PWM_PD3 = {2,2,3,DDRD};

void pwm_Init(struct PWM_PIN pwmPin);

void pwm_DutyCycle(struct PWM_PIN pwmPin, size_t dutyCycle);

#endif
