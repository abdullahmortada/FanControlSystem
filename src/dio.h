#ifndef _dio_ 
#define _dio_ 

#include <stdint.h>

#define DIO_INPUT 0
#define DIO_OUTPUT 1
#define DIO_PULLUP 2

#define HIGH 1
#define LOW 0


#define PORTB (volatile uint8_t *)0x25
#define PORTC (volatile uint8_t *)0x28
#define PORTD (volatile uint8_t *)0x2B

#define DDRB (volatile uint8_t *)0x24
#define DDRC (volatile uint8_t *)0x27
#define DDRD (volatile uint8_t *)0x2A

#define PINB (volatile uint8_t *)0x23
#define PINC (volatile uint8_t *)0x26
#define PIND (volatile uint8_t *)0x29

#define PCICR (volatile uint8_t *)0x68
#define PCMSK0 (volatile uint8_t *)0x6B
#define PCMSK1 (volatile uint8_t *)0x6C
#define PCMSK2 (volatile uint8_t *)0x6D


#define DIO_BITMASK(val, bit) (val<<bit)


void dio_SetDirection(volatile uint8_t* reg, uint8_t bit , int8_t direction);

inline void dio_SetBit(volatile uint8_t* reg, uint8_t bit, uint8_t val);

inline uint8_t dio_GetBit(volatile uint8_t* reg, uint8_t bit);

#endif 
