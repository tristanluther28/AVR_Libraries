//-----------------------------------------------------------------------------
//
//  PWM.c
//
//  Swallowtail PWM Firmware for ATmega328P
//  AVR (ATmega328P) PWM Firmware
//
//  Copyright (c) 2021 Swallowtail Electronics
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sub-license,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//
//  Web:    http://tristanluther.com
//  Email:  tristanluther28@gmail.com
//
//-----------------------------------------------------------------------------

/******************** Macros *****************************/


/******************** Includes ***************************/

#include <avr/io.h>

/******************* Globals *****************************/

//Add volatile keyword so the compiler won't optimize these variables out if only used in ISR

/******************** Functions **************************/

//Initialize the PWM Output
void PWM_init(){
	//Enable hardware outputs
	DDRB |= (1<<PB1) | (1<<PB2);
	DDRD |= (1<<PD5) | (1<<PD6);
	//Set the default values for outputs to zero and inputs to have pull-up resistors
	PORTB |= (0<<PB1) | (0<<PB2);
	PORTD |= (0<<PD5) | (0<<PD6);
	//Enable Timer 0
	//Enable PWM Output 0A and 0B and Fast PWM
	TCCR0A |= (1<<COM0A1) | (1<<COM0B1) | (1<<WGM01) | (1<<WGM00);
	//Enable Clock Divider/64
	TCCR0B |= (1<<CS01) | (1<<CS00);
	//Max PWM value possible set though OCR0A & OCR0B
	OCR0A = 0x00;
	OCR0B = 0x00;
	//Enable Timer 1
	//Enable PWM Output 1A and 1B and Fast PWM
	TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);
	//Enable Clock Divider/64
	TCCR1B = (1<<CS11) | (1<<CS10) | (1<<WGM12);
	//Max PWM value possible set though OCR1A & OCR1B
	OCR1A = 0x00;
	OCR1B = 0x00;
	return; //Return to call point
}

//Change timer 0 a value
void PWM_timer0_a(uint8_t value){
	OCR0A = value;
}

//Change timer 0 b value
void PWM_timer0_b(uint8_t value){
	OCR0B = value;
}

//Change timer 1 a value
void PWM_timer1_a(uint8_t value){
	OCR1A = value;
}

//Change timer 1 b value
void PWM_timer1_b(uint8_t value){
	OCR1B = value;
}
/******************** Interrupt Service Routines *********/
