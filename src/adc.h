#ifndef __adc__
#define __adc__

#include <stdint.h>

void adc_Init();

uint16_t adc_ReadChannel(uint8_t channel);

#endif
