#include "rtc.h"

static inline uint8_t bcd2bin(uint8_t val) { return (val - 6 * (val / 16)); }
static inline uint8_t bin2bcd(uint8_t val) { return val + 6 * (val / 10); }

void rtc_Write(struct DateTime* dt)
{
  uint8_t buf[] = {
    0,
    0,
    bin2bcd(dt->Minute),
    bin2bcd(dt->Hour),
    0,
    bin2bcd(dt->Day),
    bin2bcd(dt->Month),
    bin2bcd(dt->Year)
  };
  i2c_MasterTransmit(RTC_DEV_ADDR, buf, 8, false);
}

void rtc_Now(struct DateTime* dt)
{
	i2c_Start();/* Start I2C communication with RTC */
	i2c_WriteSla(I2C_SLA_W(RTC_DEV_ADDR));	/* Write address to read */
	i2c_Write(0);	/* Write address to read */
	i2c_Start();/* Repeated start with device read address */
	i2c_WriteSla(I2C_SLA_R(RTC_DEV_ADDR));	/* Write address to read */

  i2c_Read(true);
  dt->Minute = bcd2bin(i2c_Read(true));
  dt->Hour = bcd2bin(i2c_Read(true));
  i2c_Read(true);
  dt->Day = bcd2bin(i2c_Read(true));
  dt->Month = bcd2bin(i2c_Read(true));
  dt->Year = bcd2bin(i2c_Read(false));

  i2c_Stop();			
}

void rtc_dt2timestr(struct DateTime* dt, char* buf){
  char temp[3];

  strcpy(buf, "");
  intToString(dt->Hour, temp, 10);
  strcat(buf, temp);
  strcat(buf, ":");
  intToString(dt->Minute, temp, 10);
  strcat(buf, temp);
}

