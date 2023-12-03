#include "adc.h"
#include "config.h"
#include "timer.h"
#include <stdio.h>
#include <avr/interrupt.h>

//dc motor -> update on mode/speed change 
//servo motor -> update every 100ms IF swing mode is on
//lcd -> update temp and time every 300 ms 
//rtc -> update every 500ms 
//eeprom -> update data when button pressed, fetch data on boot and when mode changed 
//buttons dio -> interrupt to update mode, speed and swing 
//thermistor -> update before lcd cycle 
//
//
//2 buttons for temp up and down WHEN in custom mode 
//1 button for mode change 
//1 button for swing on/off 
//
//for mode change: 
//  i++, if i > size of mode, then u are in custom mode 
//  in custom mode save temp to eeprom and read from eeprom the temp when u first get into mode 

volatile uint64_t TIME = 0;

volatile uint8_t MODES[] = {100, 175, 255};
volatile uint8_t current_mode = 0;

volatile uint8_t swing_mode = 0;

int main() {

  timerStart(0, TIMER_MODE_COUNT, 0, PRESCALER_1024, (F_CPU)/(1024*1000));

  //init adc 
  
  //init button
  //init button interrupts


  while(1)
  {
    if(TIME % 100 == 0 && swing_mode == 1){
      //update servo position
    }

    if(TIME % 300 == 0){
      double vOut= adc_ReadChannel(1) * ADC_VOLT_PER_STEP;
      //5000 v cause milli volt
      uint8_t heat = vOut / 10;
      

      //update lcd string 
      //output string on lcd
    }

    if(TIME % 500 == 0){
      //update time using rtc

      //update lcd string 
    }
  }

}

ISR(TIMER1_COMPA_vect){
  TIME += 1;
}

//to init interrupts, set pcicr bit number 0 to 1 
//then MCMSK0 is like "portb", if u want interrupt on portb5, set bit number 5 in mcmsk0 to 1
ISR(PCINT0_vect){

}
