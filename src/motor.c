#include "motor.h"

void motor_Init(struct MOTOR_STRUCT* motor){
    dio_SetDirection(motor->pin1.ddr, motor->pin1.pin, DIO_OUTPUT);
    dio_SetDirection(motor->pin2.ddr, motor->pin2.pin, DIO_OUTPUT);
}

void motor_Speed(struct MOTOR_STRUCT* motor, tenuDirection direction, uint8_t speed){
  pwm_DutyCycle(motor->pin1, speed*(1^direction));
  pwm_DutyCycle(motor->pin2, speed*(0^direction));
}

void motor_Stop(struct MOTOR_STRUCT* motor){
  pwm_DutyCycle(motor->pin1, 0);
  pwm_DutyCycle(motor->pin2, 0);
}
