#include "lcd.h"

static void sendBits(uint8_t data){
  data |= LCD_BACKLIGHT;
  i2c_MasterTransmitByte((LCD_DEV_ADDR), data);
  //pulse en pin
  i2c_MasterTransmitByte((LCD_DEV_ADDR), data | LCD_EN);
  _delay_us(1);
  i2c_MasterTransmitByte((LCD_DEV_ADDR), data & ~LCD_EN);
  _delay_us(50);
}

void lcd_Init ()	
{
  i2c_Init(I2C_FREQ_100K, true);

	_delay_ms(50);

	// Now we pull both RS and R/W low to begin commands
  i2c_MasterTransmitByte(LCD_DEV_ADDR, LCD_BACKLIGHT);
	_delay_ms(1000);

	// we start in 8bit mode, try to set 4 bit mode
  sendBits(0x03 << 4);
	_delay_us(4500); // wait min 4.1ms

	// second try
  sendBits(0x03 << 4);
	_delay_us(4500); // wait min 4.1ms

	// third go!
  sendBits(0x03 << 4);
	_delay_us(4500); // wait min 4.1ms

	// finally, set to 4-bit interface
  sendBits(0x02 << 4);

	// set # lines, font size, etc.
	lcd_Send(LCD_SETUP | LCD_4BIT | LCD_2LINE | LCD_5X8DOTS, 0);

	// turn the display on with no cursor or blinking default
	lcd_Send(LCD_DISPLAYCTRL | LCD_DISPLAYON | LCD_NOCURSOR, 0);

	// clear it off
  lcd_Clear();

	// Initialize to default text direction (for roman languages)
	lcd_Send(LCD_ENTRY | LCD_ENTRY_LEFT | LCD_ENTRYSHIFTDECREMENT, 0);

  lcd_Send(LCD_HOME, 0);
}




void lcd_Send(uint8_t data, uint8_t mode)
{

  sendBits(data & 0xF0 | mode);
  _delay_ms(2);

  sendBits((data << 4) | mode);
  _delay_ms(2);
}


void lcd_String (char* str, uint8_t len)		
{
	int i;
	while(i < len && str[i])	lcd_Send(str[i++], 1);
}

void lcd_StringXY (char* str, uint8_t len, uint8_t row, uint8_t pos)	/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	  lcd_Send((pos & 0x0F)|0x80, 0);	

	else if (row == 1 && pos<16)
	  lcd_Send((pos & 0x0F)|0xC0, 0);	 
    
	lcd_String(str, len);
}

void lcd_Clear()
{
	lcd_Send (LCD_CLEAR, 0);		/* Clear display */
	lcd_Send (LCD_HOME, 0);		/* Cursor at home position */
}

