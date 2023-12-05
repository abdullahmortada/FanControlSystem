#include "rtc.h"

void rtc_write(uint8_t* data)
{
  i2c_MasterTransmit(RTC_DEV_ADDR, data, 4, 0);
}

void RTC_Read_Clock(uint8_t read_addr, uint8_t* second, uint8_t* minute, uint8_t* hour)
{
	i2c_Start();/* Start I2C communication with RTC */
	i2c_WriteSla(0xD0);	/* Write address to read */
	i2c_Write(read_addr);	/* Write address to read */
	i2c_RepStart(Device_Read_address);/* Repeated start with device read address */

	*second = i2c_Read(1);	
	*minute = i2c_Read(1);	
  *hour = i2c_Read(1);	
  i2c_Stop();			
}

