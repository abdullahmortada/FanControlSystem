#include "eeprom.h"
#include "uart.h"
#include "util/delay.h"

int main(){

  uart_Init(9600);
  // uint8_t i = 0;

  char* str = "va";
  eeprom_WriteBytes(10, str);

  char buf[4];

  while(1){
    // eeprom_write(i, 'A'+i);
    // _delay_ms(500);
    // uart_Transmit(eeprom_read(i++));
    // _delay_ms(500);

    eeprom_ReadBytes(10, buf, sizeof(str));
    uart_SendString(buf);

    _delay_ms(1000);
  }
}
