#ifndef _lcd_
#define _lcd_ 

#include "config.h"
#include "stdint.h"

void lcd_Send (uint8_t data, uint8_t toggleData);
void lcd_Init ();
void lcd_String (char *str);
void lcd_StringXY (char *str, uint8_t row, uint8_t pos);
void lcd_Clear();

#endif 
