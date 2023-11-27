#include <avr/io.h>
#include <assert.h>
#include <util/delay.h>
#include "lcd.h"
#include "uart.h"

int main() {
    uart_Init(9600);
    lcd_Init();
    assert(RS_EN_Dir & (1 << RS) != 0);
    uart_SendString("RS and EN pins are set correctly for LCD initialization\n");

    DDRD |= 1<<PD3;
    PORTD |= 1<<PD3;

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
