#include "dio.h"

inline void dio_SetBit(volatile uint8_t* reg, uint8_t bit, uint8_t val){
  *reg &= ~DIO_BITMASK(1, bit);
  *reg |= DIO_BITMASK(val, bit);
}

inline uint8_t dio_GetBit(volatile uint8_t* reg, uint8_t bit){
  return ((*reg) >> bit) & 1; //right shift to have value in first bit, then clear other bits
}

void dio_SetDirection(volatile uint8_t* reg, uint8_t bit, int8_t direction){
  if(direction == DIO_PULLUP){
    direction = DIO_INPUT;
    dio_SetBit(reg + 1, bit, 1); //PORTX is address after PINX
  }
  dio_SetBit(reg, bit, direction); //input or output
}
