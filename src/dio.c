#include "dio.h"

void dio_SetDirection(volatile uint8_t* reg, uint8_t bit, int8_t direction){
  if(direction == DIO_PULLUP){
    direction = DIO_INPUT;
    dio_SetBit(reg + 1, bit, 1); //PORTX is address after PINX
  }
  dio_SetBit(reg, bit, direction); //input or output
}
