#ifndef __eeprom__
#define __eeprom__

#include <avr/io.h>
#include <stddef.h>
#include <stdint.h>
#include "sfrdef.h"


// #define EEAR __SFR_16(0x41)
// #define EEARL __SFR_8(0x41)
// #define EEARH __SFR_8(0x42)
//
// #define EEDR __SFR_8(0x40)
// #define EECR __SFR_8(0x3F)

#define EERE 0
#define EEPE 1 
#define EEMPE 2 
#define EEPM0 4
#define EEPM1 5

void eeprom_write(uint16_t address_u16, uint8_t data);

uint8_t eeprom_read(uint16_t address_u16);

void eeprom_WriteBytes(uint16_t address_u16, uint8_t* data);

void eeprom_ReadBytes(uint16_t address_u16, uint8_t* buf, uint16_t len);
#endif
