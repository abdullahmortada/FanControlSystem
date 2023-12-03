#include "timer.h"

void timerStart(uint8_t timer, uint8_t mode, uint8_t channel, timer_prescaler prescaler, uint16_t compare){

  //controlB register
  *(TIMER_ARRAY[timer][TIMER_CTRlA] + 1) &= 0xF8;
  *(TIMER_ARRAY[timer][TIMER_CTRlA] + 1) |= (uint8_t)prescaler;

  //compare register
  if(timer == 1)
    *(TIMER1_CMPA + 2*channel) = compare;
  else 
    *TIMER_ARRAY[timer][TIMER_CMPA + (2*channel)] = compare;

  if(mode == TIMER_MODE_COUNT) {
    timerCount(timer);
    // *TIMER_ARRAY[timer][TIMER_INTMASK] |= (1<<1);
    *TIMER_ARRAY[timer][TIMER_INTMASK] |= (1<<(channel + 1));
    return;
  }
  timerPWM(timer, channel);
}

void timerPWM(uint8_t timer, uint8_t channel){
  //clear ocx on match
  *TIMER_ARRAY[timer][TIMER_CTRlA] |= 1<<(COMX+1-(channel*2));

  if(timer != 1){
    //wave generator
    *TIMER_ARRAY[timer][TIMER_CTRlA] &= 0xFC;
    *TIMER_ARRAY[timer][TIMER_CTRlA] |= 3;
    return;
  }

  *(TIMER_ARRAY[timer][TIMER_CTRlA] + 1) |= 1<<3;
  *TIMER_ARRAY[timer][TIMER_CTRlA] |= 1;

}

void timerCount(uint8_t timer){
  //normal port operation, com = 0
  *TIMER_ARRAY[timer][TIMER_CTRlA] = 0;

  if(timer != 1){
    //wgmx1 = 1, mode ctc
    *TIMER_ARRAY[timer][TIMER_CTRlA] |= 2;
    return;
  }

  //wgm12 = 1, mode ctc
  *(TIMER_ARRAY[timer][TIMER_CTRlA] + 1) |= 1<<3;
}
