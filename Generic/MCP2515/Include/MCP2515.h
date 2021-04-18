//-----------------------------------------------------------------------------
//
//  MCP2515.h
//
//  Swallowtail MCP2515 Firmware
//  AVR MCP2515 Firmware
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
#ifndef MCP2515_H_
#define MCP2515_H_

/******************* Function Declarations *******************/
void MCP2515_Write(uint8_t address, uint8_t data);
uint8_t MCP2515_Read(uint8_t address);
void MCP2515_BitModify(uint8_t address, uint8_t mask, uint8_t data);
uint8_t MCP2515_Send(CANPacket *packet);
uint8_t MCP2515_Get(CANPacket *message);
void MCP2515_Loopback();
void MCP2515_Sleep();
void MCP2515_ListenOnly();
void MCP2515_Normal();
uint8_t MCP2515_SetBaud(long clockFreq, long baud);
uint8_t MCP2515_CheckMessage(void);
void MCP2515_Reset();
void MCP2515_init();

#endif