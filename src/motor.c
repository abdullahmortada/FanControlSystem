#include "motor.h"


void DC_Init(){
  for(int i = 0; i < sizeof(MotorArray)/sizeof(MotorArray[0]); i++){
    dio_SetDirection(MOTOR_DIR_PORT, MotorArray[i][0], DIO_OUTPUT);
    dio_SetDirection(MOTOR_DIR_PORT, MotorArray[i][1], DIO_OUTPUT);
  }
}


void DC_Start(unsigned char motorID, tenuDirection direction, unsigned char speed){
  dio_SetBit(MOTOR_PORT, MotorArray[motorID][0], direction ^ 1);
  dio_SetBit(MOTOR_PORT, MotorArray[motorID][1], direction ^ 0);
}

void DC_Stop(unsigned char motorID){
  dio_SetBit(MOTOR_PORT, MotorArray[motorID][0], 0);
  dio_SetBit(MOTOR_PORT, MotorArray[motorID][1], 0);
}
