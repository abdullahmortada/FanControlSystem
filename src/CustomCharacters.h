#ifndef _CUSTOM_CHARACTERS_H_
#define _CUSTOM_CHARACTERS_H_

#include <LiquidCrystal.h>

class CustomCharacters {
public:
    CustomCharacters(); // Constructor

    void setupLCD();
    void displayCustomCharacters();

private:
    LiquidCrystal MyLCD;

    // LCD Custom Characters
    uint8_t CatChar[8];
    uint8_t SharkChar[8];
    uint8_t HeartChar[8];
    uint8_t FunnyManChar[8];
};

#endif 
