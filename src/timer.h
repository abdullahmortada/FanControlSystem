#ifndef __timer__
#define __timer__

#include <stdint.h>
#include <stddef.h>

#define TIMER_MODE_PWM 0 
#define TIMER_MODE_COUNT 1

#define TIMER_CTRlA 0 
#define TIMER_CMPA 1
#define TIMER_CMPB 2
#define TIMER_INTMASK 3

#define COMX 6

#define __SFR_8(mem_addr) (volatile uint8_t *)(mem_addr)
#define __SFR_16(mem_addr) (volatile uint16_t *)(mem_addr)

#define TIMER0_CMPA __SFR_8(0x47)
#define TIMER0_CMPB __SFR_8(0x48)
#define TIMER1_CMPA __SFR_16(0x88)
#define TIMER1_CMPB __SFR_16(0x8A)
#define TIMER2_CMPA __SFR_8(0xB3)
#define TIMER2_CMPB __SFR_8(0xB4)


typedef enum {
  PRESCALER_NONE = 1,
  PRESCALER_8,
  PRESCALER_64,
  PRESCALER_256,
  PRESCALER_1024
} timer_prescaler;


static volatile uint8_t* TIMER_ARRAY[][7] = 
  //Ctrl         ,CmpA          ,CmpB          ,IntMsk
  {{__SFR_8(0x44), __SFR_8(0x47), __SFR_8(0x48), __SFR_8(0x6E)},
   {__SFR_8(0x80), __SFR_8(0x88), __SFR_8(0x8A), __SFR_8(0x6F)},
   {__SFR_8(0xB0), __SFR_8(0xB3), __SFR_8(0xB4), __SFR_8(0x70)}};


void timerStart(uint8_t timer, 
    uint8_t mode, 
    uint8_t channel, 
    timer_prescaler prescaler, 
    size_t compare);

void timerPWM(uint8_t timer, uint8_t channel);

void timerCount(uint8_t timer);
#endif
