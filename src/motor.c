#include "motor.h"

void motor_Init(struct MOTOR_STRUCT* motor){
    dio_SetDirection(motor->en.ddr, motor->en.pin, DIO_OUTPUT);
    dio_SetDirection(motor->ddr, motor->pin1, DIO_OUTPUT);
    dio_SetDirection(motor->ddr, motor->pin2, DIO_OUTPUT);
    pwm_DutyCycle(motor->en, 0);
}

void motor_Speed(struct MOTOR_STRUCT* motor, tenuDirection direction, uint8_t speed){
  pwm_DutyCycle(motor->en, 0);
  dio_SetBit(motor->ddr + 1, motor->pin1, 1^direction);
  dio_SetBit(motor->ddr + 1, motor->pin2, 0^direction);
  pwm_DutyCycle(motor->en, speed);
}

void motor_Stop(struct MOTOR_STRUCT* motor){
  pwm_DutyCycle(motor->en, 0);
}
