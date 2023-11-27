#include <avr/io.h>
#include "uart.h"

void uart_SetBaudRate(uint64_t baud){
  uint16_t ubrr = F_CPU/((baud*16UL) - 1); //baud rate formula
  UBRR0H = (ubrr >> 8); //4 msb
  UBRR0L = ubrr; //8 lsb
}


void uart_Init(uint64_t baud){
  uart_SetBaudRate(baud);

  UCSR0B |= (1 << RXEN0) | (1 << TXEN0); //enable uart transmit and receive
  UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); //set to 8-bit mode
}


void uart_Transmit(uint8_t data){
  //wait for data register
  do{} while ((UCSR0A & (1 << UDRE0)) == 0);

  UDR0 = data; //set data register 
}


void uart_SendString(char* String){
  //loop over all the characters and transmit them one by one
  int16_t i = 0;
  while(String[i]) uart_Transmit(String[i++]);
}


uint8_t uart_Receive(){
  //wait for data register
  while((UCSR0A & (1 << RXC0)) == 0);
  return UDR0; //return received data
}


void uart_EnableRXInterrupt(){UCSR0B |= (1 << RXCIE0);}
void uart_EnableTXInterrupt(){UCSR0B |= (1 << TXCIE0);}

