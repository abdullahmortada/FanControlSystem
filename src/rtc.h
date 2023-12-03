#ifndef __rtc__
#define __rtc__

#include <stdint.h>

void rtc_write(char second, char minute,char hour);

void RTC_Read_Clock(char read_clock_address);

#endif