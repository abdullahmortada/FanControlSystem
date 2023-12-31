#ifndef __rtc__
#define __rtc__

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "helpers.h"
#include "i2c.h"

#define RTC_DEV_ADDR 0x68
#define RTC_CTRL 0x07
#define RTC_RAM 0x08

struct DateTime {
  uint8_t Minute;
  uint8_t Hour;
  uint8_t Day;
  uint8_t Month;
  uint8_t Year;
};

void rtc_Write(struct DateTime *dt);

void rtc_Now(struct DateTime *dh);

void rtc_dt2timestr(struct DateTime* dt, char* buf);
#endif
