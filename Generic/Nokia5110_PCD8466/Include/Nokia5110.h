//-----------------------------------------------------------------------------
//
//  MCP2515.h
//
//  Swallowtail Nokia 5110/PCD8544 Firmware
//  AVR Nokia 5110/PCD8544 Firmware
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
#ifndef NOKIA5110_H_
#define NOKIA5110_H_

/******************* Function Declarations *******************/
void Nokia5110_Reset();
void Nokia5110_Clear();
void Nokia5110_Fill();
void Nokia5110_Command(char byte);
void Nokia5110_SetXY(char x, char y);
void Nokia5110_Invert();
void Nokia5110_Noninvert();
void Nokia5110_Data(char* data);
void Nokia5110_Image (const unsigned char *image_data);
void Nokia5110_init();
uint8_t MCP2515_CheckMessage(void);
void MCP2515_Reset();
void MCP2515_init();

#endif