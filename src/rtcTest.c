#include "i2c.h"
#include "rtc.h"
#include "uart.h"
#include <util/delay.h>

int main (){

  uart_Init(9600);
  i2c_Init(I2C_FREQ_100K, false);

  // struct DateTime dt = {36, 3, 15, 10, 15};
  // rtc_Write(&dt);

  struct DateTime d; 
  char string [8];

  while(1){
    rtc_Now(&d);
    rtc_dt2timestr(&d, string);
    uart_SendString(string);
    uart_Transmit('\n');
    _delay_ms(2000);

  }
  while(1){

  }
}
