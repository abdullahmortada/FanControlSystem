#ifndef CUSTOM_CHARACTERS_H
#define CUSTOM_CHARACTERS_H

#include <stdint.h>
#include <avr/pgmspace.h>


extern uint8_t CatChar[] PROGMEM = {
    0b00000,
    0b00110,
    0b01111,
    0b11110,
    0b11110,
    0b01111,
    0b00110,
    0b00000
};

extern uint8_t SharkChar[] PROGMEM = {
    0b00100,
    0b01110,
    0b11111,
    0b10101,
    0b10101,
    0b11111,
    0b01110,
    0b00100
};

extern uint8_t HeartChar[] PROGMEM = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000
};

extern uint8_t FunnyManChar[] PROGMEM = {
    0b01110,
    0b11111,
    0b11011,
    0b10001,
    0b11111,
    0b01010,
    0b01010,
    0b11011
};
#endif 
