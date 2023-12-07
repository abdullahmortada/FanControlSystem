#include "config.h" 

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

#define check_button(button) if(!dio_GetBit(__SFR_8(BUTTON_DDR - 1), button))
#define wait_button(button) while(!dio_GetBit(__SFR_8(BUTTON_DDR - 1), button))

volatile uint64_t TIME = 0;

volatile uint8_t MODES[] = {100, 175, 255};
volatile uint8_t current_mode = 0;

volatile uint8_t swing_mode = 0;

uint16_t servo_position = 0;

struct MOTOR_STRUCT motor;
struct DateTime dateTime;

void updateServoPosition() {
  servo_position = (servo_position < 510) ? (servo_position + 1) : 0;
  if (servo_position > 255){
    pwm_DutyCycle(PWM_PB1, 510 - servo_position);
  } else {
    pwm_DutyCycle(PWM_PB1, servo_position);
  }
}

void initButtons() {
  //set as input with pullup resistor
  dio_SetDirection(BUTTON_DDR, SWING_BUTTON, DIO_INPUT);
  dio_SetDirection(BUTTON_DDR, MODE_BUTTON, DIO_INPUT);
  dio_SetDirection(BUTTON_DDR, UP_BUTTON, DIO_INPUT);
  dio_SetDirection(BUTTON_DDR, DOWN_BUTTON, DIO_INPUT);

  dio_SetBit(BUTTON_DDR + 1, SWING_BUTTON, HIGH);
  dio_SetBit(BUTTON_DDR + 1, MODE_BUTTON, HIGH);
  dio_SetBit(BUTTON_DDR + 1, UP_BUTTON, HIGH);
  dio_SetBit(BUTTON_DDR + 1, DOWN_BUTTON, HIGH);

  // enable pin change interrupts for button port
  dio_SetBit(PCICR, BUTTON_PCIE, HIGH);

  // enable pin change interrupts for each pin
  dio_SetBit(BUTTON_PCMSK, SWING_BUTTON, HIGH);
  dio_SetBit(BUTTON_PCMSK, MODE_BUTTON, HIGH);
  dio_SetBit(BUTTON_PCMSK, UP_BUTTON, HIGH);
  dio_SetBit(BUTTON_PCMSK, DOWN_BUTTON, HIGH);
}


void updateLCD(struct DateTime* time, uint8_t heat) {
  lcd_Clear();

  char tmp[6];

  rtc_dt2timestr(time, tmp);
  lcd_StringXY(tmp, 5, 0, 1);

  intToString(heat, tmp, 10);
  lcd_StringXY("°C: ", 4, 0, 8);
  lcd_String(tmp, 2);
  uart_SendString("°C: ");
  uart_SendString(tmp);
  uart_Transmit('\n');

  intToString(current_mode, tmp, 10);
  lcd_StringXY("Mode: ", 6, 1, 1);
  lcd_String(tmp, 1);
  uart_SendString("Mode: ");
  uart_SendString(tmp);
  uart_Transmit('\n');

  intToString(motor.speed, tmp, 10);
  lcd_StringXY("Speed: ", 7, 1, 10);
  lcd_String(tmp, 3);
  uart_SendString("Speed: ");
  uart_SendString(tmp);
  uart_Transmit('\n');
}

int main() {

  timerStart(0, TIMER_MODE_COUNT, 0, PRESCALER_1024, ((uint64_t)F_CPU)/((uint64_t)1024*1000));

  uart_Init(9600);
  adc_Init();
  initButtons();
  lcd_Init();
  
  sei(); // global inturrupts enabled

  motor.en = MOTOR_EN;
  motor.pin1 = MOTOR_P1;
  motor.pin2 = MOTOR_P2;
  motor.ddr = MOTOR_DDR;

  while(1)
  {
    if(TIME % 100 == 0 && swing_mode){
      //update servo position
      updateServoPosition();
      // use updated to control servo
    }

    // if(TIME % 300 == 0){
    //     // double thermistorVoltage = adc_ReadChannel(THMISTOR_ADC_CHANNEL) * ADC_VOLT_PER_STEP;
    //     // double thermistorResistance = (ADC_REF_VOLTAGE / thermistorVoltage - 1) * THERMISTOR_RESISTOR;
    //     // double temperature = THERMISTOR_BETA / log(thermistorResistance / THERMISTOR_RESISTANCE_ROOM_TEMP);
    //     // temperature = temperature - KELVIN_OFFSET;  //to Cels\
    //
    //   double vOut = adc_ReadChannel(ADC_CHANNEL) * ADC_VOLT_PER_STEP;
    //   uint8_t heat = vOut / 10;
    //   
    //   rtc_Now(&dateTime);
    //   updateLCD(&dateTime, heat);
    //
    //   _delay_ms(1);
    // }

    lcd_String("hello", 5);
    double vOut = adc_ReadChannel(ADC_CHANNEL) * ADC_VOLT_PER_STEP;
    uint8_t heat = vOut / 10;
    
    rtc_Now(&dateTime);
    // updateLCD(&dateTime, heat);

    _delay_ms(10);
  }

}

ISR(TIMER1_COMPA_vect){
  //increment time elapsed every ms
  TIME += 1;
  uart_Transmit('a');
  uart_Transmit('\n');
}

ISR(PCINT0_vect){
    check_button(MODE_BUTTON){
      current_mode += 1;
      if(current_mode > 7) current_mode = 0;
      if((current_mode + 1) % 8 == 0) {
        motor.speed = eeprom_read(current_mode);
      } else {
        motor.speed = MODES[current_mode % 4];
      }
      motor_Go(&motor, (current_mode > 3));

      wait_button(MODE_BUTTON);
    }

    check_button(SWING_BUTTON){
      swing_mode = !swing_mode;
      wait_button(SWING_BUTTON);
    }

    check_button(UP_BUTTON){
      motor.speed += 10;
      motor.speed = clamp(motor.speed, MOTOR_MIN_SPEED, MOTOR_MAX_SPEED);
      motor_Go(&motor, (current_mode > 3));

      if((current_mode + 1) % 4 == 0){
        eeprom_write(current_mode, motor.speed);
      }
    }

    check_button(DOWN_BUTTON){

      motor.speed -= 10;
      motor.speed = clamp(motor.speed, MOTOR_MIN_SPEED, MOTOR_MAX_SPEED);
      motor_Go(&motor, (current_mode > 3));

      if((current_mode + 1) % 4 == 0){
        eeprom_write(current_mode, motor.speed);
      }
    }
}
