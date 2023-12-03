#include "CustomCharacters.h"
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lcd.h"

// LCD Custom Characters
const uint8_t CatChar[] PROGMEM = {
    0b00000,
    0b00110,
    0b01111,
    0b11110,
    0b11110,
    0b01111,
    0b00110,
    0b00000
};

const uint8_t SharkChar[] PROGMEM = {
    0b00100,
    0b01110,
    0b11111,
    0b10101,
    0b10101,
    0b11111,
    0b01110,
    0b00100
};

const uint8_t HeartChar[] PROGMEM = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000
};

const uint8_t FunnyManChar[] PROGMEM = {
    0b01110,
    0b11111,
    0b11011,
    0b10001,
    0b11111,
    0b01010,
    0b01010,
    0b11011
};

void customCharacters_Init() {
    lcd_Init();
}

void customCharacters_Display() {
    lcd_Clear();
    lcd_String("Custom Characters:");

    lcd_SetCursor(0, 1);
    lcd_WriteCustomChar(CatChar);
    lcd_SetCursor(2, 1);
    lcd_WriteCustomChar(SharkChar);
    lcd_SetCursor(4, 1);
    lcd_WriteCustomChar(HeartChar);
    lcd_SetCursor(6, 1);
    lcd_WriteCustomChar(FunnyManChar);
}
