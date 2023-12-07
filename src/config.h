#ifndef __config__ 
#define __config__

#include <stdio.h>
#include <util/delay.h>
#include "helpers.h"
#include "uart.h"
#include "adc.h"
#include "dio.h"
#include "timer.h"
#include "eeprom.h"
#include "pwm.h"
#include "rtc.h"
#include "lcd.h"
#include "helpers.h"
#include "i2c.h"
#include "motor.h"

#define BAUD 9600 

#define MOTOR_MIN_SPEED 60
#define MOTOR_LOW_SPEED 110
#define MOTOR_MED_SPEED 170
#define MOTOR_HIGH_SPEED 210
#define MOTOR_MAX_SPEED 240

#define MOTOR_EN PWM_PD6
#define MOTOR_P1 7 
#define MOTOR_P2 5
#define MOTOR_DDR DDRD
#define MOTOR_DDR_ADDE DDRD_ADDR

#define ADC_VOLT_PER_STEP 1100/1024.0 
#define ADC_CHANNEL 0 

#define BUTTON_DDR DDRB
#define BUTTON_PCIE 0
#define BUTTON_PCMSK PCMSK0
#define SWING_BUTTON 0
#define MODE_BUTTON 1
#define UP_BUTTON 2
#define DOWN_BUTTON 3

//main loop delay
#define DELAY_LOOP 100

#define ISR(vector, ...)            \
    void vector (void) __attribute__ ((signal) __VA_ARGS__); \
    void vector (void)

#define sei()  __asm__ __volatile__ ("sei" ::: "memory")
#endif
