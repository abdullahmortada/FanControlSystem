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

    pwm_Init(PWM_PD6);
    
    int i=0 ;
    int speed=0

    mode[i]={cooling,extreme cooling, heating ,custom}

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
            else if (i<5)

            {
            i=0;
            }
            

        }
        if (i==4  && button2 !=0)
        {
            //custom mode 
            speed+=15;
            pwm_DutyCycle(PWM_PD6, speed);
            
            
            
        }
         if (i==4  && button3 != 0)
        {
            //custom mode 
            speed-=15;
            pwm_DutyCycle(PWM_PD6, speed);
            
            
        }
    }
   

}


