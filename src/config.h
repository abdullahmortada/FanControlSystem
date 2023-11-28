#ifndef __config__ 
#define __config__

#include <stdint.h>

#define F_CPU 16000000UL
#define BAUD 9600 

#define ADC_VOLT_PER_STEP 5.0/1024.0 

//LCD config
#define LCD_Dir  DDRD	
#define LCD_Port PORTD
#define RS_EN_Dir  DDRB		
#define RS_EN_Port PORTB  
#define RS PB0	
#define EN PB1 

//main loop delay
#define DELAY_LOOP 100

#define MOTOR_DIR_PORT DDRD
#define MOTOR_PORT PORTD
#define MOTOR_NUM 1
uint8_t MotorArray[][2] = {{2, 3}};

#endif
