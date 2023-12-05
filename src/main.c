#include <avr/interrupt.h>
#include <stdio.h>
#include "adc.h"
#include "config.h"
#include "dio.h"
#include "timer.h"
#include "eeprom.h"
#include "pwm.h"
#include "rtc.h"
#include "lcd.h"

#define BUTTON1_PIN 5
#define BUTTON2_PIN 6
#define LCD_ADDR 0x27  
//i2c address of lcd (check this)
#define EEPROM_MODE_ADDR 0
#define RTC_UPDATE_INTERVAL 500
#define THMISTOR_ADC_CHANNEL 1

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

uint16_t servo_position = 0;

//*ill fix the order put initwtv first then the updated after dw and please dont kill me
void updateServoPosition() {
  servo_position = (servo_position < 510) ? (servo_position + 1) : 0;
  if (servo_position > 255){
    pwm_DutyCycle(PWM_PB1, 510 - servo_position);
  } else {
    pwm_DutyCycle(PWM_PB1, servo_position);
  }
}

// note from fatima: button1 and button2 pins please chang them to the actual pin numbers ty :3
void initButtons() {
  // i used PORTB
      // pull-up resistors
    PORTB |= (1 << BUTTON1_PIN) | (1 << BUTTON2_PIN);
}

void initButtonInterrupts() {
 // enable pin change interrupts for PORTB
    PCICR |= (1 << PCIE0);

    //set specific pins for pin change interrupts (BUTTON1_PIN and BUTTON2_PIN)
    PCMSK0 |= (1 << BUTTON1_PIN) | (1 << BUTTON2_PIN);
}


void updateLCD(uint8_t heat, time) {
    lcd.clear();                // Clear the LCD screen
    lcd.setCursor(0, 0);        // Set the cursor to the top-left corner
    lcd.print("Temperature: "); 
    lcd.print(heat);  
    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    lcd.print(now.hour());
    lcd.print(":");
    lcd.print(now.minute());
    // do we need more?
}

void handleButtonPress() {
}

int main() {

  timerStart(0, TIMER_MODE_COUNT, 0, PRESCALER_1024, (F_CPU)/(1024*1000));

    adc_Init();
    initButtons();
    initButtonInterrupts();
    lcd_Init();
    
    sei(); // global inturrupts enabled

  while(1)
  {
    if(TIME % 100 == 0 && swing_mode == 1){
      //update servo position
      updateServoPosition();
      // use updated to control servo
    }

    if(TIME % 300 == 0){
        // double thermistorVoltage = adc_ReadChannel(THMISTOR_ADC_CHANNEL) * ADC_VOLT_PER_STEP;
        // double thermistorResistance = (ADC_REF_VOLTAGE / thermistorVoltage - 1) * THERMISTOR_RESISTOR;
        // double temperature = THERMISTOR_BETA / log(thermistorResistance / THERMISTOR_RESISTANCE_ROOM_TEMP);
        // temperature = temperature - KELVIN_OFFSET;  //to Cels\

      double vOut = adc_ReadChannel(1) * ADC_VOLT_PER_STEP;
      uint8_t heat = vOut / 10;
      
      updateRTC();
      updateLCD(heat);

      char lcdString[17]; 
      snprintf(lcdString, sizeof(lcdString), "Temp:%d Mode:%d %02d:%02d",
                 heat, current_mode, , );
      
      lcd.setCursor(0, 1); 
      lcd.print(lcdString);

      //update lcd string 
      //output string on lcd
    }

  }

}

ISR(TIMER1_COMPA_vect){
  TIME += 1;
}

//to init interrupts, set pcicr bit number 0 to 1 
//then MCMSK0 is like "portb", if u want interrupt on portb5, set bit number 5 in mcmsk0 to 1
ISR(PCINT0_vect){
    // Button press handling code
    if (dio_GetBit(PINB, BUTTON1_PIN)) {
        // Button 1 is pressed, handle accordingly
        if (current_mode == sizeof(MODES) / sizeof(MODES[0])) {
            // In custom mode
            // Save temperature to EEPROM
            eeprom_write_byte((uint8_t *)EEPROM_TEMP_ADDR, temperature);
        }
        // Increase temperature or perform other actions
    }
    if (dio_GetBit(PINB, BUTTON2_PIN)) {
        // Button 2 is pressed, handle accordingly
        // Toggle swing mode or perform other actions
        swing_mode = !swing_mode;
    }
}
