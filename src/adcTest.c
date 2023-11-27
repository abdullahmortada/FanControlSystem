#include <assert.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/io.h>
#include "adc.h"
#include "uart.h"


int main(){

  uart_Init(9600);
  adc_Init();
  // assert(ADMUX & (1<<REFS0) !=0);
  uart_SendString("REFS0 is correct\n");
  assert(ADCSRA & (1<<ADEN) !=0 );
  uart_SendString("ADEN is correct\n");
  assert(ADCSRA & (1<<ADPS2) !=0 );
  uart_SendString("ADPS2 is correct\n");
  assert(ADCSRA & (1<<ADPS1) !=0 );
  uart_SendString("ADPS1 is correct\n");
  assert(ADCSRA & (1<<ADPS0) !=0 );
  uart_SendString("ADPS0 is correct\n");

  char str[6];

  while (1){
    itoa(adc_ReadChannel(0), str, 10);
    uart_SendString(str);
    uart_Transmit('\n');
    
    _delay_ms(400);
  }
}
