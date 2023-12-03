#ifndef __DC_MOTOR
#define __DC_MOTOR

#include "dio.h"
#include "pwm.h"

typedef enum {
    DIRECTION_CW = 0,
    DIRECTION_CCW
} tenuDirection;

struct MOTOR_STRUCT{
  struct PWM_PIN pin1;
  struct PWM_PIN pin2;
};

void motor_Init(struct MOTOR_STRUCT* motor);

void motor_Speed(struct MOTOR_STRUCT* motor, tenuDirection Direction, uint8_t Speed);

void motor_Stop(struct MOTOR_STRUCT* motor);

#endif
