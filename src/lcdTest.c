#include <avr/io.h>
#include <assert.h>
#include <util/delay.h>
#include "lcd.h"
#include "uart.h"

int main() {
    uart_Init(9600);
    lcd_Init();
    // lcd_Send(LCD_BACKLIGHT, 0);
    // _delay_ms(3000);
    // lcd_Send(LCD_CLEAR, 0);
    lcd_Send('a', 1);
    _delay_ms(3000);

    while (1) {
      char testString[] = "LCD Test";
      lcd_Clear();
      lcd_String(testString);
      _delay_ms(2000);

      lcd_Clear();
      char testString2[] = "Position Test";
      lcd_StringXY(testString2, 1, 5);
      _delay_ms(2000);
    }

    return 0;
}
