#ifndef __config__ 
#define __config__

#include "dio.h"

#define F_CPU 16000000UL
#define BAUD 9600 

#define ADC_VOLT_PER_STEP 5000/1024.0 

#define button1 dio_SetDirection('b', 0, INPUT_PULLUP) && dio_GetBit('b',0)


#define button2   dio_SetDirection('b', 1, INPUT_PULLUP) && dio_getbit('b',1)


#define button3  dio_SetDirection('b', 2, INPUT_PULLUP) && dio_getbit('b',2)


//LCD config
#define LCD_Dir  DDRD	
#define LCD_Port PORTD
#define RS_EN_Dir  DDRB		
#define RS_EN_Port PORTB  
#define RS PB0	
#define EN PB1 

//main loop delay
#define DELAY_LOOP 100

#endif
