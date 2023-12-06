#include "lcd.h"

void lcd_Init ()	
{
  i2c_Init(I2C_FREQ_250K, false);

	_delay_ms(40);	
	
	lcd_Send(0x02, 0);		  /* send for 4 bit initialization of LCD  */
	lcd_Send(LCD_SETUP | LCD_4BIT | LCD_2LINE, 0);      /* 2 line, 5*7 matrix in 4-bit mode */
	lcd_Send(LCD_BACKLIGHT | LCD_NOCURSOR, 0);      /* Display on cursor off*/
	// lcd_Send(0x06, 0);      /* Increment cursor (shift cursor to right)*/
	// lcd_Send(0x01, 0);      /* Clear display screen*/
}


static void sendBits(uint8_t data){
  i2c_MasterTransmitByte(LCD_DEV_ADDR, data | LCD_EN);
  _delay_us(1);
  i2c_MasterTransmitByte(LCD_DEV_ADDR, data & ~LCD_EN);
  _delay_us(50);
}


void lcd_Send(uint8_t data, uint8_t mode)
{

  // i2c_MasterTransmitByte(LCD_DEV_ADDR, data & 0xF0 | mode);

  sendBits(data & 0xF0 | mode);

  // i2c_MasterTransmitByte(LCD_DEV_ADDR, (data << 4) | mode);
  sendBits((data << 4) | mode);
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
	lcd_Send (LCD_CLEAR, 0);		/* Clear display */
	lcd_Send (0x80, 0);		/* Cursor at home position */
}
