#include"rtc.h"
#include <avr/io.h>
#include "I2C.h"

void rtc_write(char second, char minute,char hour)
{
    I2C_start(0xD0);//device address in the i2c
    I2C_write(0); //(00)
    I2C_write(_second);//loction gets auto incremented (01)
    I2C_write(_minute);//(02)
    I2C_stop()

}
void RTC_Read_Clock(char read_clock_address)
{
	I2C_Start(0xD0);/* Start I2C communication with RTC */
	I2C_Write(read_clock_address);	/* Write address to read */
	I2C_Repeated_Start(Device_Read_address);/* Repeated start with device read address */

	second = I2C_Read_Ack();	
	minute = I2C_Read_Ack();	
	hour = I2C_Read_Nack();		
	I2C_Stop();			
}

