#include <avr/io.h>
#include <avr/interrupt.h>
#include <assert.h>
#include <util/delay.h>
#include "timer.h"
#include "uart.h"

uint8_t timer = 1;
uint8_t channel = 0;

ISR (TIMER1_COMPA_vect)    // Timer1 ISR
{
	PORTB ^= (1 << PB5);	
}

int main()
{
  uart_Init(9600);
	DDRB = (0x01 << PB5);     //Configure the PORTD4 as output
	

	// TCCR1B = (1<<CS10) | (1<<CS12) | (1 << WGM12);  // Timer mode with 1024 prescler
	// TIMSK1 = (1 << OCIE1A) ;   // Enable timer1 overflow interrupt(TOIE1)
 //  OCR1A = 15625;               // number of ticks in a second
  timerStart(0, TIMER_MODE_COUNT, 0, PRESCALER_1024, 15625);
  assert(TCCR1B & ((1<<CS10)| (1<<CS12) | (1 << WGM12)) == ((1<<CS10)| (1<<CS12) | (1 << WGM12)));
  // TCCR1B |= ((1<<CS10)| (1<<CS12) | (1 << WGM12)) ;
  PORTB |= 1<<PB5;
	sei();        // Enable global interrupts by setting global interrupt enable bit in SREG
	
	while(1)
	{
		
    _delay_ms(1000);
    uart_Transmit('a');
	}
}
