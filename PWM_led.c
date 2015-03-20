/*
 * PWM_LED.c
 *
 * Created: 3/8/2015 6:39:49 PM
 *  Author: Auro
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int count;
int sw_pwm = 3;
int sw_pwm_max = 256;
int phase = 0;
int sw_pwm_en = 1;

int main(void)
{
	count = 0;
	DDRB  = 0b00001110;   // PB1, PB2, PB3 outputs
	DDRD  = 0b01111000;   // PD3, PD4, PD5, PD6 outputs

	if (sw_pwm_en == 0) {
		TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);      // Non inverting mode on OC0A and OC0B, Mode = Mode 3 FAST PWM
		//TCCR0B = _BV(CS00) | _BV(CS02);                                    // 1024 prescaling	
		TCCR0B = _BV(CS01) | _BV(CS00);                                    // 1024 prescaling	
	
		TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);				   // Non inverting mode on OC0A and OC0B, Mode = Mode 3 FAST PWM
		//TCCR1B = _BV(WGM10) | _BV(CS10) | _BV(CS12);                        // 1024 prescaling
		TCCR1B = _BV(WGM12) | _BV(CS11) | _BV(CS10);                        // 1024 prescaling
	
	    TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);      // Non inverting mode on OC2A, Mode = Mode 3 FAST PWM
		//TCCR2B = _BV(CS20) | _BV(CS21);                                    // 1024 prescaling
		TCCR2B = _BV(CS21) | _BV(CS20);                                    // 1024 prescaling
	
		OCR0A = 0;
		OCR0B = 0;
		OCR0A = 0;
		OCR0B = 0;
		OCR2A = 0;
		OCR2B = 0;	
	}
	
	PCICR = _BV(PCIE0);
	PCMSK0 = _BV(PCINT0);

	sei();
			
    while(1)
    {
        //TODO:: Please write your application code 
		if (count == 0) {
			PORTD = 0b00000000;
			PORTB &= 0b00000001;
			//DDRD |= 0b01000000;
			//OCR0A = 3;
			if (phase < sw_pwm) {
				PORTD |= 0b01000000;
				} else {
				PORTD &= 0b10111111;
			}
			phase = phase + 1;
			if (phase == sw_pwm_max) phase = 0;
	
		} else if (count == 1) {
			PORTD = 0b00000000;
			PORTB &= 0b00000001;
			//PORTD &= 0b10111111;
			//OCR0A = 0;
			//DDRD &= 0b10111111; 	
			//DDRD |= 0b00100000;
			//OCR0B = 3;
			if (phase < sw_pwm) {
				PORTD |= 0b00100000;
				} else {
				PORTD &= 0b11011111;
			}
			phase = phase + 1;
			if (phase == sw_pwm_max) phase = 0;
	
		} else if (count == 2) {
			PORTD = 0b00000000;
			PORTB &= 0b00000001;
			//PORTD &= 0b11011111;
			//OCR0B = 0	;
			//DDRD &= 0b11011111;
			//DDRB |= 0b00000010;
			//OCR1A = 3;
			if (phase < sw_pwm) {
				PORTB |= 0b00000010;
				} else {
				PORTB &= 0b11111101;
			}
			phase = phase + 1;
			if (phase == sw_pwm_max) phase = 0;

		} else if (count == 3) {
			PORTD = 0b00000000;
			PORTB &= 0b00000001;
			//PORTB &= 0b11111101;
			//OCR1A = 0;
			//DDRB &= 0b11111101;
			//DDRB |= 0b00000100;
			//OCR1B = 3;
			if (phase < sw_pwm) {
				PORTB |= 0b00000100;
				} else {
				PORTB &= 0b11111011;
			}
			phase = phase + 1;
			if (phase == sw_pwm_max) phase = 0;

		} else if (count == 4) {
			PORTD = 0b00000000;
			PORTB &= 0b00000001;
			//PORTB &= 0b11111011;
			//OCR1B = 0;
			//DDRB &= 0b11111011;
			//DDRB |= 0b00001000;
			//OCR2A = 3;
			if (phase < sw_pwm) {
				PORTB |= 0b00001000;
				} else {
				PORTB &= 0b11110111;
			}
			phase = phase + 1;
			if (phase == sw_pwm_max) phase = 0;

		} else if (count == 5) {
			PORTD = 0b00000000;
			PORTB &= 0b00000001;
			//PORTB &= 0b11110111;
			//OCR2A = 0;
			//DDRB &= 0b11110111;
			//DDRD |= 0b00001000;
			//OCR2B = 3;
			if (phase < sw_pwm) {
				PORTD |= 0b00001000;
				} else {
				PORTD &= 0b11110111;
			}
			phase = phase + 1;
			if (phase == sw_pwm_max) phase = 0;

		} else if (count == 6) {
			PORTD = 0b00000000;
			PORTB &= 0b00000001;
			//PORTD &= 0b11110111;
			//OCR2B = 0;
			//DDRD &= 0b11110111;
			// ENABLE SOFTWARE PWM
			if (phase < sw_pwm) {
				PORTD |= 0b00010000;
				} else {
				PORTD &= 0b11101111;
			}
			phase = phase + 1;
			if (phase == sw_pwm_max) phase = 0;
			
		} else if (count == 7) {
			//All LEDs off
			PORTD = 0b00000000;
			PORTB &= 0b00000001;		
		}
    }
}
 
ISR (PCINT0_vect)
{
	if ((PINB & (1 << PINB0)) == 1) //& (trigger == 1) )
	{
		/* LOW to HIGH pin change */
		phase = 0;
		if (count == 7) {
			count = 0;
		} else {
			count  = count + 1;
		}		
	}
	else
	{
		/* HIGH to LOW pin change */		
	}
	PORTB &= 0b00000001;
	PORTD = 0b00000000;
	_delay_ms(50);
}
