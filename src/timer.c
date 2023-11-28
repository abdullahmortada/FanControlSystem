#include "timer.h"
#include <avr/interrupt.h>
#include <avr/io.h>

volatile uint8_t* TIMER_ARRAY[][7] = 
  //Ctrl           ,CmpAH,CmpAL,CmpBH,CmpBL, IntMsk, IntFlag
  {{&_SFR_MEM8(0x44), 0               , &_SFR_MEM8(0x47), 0               , &_SFR_MEM8(0x48), &_SFR_MEM8(0x6E), &_SFR_MEM8(0x35)},
   {&_SFR_MEM8(0x80), &_SFR_MEM8(0x89), &_SFR_MEM8(0x88), &_SFR_MEM8(0x8B), &_SFR_MEM8(0x8A), &_SFR_MEM8(0x6F), &_SFR_MEM8(0x36)},
   {&_SFR_MEM8(0xB0), 0               , &_SFR_MEM8(0xB3), 0               , &_SFR_MEM8(0xB4), &_SFR_MEM8(0x70), &_SFR_MEM8(0x37)}};

void timerStart(uint8_t timer, uint8_t mode, uint8_t channel, timer_prescaler prescaler, size_t compare){

  *TIMER_ARRAY[0][1] |= 1<<5;
  //controlB register
  *(TIMER_ARRAY[timer][TIMER_CTRlA] + 1) &= 0xF8;
  *(TIMER_ARRAY[timer][TIMER_CTRlA] + 1) |= prescaler;

  //compare register
  *TIMER_ARRAY[timer][TIMER_CMPAL + (2*channel)] = compare;

  if(timer == 1){
    *TIMER_ARRAY[timer][TIMER_CMPAH + (2*channel)] = (compare >> 8);
  }

  if(mode == TIMER_MODE_COUNT) {
    timerCount(timer);
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
