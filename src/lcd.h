#ifndef _lcd_
#define _lcd_ 

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"

#define LCD_DEV_ADDR 0x3F
#define LCD_EN 0x04
#define LCD_RS 0x01

#define LCD_CMD_REG 0 
#define LCD_DATA_REG 1

#define LCD_SETUP 0x20
#define LCD_8BIT 0x10 
#define LCD_4BIT 0x00 
#define LCD_2LINE 0x08 
#define LCD_1LINE 0x00 

#define LCD_CLEAR 0x01 
#define LCD_BACKLIGHT 0x08 
#define LCD_NOBACKLIGHT 0x00 
#define LCD_CURSOR 0x02
#define LCD_NOCURSOR 0x00

void lcd_Init ();
void lcd_Send (uint8_t data, uint8_t toggleData);
void lcd_String (char *str);
void lcd_StringXY (char *str, uint8_t row, uint8_t pos);
void lcd_Clear();

#endif 
