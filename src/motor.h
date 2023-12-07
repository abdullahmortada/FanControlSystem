#ifndef __DC_MOTOR
#define __DC_MOTOR

#include "dio.h"
#include "pwm.h"

typedef enum {
    DIRECTION_CW = 0,
    DIRECTION_CCW
} tenuDirection;

struct MOTOR_STRUCT{
  struct PWM_PIN en;
  uint8_t pin1;
  uint8_t pin2;
  uint8_t speed;
  volatile uint8_t* ddr;
};

void motor_Init(struct MOTOR_STRUCT* motor);

void motor_Go(struct MOTOR_STRUCT* motor, tenuDirection Direction);

void motor_Stop(struct MOTOR_STRUCT* motor);

#endif
