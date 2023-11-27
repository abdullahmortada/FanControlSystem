#ifndef _uart_
#define _uart_

#include <stdint.h>

#define UART_RX_INTERRUPT USART_RX_vect
#define UART_TX_INTERRUPT USART_TX_vect

void uart_SetBaudRate(uint64_t baud);

void uart_Init(uint64_t baud);

void uart_Transmit(uint8_t data);

void uart_SendString(char * String);

uint8_t uart_Receive(void);

void uart_EnableRXInterrupt();
void uart_EnableTXInterrupt();
#endif
