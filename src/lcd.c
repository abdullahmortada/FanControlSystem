#include <avr/io.h>
#include <util/delay.h>	  
#include "lcd.h"

void lcd_Send(uint8_t data, uint8_t toggleData)
{
  // send upper nibble of data
	LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0); 
	RS_EN_Port = (RS_EN_Port & ~(1<<RS)) | (toggleData << RS);		

  // send pulse
	RS_EN_Port |= (1<<EN);
	_delay_us(1);
	RS_EN_Port &= ~ (1<<EN);

	_delay_us(200);

  // send lower nibble of data
	LCD_Port = (LCD_Port & 0x0F) | (data << 4); 

	RS_EN_Port |= (1<<EN);
	_delay_us(1);
	RS_EN_Port &= ~ (1<<EN);

  _delay_ms(2);

}


void lcd_Init ()	
{
	LCD_Dir |= 0xFF; 
  RS_EN_Dir |= (1 << EN) | (1 << RS);

	_delay_ms(20);	
	
	lcd_Send(0x02, 0);		  /* send for 4 bit initialization of LCD  */
	lcd_Send(0x28, 0);      /* 2 line, 5*7 matrix in 4-bit mode */
	lcd_Send(0x0c, 0);      /* Display on cursor off*/
	lcd_Send(0x06, 0);      /* Increment cursor (shift cursor to right)*/
	lcd_Send(0x01, 0);      /* Clear display screen*/
}

void lcd_String (char* str)		
{
	int i;
	while(str[i])	lcd_Send(str[i++], 1);
}

void lcd_StringXY (char* str, uint8_t row, uint8_t pos)	/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	  lcd_Send((pos & 0x0F)|0x80, 0);	

	else if (row == 1 && pos<16)
	  lcd_Send((pos & 0x0F)|0xC0, 0);	 
    
	lcd_String(str);
}

void lcd_Clear()
{
	lcd_Send (0x01, 0);		/* Clear display */
	lcd_Send (0x80, 0);		/* Cursor at home position */
}
