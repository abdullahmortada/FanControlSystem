#include "timer.h"
#include <avr/interrupt.h>

void timerStart(uint8_t timer, uint8_t mode, uint8_t channel, timer_prescaler prescaler, size_t compare){

  //controlB register
  *(volatile uint8_t*)(TIMER_ARRAY[timer][0] + 1) &= 0xF8;
  *(volatile uint8_t*)(TIMER_ARRAY[timer][0] + 1) |= prescaler;

  //compare register
  *(volatile uint8_t*)TIMER_ARRAY[timer][2 + (2*channel)] &= 0;
  *(volatile uint8_t*)TIMER_ARRAY[timer][2 + (2*channel)] |= compare;

  if(timer == 1){
    *(volatile uint8_t*)TIMER_ARRAY[timer][1 + (2*channel)] &= 0;
    *(volatile uint8_t*)TIMER_ARRAY[timer][1 + (2*channel)] |= (compare >> 8);
  }

  if(mode == TIMER_MODE_PWM) timerPWM(timer, channel);
  else timerCount(timer);
}

void timerPWM(uint8_t timer, uint8_t channel){
  //clear ocx on match
  *(volatile uint8_t*)TIMER_ARRAY[timer][0] |= 1<<(COMX+1-(channel*2));

  if(timer != 1){
    //wave generator
    *(volatile uint8_t*)TIMER_ARRAY[timer][0] &= 0xFC;
    *(volatile uint8_t*)TIMER_ARRAY[timer][0] |= 3;
    return;
  }

  *(volatile uint8_t*)(TIMER_ARRAY[timer][0] + 1) |= 1<<3;
  *(volatile uint8_t*)TIMER_ARRAY[timer][0] |= 1;

}

void timerCount(uint8_t timer){
  //normal port operation, com = 0
  *(volatile uint8_t*)TIMER_ARRAY[timer][0] = 0;

  if(timer != 1){
    //wgmx1 = 1, mode ctc
    *(volatile uint8_t*)TIMER_ARRAY[timer][0] |= 2;
    return;
  }

  //wgm12 = 1, mode ctc
  *(volatile uint8_t*)(TIMER_ARRAY[timer][0] + 1) |= 1<<3;
}
