#ifndef _dio_ 
#define _dio_ 

#include <stdint.h>
#include "sfrdef.h"

#define DIO_INPUT 0
#define DIO_OUTPUT 1
#define DIO_PULLUP 2

#define HIGH 1
#define LOW 0

#define DIO_BITMASK(val, bit) (val<<bit)

#define PORTB_ADDR (0x25)
#define PORTC_ADDR (0x28)
#define PORTD_ADDR (0x2B)

#define DDRB_ADDR (0x24)
#define DDRC_ADDR (0x27)
#define DDRD_ADDR (0x2A)

#define PINB_ADDR (0x23)
#define PINC_ADDR (0x26)
#define PIND_ADDR (0x29)

#define PORTB __SFR_8(0x25)
#define PORTC __SFR_8(0x28)
#define PORTD __SFR_8(0x2B)

#define DDRB __SFR_8(0x24)
#define DDRC __SFR_8(0x27)
#define DDRD __SFR_8(0x2A)

#define PINB __SFR_8(0x23)
#define PINC __SFR_8(0x26)
#define PIND __SFR_8(0x29)

#define PCICR __SFR_8(0x68)
#define PCMSK0 __SFR_8(0x6B)
#define PCMSK1 __SFR_8(0x6C)
#define PCMSK2 __SFR_8(0x6D)


inline void dio_SetBit(volatile uint8_t* reg, uint8_t bit, uint8_t val){
  *reg &= ~DIO_BITMASK(1, bit);
  *reg |= DIO_BITMASK(val, bit);
}

inline uint8_t dio_GetBit(volatile uint8_t* reg, uint8_t bit){
  return ((*reg) >> bit) & 1; //right shift to have value in first bit, then clear other bits
}

void dio_SetDirection(volatile uint8_t* reg, uint8_t bit, int8_t direction);

#endif 
