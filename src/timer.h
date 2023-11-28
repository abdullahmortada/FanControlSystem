#ifndef __timer__
#define __timer__

#include <stdint.h>
#include <stddef.h>

#define TIMER_MODE_PWM 0 
#define TIMER_MODE_COUNT 1

#define TIMER_CTRlA 0 
#define TIMER_CMPAH 1
#define TIMER_CMPAL 2 
#define TIMER_CMPBH 3
#define TIMER_CMPBL 4 
#define TIMER_INTMASK 5
#define TIMER_INTFLAG 6

#define COMX 6

typedef enum {
  PRESCALER_NONE = 1,
  PRESCALER_8,
  PRESCALER_64,
  PRESCALER_256,
  PRESCALER_1024
} timer_prescaler;

void timerStart(uint8_t timer, 
    uint8_t mode, 
    uint8_t channel, 
    timer_prescaler prescaler, 
    size_t compare);

void timerPWM(uint8_t timer, uint8_t channel);

void timerCount(uint8_t timer);
#endif
