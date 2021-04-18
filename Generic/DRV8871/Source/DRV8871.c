//-----------------------------------------------------------------------------
//
//  DRV8871.h
//
//  Swallowtail DRV8871 Firmware
//  DRV8871.h Firmware to capture the logic to interface with this chip
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
#include "PWM.h"

/******************* Globals *****************************/

//Add volatile keyword so the compiler won't optimize these variables out if only used in ISR

/******************** Functions **************************/

//Function for setting up the driver input and outputs
void DRV8871_init(){
	PWM_init();
	return; //Go back to previous location
}

//Sets a new continuous PWM duty cycle that regulates the speed going forward on this motor
void DRV8871_move(uint8_t speed, uint8_t direction, uint8_t right){
	if(right){
		//Move the right motor
		if(direction){
			//Move the right motor forward
			PWM_timer1_a(0);
			PWM_timer1_b(speed);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
		}
		else{
			//Move the right motor backwards
			PWM_timer1_a(speed);
			PWM_timer1_b(0);
		}
	}
	else{
		//Move the left motor
		if(direction){
			//Move the left motor forward
			PWM_timer0_a(0);
			PWM_timer0_b(speed);
		}
		else{
			//Move the left motor backwards
			PWM_timer0_a(speed);
			PWM_timer0_b(0);
		}
	}
	return; //Go back to previous location
}

//Sets a new continuous PWM duty cycle that regulates the speed going backward on this motor
void DRV8871_backward(uint8_t speed){
	DRV8871_move(speed, 0, 0);
	DRV8871_move(speed, 0, 1);
	return; //Go back to previous location
}

//Sets a new continuous PWM duty cycle that regulates the speed going forward on this motor
void DRV8871_forward(uint8_t speed){
	DRV8871_move(speed, 1, 0);
	DRV8871_move(speed, 1, 1);
	return; //Go back to previous location
}

//Sets a new continuous PWM duty cycle that move the system to the right
void DRV8871_right(uint8_t speed){
	DRV8871_move(speed, 1, 0);
	DRV8871_move(speed, 0, 1);
	return; //Go back to previous location
}

//Sets a new continuous PWM duty cycle that move the system to the left
void DRV8871_left(uint8_t speed){
	DRV8871_move(speed, 0, 0);
	DRV8871_move(speed, 1, 1);
	return; //Go back to previous location
}

//Stops the PWM duty cycle that regulates the speed
void DRV8871_stop(){
	PWM_timer0_a(0x00);
	PWM_timer0_b(0x00);
	PWM_timer1_a(0x00);
	PWM_timer1_b(0x00);
	return; //Go back to previous location
}

/******************** Interrupt Service Routines *********/
