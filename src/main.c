#include "adc.h"
#include "config.h"
#include "timer.h"
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>  
#include <RTClib.h>


#define BUTTON1_PIN 5
#define BUTTON2_PIN 6
#define LCD_ADDR 0x27  
//i2c address of lcd (check this)
#define EEPROM_MODE_ADDR 0
#define RTC_UPDATE_INTERVAL 500
#define THMISTOR_ADC_CHANNEL 1

LiquidCrystal_I2C lcd(LCD_ADDR, 16, 2);
RTC_DS3231 rtc;


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

volatile unit8_t servo_position = 0;

//*ill fix the order put initwtv first then the updated after dw and please dont kill me
void updateServoPosition() {
    if (servo_position < 255) {
        servo_position++;
    } else {
        servo_position = 0;
      OCR1A = map(servo_position, 0, 255, 1000, 2000);  // map servo position to PWM signal
    }
}

void initADC() {
   // i used PORTC
    ADMUX |= (1 << REFS0);

    ADMUX &= ~((1 << MUX4) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));
// enable ADC and set prescaler to 128 (check please)
    ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
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
}

void initServoPWM() {
    // Set up PWM for servo control
    pinMode(SERVO_PIN, OUTPUT);
    // Set the PWM frequency (adjust as needed)
    TCCR1A = _BV(COM1A1) | _BV(WGM11);
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);
    ICR1 = 19999;  // 20ms period (50 Hz frequency)
}

void initEEPROM() {
   EECR |= (1 << EEMPE); //set EEMPE bit
    EECR |= (1 << EEPE); //set EEPE for EEPROM write
}

void writeModeToEEPROM() {
    eeprom_write_byte((uint8_t *)EEPROM_MODE_ADDR, current_mode);
}

void readModeFromEEPROM() {
    current_mode = eeprom_read_byte((uint8_t *)EEPROM_MODE_ADDR);
}

void initRTC() {
    if (!rtc.begin()) {
        //rtc initialization failure
        while (1) {
            // indicate error
        }
    }
}

void updateRTC() {
    DateTime now = rtc.now();
    // Use 'now' to get the current date and time information
    // Update your time-related functionality here
}


void initLCD() {
    lcd.init();                      // Initialize the LCD
    lcd.backlight();                 // Turn on the backlight (if your LCD has it)
    lcd.setCursor(0, 0);             // Set the cursor to the top-left corner
    lcd.print("Hello :3");  //initial message on the LCD
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
    // Button press handling code
    if (bit_is_set(PINB, BUTTON1_PIN)) {
        // Button 1 is pressed, handle accordingly
        if (current_mode == sizeof(MODES) / sizeof(MODES[0])) {
            // In custom mode
            // Save temperature to EEPROM
            eeprom_write_byte((uint8_t *)EEPROM_TEMP_ADDR, temperature);
        }
        // Increase temperature or perform other actions
    }
if (bit_is_set(PINB, BUTTON2_PIN)) {
        // Button 2 is pressed, handle accordingly
        // Toggle swing mode or perform other actions
        swing_mode = !swing_mode;
    }
}

int main() {

  timerStart(0, TIMER_MODE_COUNT, 0, PRESCALER_1024, (F_CPU)/(1024*1000));

    initADC();
    initButtons();
    initButtonInterrupts();
    initEEPROM();
    readModeFromEEPROM();
    initLCD();
    initRTC(); 
    initServoPWM();
    
    sei(); // global inturrupts enabled

  while(1)
  {
    if(TIME % 100 == 0 && swing_mode == 1){
      //update servo position
      updateServoPosition();
      // use updated to control servo
    }

    if(TIME % 300 == 0){
        double thermistorVoltage = adc_ReadChannel(THMISTOR_ADC_CHANNEL) * ADC_VOLT_PER_STEP;
        double thermistorResistance = (ADC_REF_VOLTAGE / thermistorVoltage - 1) * THERMISTOR_RESISTOR;
        double temperature = THERMISTOR_BETA / log(thermistorResistance / THERMISTOR_RESISTANCE_ROOM_TEMP);
        temperature = temperature - KELVIN_OFFSET;  //to Cels
      
     updateLCD((uint8_t)temperature, rtc.now());

      char lcdString[17]; 
        snprintf(lcdString, sizeof(lcdString), "Temp:%d Mode:%d %02d:%02d",
                 (uint8_t)temperature, current_mode, rtc.now().hour(), rtc.now().minute());
      
      lcd.setCursor(0, 1); 
      lcd.print(lcdString);

      //update lcd string 
      //output string on lcd
    }

    if(TIME % 500 == 0){
      //update time using rtc
      updateRTC();

     char lcdString[17]; 
        snprintf(lcdString, sizeof(lcdString), "Temp:%d Mode:%d %02d:%02d",
                 heat, current_mode, rtc.now().hour(), rtc.now().minute());
      lcd.setCursor(0, 1);
      lcd.print(lcdString);
      
    }
  }

}

ISR(TIMER1_COMPA_vect){
  TIME += 1;
}

//to init interrupts, set pcicr bit number 0 to 1 
//then MCMSK0 is like "portb", if u want interrupt on portb5, set bit number 5 in mcmsk0 to 1
ISR(PCINT0_vect){
handleButtonPress(); 
}
