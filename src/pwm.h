#ifndef __PWM__
#define __PWM__

#include <avr/io.h>
#include "dio.h"
#include "timer.h"

struct PWM_PIN{
  uint8_t timer;
  uint8_t channel;
  uint8_t pin;
  volatile uint8_t* ddr;
};

static struct PWM_PIN PWM_PD6;
static struct PWM_PIN PWM_PD5;
static struct PWM_PIN PWM_PB1;
static struct PWM_PIN PWM_PB2;
static struct PWM_PIN PWM_PB3;
static struct PWM_PIN PWM_PD3;

void pwm_Setup();

void pwm_Init(struct PWM_PIN pwmPin);

void pwm_DutyCycle(struct PWM_PIN pwmPin, uint16_t dutyCycle);

#endif
