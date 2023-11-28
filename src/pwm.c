void Pwm_Init(){
  
  DDRD |= (1<<PD6);  

  TCCR0A |= (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);	//Non-Inverting Fast PWM mode 3 using OCR A unit
	TCCR0B |= (1<<CS00);	//No-Prescalar

  OCR0A = 191;	// Duty cycle of 75%

}

void Pwm_SetDutyCycle(unsigned char DutyCycle){
    OCR0A = DutyCycle;
}
