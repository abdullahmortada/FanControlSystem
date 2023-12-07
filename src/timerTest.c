// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include <assert.h>
// #include <util/delay.h>
// #include "timer.h"
// #include "uart.h"

// uint8_t timer = 1;
// uint8_t channel = 0;
//
// ISR (TIMER1_COMPA_vect)    // Timer1 ISR
// {
//   PORTB ^= 1<<5;
// }
//
// int main()
// {
//   uart_Init(9600);
// 	DDRB = (0x01 << PB5);     //Configure the PORTD4 as output
// 	
//
// 	// TCCR1B = (1<<CS10) | (1<<CS12) | (1 << WGM12);  // Timer mode with 1024 prescler
// 	// TIMSK1 = (1 << OCIE1A) ;   // Enable timer1 overflow interrupt(TOIE1)
//  //  OCR1A = 15625;               // number of ticks in a second
//
//   uint16_t count = F_CPU / 1024;
//   timerStart(timer, TIMER_MODE_COUNT, channel, PRESCALER_1024, count);
//   // assert((TCCR1B & (1<<CS10) | (1<<CS12) | (1 << WGM12)) == ((1<<CS10) | (1<<CS12) | (1 << WGM12)));
//   assert((TIMSK1 & (1 << OCIE1A)) == 2);
//   PORTB |= 1<<5;
// 	sei();        // Enable global interrupts by setting global interrupt enable bit in SREG
// 	
// 	while(1)
// 	{
// 		
//     _delay_ms(1000);
//     uart_Transmit('a');
// 	}
// }
//

#include "pwm.h"
#include "dio.h"
#include "util/delay.h"

int main(){
  DDRD |= 1 << 6 | 1<<7 | 1<<5;
    dio_SetBit(&PORTD, 7, 1);
  while(1){
    for (int i = 100; i < 255; i = i + 20){
    pwm_DutyCycle(PWM_PD6, i);
    _delay_ms(1000);
    }
    for (int i = 255; i > 100; i = i - 20){
    pwm_DutyCycle(PWM_PD6, i);
    _delay_ms(1000);
    }

    // dio_SetBit(DDRD, 7, 1);
    // pwm_DutyCycle(PWM_PD6, 100);
    // _delay_ms(4000);
    // pwm_DutyCycle(PWM_PD6, 150);
    // _delay_ms(4000);
    // pwm_DutyCycle(PWM_PD6, 200);
    // _delay_ms(4000);
    // pwm_DutyCycle(PWM_PD6, 255);
    // _delay_ms(4000);

    // pwm_DutyCycle(PWM_PD6, 0);
    // dio_SetBit(DDRD, 5, 1);
    // _delay_ms(1000);
    // pwm_DutyCycle(PWM_PD6, 75);
    // _delay_ms(1000);
    // pwm_DutyCycle(PWM_PD6, 130);
    // _delay_ms(1000);
    // pwm_DutyCycle(PWM_PD6, 200);
    // _delay_ms(1000);
  }
}
