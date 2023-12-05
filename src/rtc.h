#ifndef __rtc__
#define __rtc__

#include <stdint.h>
#include "i2c.h"

void rtc_Write(uint8_t second, uint8_t minute, uint8_t hour);

void rtc_Read( uint8_t read_clock_address);

#endif
