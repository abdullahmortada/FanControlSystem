#ifndef __rtc__
#define __rtc__

#include <stdint.h>
#include <stdbool.h>
#include "i2c.h"

#define RTC_DEV_ADDR 0x68
#define RTC_CTRL 0x07
#define RTC_RAM 0x08

struct DateTime {
  uint16_t Year;
  uint8_t Month;
  uint8_t Day;
  uint8_t Hour;
  uint8_t Minute;
};

void rtc_Write(struct DateTime *dt);

void rtc_Now(struct DateTime *dh);

#endif
