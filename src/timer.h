#ifndef __timer__
#define __timer__

#include <stdint.h>
#include <stddef.h>

#define TIMER_MODE_PWM 0 
#define TIMER_MODE_COUNT 1

#define COMX 6

typedef enum {
  PRESCALER_NONE = 1,
  PRESCALER_8,
  PRESCALER_64,
  PRESCALER_256,
  PRESCALER_1024
} timer_prescaler;

uint8_t TIMER_ARRAY[][7] = 
  //Ctrl,CmpAH,CmpAL,CmpBH,CmpBL, IntMsk, IntFlag
  {{0x44, 0   , 0x47, 0   , 0x48, 0x6E, 0x35},
   {0x80, 0x89, 0x88, 0x8B, 0x8A, 0x6F, 0x36},
   {0xB0, 0   , 0xB3, 0   , 0xB4, 0x70, 0x37}};

void timerStart(uint8_t timer, 
    uint8_t mode, 
    uint8_t channel, 
    timer_prescaler prescaler, 
    size_t compare);

void timerPWM(uint8_t timer, uint8_t channel);

void timerCount(uint8_t timer);
#endif
