#include <stdio.h>
#include "adc.h"
#include "lcd.h"
#include "dio.h"
#include "config.h"
#include "eeprom.h"


int main() {
    
    uart_Init(BAUD);
    Adc_int();
    lcd_int();
    motor_Init(pin1);
    pwm_Init(PWM_PD6);
    
    int i=0 ;
    int pace=0

    mode[i]={cooling,extreme cooling, heating ,custom1 ,custom2}

    while(1)
    {

        int analog=adc_ReadChannel(1);
        int heat=analog*ADC_VOLT_PER_STEP 
;
        //5000 v cause milli volt
        //n number of bits
        int temp= heat/10;
        //make it degree celcius 10 mv per 1 degree



        if (button1 != 0)
        {
            mode[i++];
            else if (i<6)

            {
            i=0;
            }
            

        }

         if (i==1)
        {
            mode[1];
            //cooling mode
            pace=150
            motor_Speed(pin1, DIRECTION_CW , uint8_t Speed);
            pwm_DutyCycle(PWM_PD6, pace);

        }


        
         if (i==2)
        {
            mode[2];
            //extreme cooling mode
            pace=250
            motor_Speed(pin1, DIRECTION_CW , uint8_t Speed);
            pwm_DutyCycle(PWM_PD6, pace);

        }
        if (i==3)
        {
            mode[3];
            //heating mode
            motor_Speed(pin1, DIRECTION_CCW , uint8_t Speed);
            pace=150
            pwm_DutyCycle(PWM_PD6, pace);

        }

        if (i==4  && button2 !=0)
        {
            mode[4];
            pace+=15;
            motor_Speed(pin1, DIRECTION_CW , uint8_t Speed);
            pwm_DutyCycle(PWM_PD6, pace);
            
            
            
        
            else if ( button3 != 0)
            {
                mode[4];
                pace-=15;
                motor_Speed(pin1, DIRECTION_CW , uint8_t Speed);
                pwm_DutyCycle(PWM_PD6, pace);
            
            
            }
        }
        if (i==5  && button2 !=0)
        {
            mode[5];
            pace+=15;
            motor_Speed(pin1, DIRECTION_CCW , uint8_t Speed);
            pwm_DutyCycle(PWM_PD6, pace);
            
            
            
        
            else if ( button3 != 0)
            {
                mode[5];
                pace-=15;
                motor_Speed(pin1, DIRECTION_CCW , uint8_t Speed);
                pwm_DutyCycle(PWM_PD6, pace);
            
            
            }
        }
    }
   

}


