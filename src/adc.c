#include <avr/io.h>
#include "adc.h"

void adc_Init()
{
    ADMUX = (1<<REFS0);
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t adc_ReadChannel(uint8_t ch)
{

  ADMUX = (ADMUX & 0xF8)|(ch & 0x07); // clears the bottom 3 bits before ORing
 
  // start adc convertion
  ADCSRA |= (1<<ADSC);
 
  // wait for conversion to complete
  while(ADCSRA & (1<<ADSC));
 
  return (ADC);
}
