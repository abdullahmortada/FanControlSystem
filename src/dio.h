#ifndef _dio_ 
#define _dio_ 

#include <stdint.h>

#define DIO_INPUT 0
#define DIO_OUTPUT 1
#define DIO_PULLUP 2

#define HIGH 1
#define LOW 0

#define DIO_BITMASK(val, bit) (val<<bit)

#define __SFR_8(mem_addr) (volatile uint8_t *)(mem_addr)

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


void dio_SetDirection(volatile uint8_t* reg, uint8_t bit , int8_t direction);

inline void dio_SetBit(volatile uint8_t* reg, uint8_t bit, uint8_t val);

inline uint8_t dio_GetBit(volatile uint8_t* reg, uint8_t bit);

#endif 
