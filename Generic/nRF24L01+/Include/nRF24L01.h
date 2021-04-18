//-----------------------------------------------------------------------------
//
//  nRF24L01.h
//
//  Swallowtail nRF24L01+ Firmware
//  AVR nRF24L01+ Firmware
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

/******************** Include Guard **************************/
#ifndef NRF24L01_H_
#define NRF24L01_H_

/******************* Function Declarations *******************/
void nRF24L01_Enable();
void nRF24L01_Disable();
uint8_t *nRF24L01_Transfer(uint8_t rwt, uint8_t reg, uint8_t *buffer, uint8_t length);
void nRF24L01_Reset();
uint8_t nRF24L01_ReadRegister(uint8_t reg);
void nRF24L01_init(uint8_t mode, uint8_t *RX_Address, uint8_t *TX_Address);
void nRF24L01_Transmit(uint8_t *buffer);
uint8_t *nRF24L01_Recieve();

#endif