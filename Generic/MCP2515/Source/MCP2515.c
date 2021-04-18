//-----------------------------------------------------------------------------
//
//  MCP2515.c
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

/******************** Macros *****************************/

/* CAN Controller Register Map */
/* Receiver Related */
// Receiver Acceptance Filters (0 & 1 apply to Mask 0/Buffer 0) (2, 3, 4 & 5 apply to Mask 1/Buffer 1) 
#define RXF0SIDH 0x00
#define RXF0SIDL 0x01
#define RXF0EID8 0x02
#define RXF0EID0 0x03
#define RXF1SIDH 0x04
#define RXF1SIDL 0x05
#define RXF1EID8 0x06
#define RXF1EID0 0x07
#define RXF2SIDH 0x08
#define RXF2SIDL 0x09
#define RXF2EID8 0x0A
#define RXF2EID0 0x0B
#define RXF3SIDH 0x10
#define RXF3SIDL 0x11
#define RXF3EID8 0x12
#define RXF3EID0 0x13
#define RXF4SIDH 0x14
#define RXF4SIDL 0x15
#define RXF4EID8 0x16
#define RXF4EID0 0x17
#define RXF5SIDH 0x18
#define RXF5SIDL 0x19
#define RXF5EID8 0x1A
#define RXF5EID0 0x1B
// Receiver Masks (Mask 0 applies to Buffer 0) (Mask 1 applies to Buffer 1)
#define RXM0SIDH 0x20
#define RXM0SIDL 0x21
#define RXM0EID8 0x22
#define RXM0EID0 0x23
#define RXM1SIDH 0x24
#define RXM1SIDL 0x25
#define RXM1EID8 0x26
#define RXM1EID0 0x27
// Receiver Buffers (0, 1)
// RX Buffer 0
#define RXB0CTRL 0x60
#define RXB0SIDH 0x61
#define RXB0SIDL 0x62
#define RXB0EID8 0x63
#define RXB0EID0 0x64
#define RXB0DLC 0x65
#define RXB0D0 0x66
#define RXB0D1 0x67
#define RXB0D2 0x68
#define RXB0D3 0x69
#define RXB0D4 0x6A
#define RXB0D5 0x6B
#define RXB0D6 0x6C
#define RXB0D7 0x6D
// RX Buffer 1
#define RXB1CTRL 0x70
#define RXB1SIDH 0x71
#define RXB1SIDL 0x72
#define RXB1EID8 0x73
#define RXB1EID0 0x74
#define RXB1DLC 0x75
#define RXB1D0 0x76
#define RXB1D1 0x77
#define RXB1D2 0x78
#define RXB1D3 0x79
#define RXB1D4 0x7A
#define RXB1D5 0x7B
#define RXB1D6 0x7C
#define RXB1D7 0x7D
// RXBnCTRL Bit Registers
#define RXM1 0x06
#define RXM0 0x05
#define RXRTR 0x03
#define BUKT 0x02
#define BUKT1 0x01
#define FILHIT0 0x00
#define FILHIT2 0x02
#define FILHIT1 0x01
// RXnBF Interrupt Pin Control and Status Register
#define BFPCTRL 0x0C
// BFPCTRL Bit Registers
#define B1BFS 0x05
#define B0BFS 0x04
#define B1BFE 0x03
#define B0BFE 0x02
#define B1BFM 0x01
#define B0BFM 0x00
// Receive Error Counter
#define REC 0x1D
/* Transmitter Related */
// Transmitter Buffers (0, 1, 2)
//TX Buffer 0
#define TXB0CTRL 0x30
#define TXB0SIDH 0x31
#define TXB0SIDL 0x32
#define TXB0EID8 0x33
#define TXB0EID0 0x34
#define TXB0DLC 0x35
#define TXB0D0 0x36
#define TXB0D1 0x37
#define TXB0D2 0x38
#define TXB0D3 0x39
#define TXB0D4 0x3A
#define TXB0D5 0x3B
#define TXB0D6 0x3C
#define TXB0D7 0x3D
//TX Buffer 1
#define TXB1CTRL 0x40
#define TXB1SIDH 0x41
#define TXB1SIDL 0x42
#define TXB1EID8 0x43
#define TXB1EID0 0x44
#define TXB1DLC 0x45
#define TXB1D0 0x46
#define TXB1D1 0x47
#define TXB1D2 0x48
#define TXB1D3 0x49
#define TXB1D4 0x4A
#define TXB1D5 0x4B
#define TXB1D6 0x4C
#define TXB1D7 0x4D
//TX Buffer 2
#define TXB2CTRL 0x50
#define TXB2SIDH 0x51
#define TXB2SIDL 0x52
#define TXB2EID8 0x53
#define TXB2EID0 0x54
#define TXB2DLC 0x55
#define TXB2D0 0x56
#define TXB2D1 0x57
#define TXB2D2 0x58
#define TXB2D3 0x59
#define TXB2D4 0x5A
#define TXB2D5 0x5B
#define TXB2D6 0x5C
#define TXB2D7 0x5D
// TXBnCTRL Bit Registers
#define ABTF 0x06
#define MLOA 0x05
#define TXERR 0x04
#define TXREQ 0x03
#define TXP1 0x01
#define TXP0 0x00
// TXnRTS Interrupt Pin Control and Status Register
#define TXRTSCTRL 0x0D
// TXRTSCRTL Bit Registers
#define B2RTS 0x05
#define B1RTS 0x04
#define B0RTS 0x03
#define B2RTSM 0x02
#define B1RTSM 0x01
#define B0RTSM 0x00
// Transmit Error Counter
#define TEC 0x1C
/* Configuration Related */
// Configuration Registers
#define CNF1 0x2A
// CNF1 Bit Registers
#define SJW1 0x07
#define SJW0 0x06
#define BRP5 0x05
#define BRP4 0x04
#define BRP3 0x03
#define BRP2 0x02
#define BRP1 0x01
#define BRP0 0x00 
#define CNF2 0x29
// CNF2 Bit Registers
#define BTLMODE 0x07
#define SAM 0x06
#define PHSEG12 0x05
#define PHSEG11 0x04
#define PHSEG10 0x03
#define PRSEG2 0x02
#define PRSEG1 0x01
#define PRSEG0 0x00
#define CNF3 0x28
// CNF3 Bit Registers
#define SOF 0x07
#define WAKFIL 0x06
#define PHSEG22 0x02
#define PHSEG21 0x01
#define PHSEG20 0x00
#define CANCTRL 0x0F
// CANCTRL Bit Registers
#define REQOP2 0x07
#define REQOP1 0x06
#define REQOP0 0x05
#define ABAT 0x04
#define OSM 0x03
#define CLKEN 0x02
#define CLKPRE1 0x01
#define CLKPRE0 0x00
#define CANINTE 0x2B
// CANINTE Bit Registers
#define MERRE 0x07
#define WAKIE 0x06
#define ERRIE 0x05
#define TX2IE 0x04
#define TX1IE 0x03
#define TX0IE 0x02
#define RX1IE 0x01
#define RX0IE 0x00
#define CANINTF 0x2C
// CANINTF Bit Registers
#define MERRF 0x07
#define WAKIF 0x06
#define ERRIF 0x05
#define TX2IF 0x04
#define TX1IF 0x03
#define TX0IF 0x02
#define RX1IF 0x01
#define RX0IF 0x00
#define EFLG 0x2D
// EFLG Bit Registers
#define RX1OVR 0x07
#define RX0OVR 0x06
#define TXBO 0x05
#define TXEP 0x04
#define RXEP 0x03
#define TXWAR 0x02
#define RXWAR 0x01
#define EWARN 0x00
#define CANSTAT 0x0E
// CANSTAT Bit Registers
#define OPMOD2 0x07
#define OPMOD1 0x06
#define OPMOD0 0x05
#define ICOD2 0x03
#define ICOD1 0x02
#define ICOD0 0x01

// Instruction Set Commands
#define RESET 0xC0
#define READ 0x03
#define READ_RX_BUFFER 0x90
#define WRITE 0x02
#define LOAD_TX_BUFFER 0x40
#define RTS_TX 0x80
#define RTS_B0 0x81 //Request Message Buffer TXB0 to send
#define RTS_B1 0x82 //Request Message Buffer TXB1 to send
#define RTS_B2 0x84 //Request Message Buffer TXB2 to send
#define READ_STATUS 0xA0
#define RX_STATUS 0xB0
#define BIT_MODIFY 0x05

//Physical Pin Definitions
#define INT PB0
#define DDR_MCP2515 DDRB
#define PORT_MCP2515 PORTB
#define PIN_MCP2515 PINB

/******************** Includes ***************************/
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stddef.h>
#include <string.h>
#include "SPI.h"

/******************* Globals/Type Def *****************************/

//CAN packet used to package data
typedef struct CANPacket
{
	uint16_t id;
	uint8_t rtr : 1;
	uint8_t length : 4;
	uint8_t data[8];
} CANPacket;

/******************** Functions **************************/
//Write a single command
void MCP2515_Write(uint8_t address, uint8_t data){
	//Enable the SPI Line
	SPI_Enable();
	//Send the instruction
	SPI_Transfer(WRITE);
	//Send the address to write to
	SPI_Transfer(address);
	//Send the data
	SPI_Transfer(data);
	//Disable the SPI Line
	SPI_Disable();
}

//Read the value from an address
uint8_t MCP2515_Read(uint8_t address){
	//Enable the SPI Line
	SPI_Enable();
	//Send the instruction
	SPI_Transfer(READ);
	//Send the address to write to
	SPI_Transfer(address);
	//Get the data
	uint8_t data = SPI_Transfer(0xFF);
	//Disable the SPI Line
	SPI_Disable();
	//Return the data
	return data;
}

//Modifies a particular bit in a byte for a given address (Only applies to specific registers: See Datasheet)
void MCP2515_BitModify(uint8_t address, uint8_t mask, uint8_t data){
	//Enable the SPI Line
	SPI_Enable();
	//Send the instruction
	SPI_Transfer(BIT_MODIFY);
	//Send the address to write to
	SPI_Transfer(address);
	//Send the Masking Byte & Data
	SPI_Transfer(mask);
	SPI_Transfer(data);
	//Disable the SPI Line
	SPI_Disable();
}

//Sends Request to Transmit to Transmit on the given buffer
uint8_t MCP2515_Send(CANPacket *packet){
	//Get the status of the currently available TX buffers
	uint8_t tx_status = MCP2515_Read(READ_STATUS);
	uint8_t tx_buffer = 0x00;
	//Check to see which TX Buffer is available
	if(!(tx_status & (1<<2))){
		tx_buffer = 0x00;
	}
	else if(!(tx_status & (1<<4))){
		tx_buffer = 0x02;
	}
	else if(!(tx_status & (1<<6))){
		tx_buffer = 0x04;
	}
	else{
		//All the buffers are in use/cannot send the message/Unlikely
		return 0;
	}
	//Enable the SPI Line
	SPI_Enable();
	//Write to transmitter
	SPI_Transfer(LOAD_TX_BUFFER | tx_buffer);
	//Send the packet ID
	SPI_Transfer(packet->id >> 3);
	SPI_Transfer(packet->id << 5);
	//Skip the extended ID block
	SPI_Transfer(0x00);
	SPI_Transfer(0x00);
	uint8_t dlc = packet->length & 0x0F;
	//If the frame is RTR
	if(packet->rtr){
		SPI_Transfer((1<<6) | dlc); //No data
	}
	//Not an RTR data frame
	else{
		//Set the message length
		SPI_Transfer(dlc);
		//Add the data to the buffer
		int i;
		for(i = 0; i < dlc; i++){
			SPI_Transfer(packet->data[i]);
		}
	}
	//Disable the SPI Line
	SPI_Disable();
	//Let the transistors rest
	_delay_us(2);
	//Send the message from the selected buffer
	tx_buffer = (tx_buffer == 0) ? 1 : tx_buffer;
	SPI_Enable();
	SPI_Transfer(RTS_TX | tx_buffer);
	SPI_Disable();
	return tx_buffer;
}

//Gets the contents of a the message buffer
uint8_t MCP2515_Get(CANPacket *message){
	//Get the status of the currently filled RX Buffers
	uint8_t rx_status = MCP2515_Read(RX_STATUS);
	uint8_t rx_buffer = 0;
	//Check to see which RX Buffer is available
	if(!(rx_status & (1<<6))){
		//Buffer 0 has contents
		rx_buffer = READ_RX_BUFFER;
	}
	else if(!(rx_status & (1<<7))){
		//Buffer 1 has contents
		rx_buffer = READ_RX_BUFFER | 0x04;
	}
	else{
		//No messages enqueue
		return 0;
	}
	//Enable the SPI Line
	SPI_Enable();
	
	//Transfer the buffer pointer address for the buffer contents
	SPI_Transfer(rx_buffer);
	
	//Read the ID
	message->id = (uint16_t) SPI_Transfer(0xFF) << 3;
	message->id |= SPI_Transfer(0xFF) >> 5;
	
	//Skip Extended ID Block
	SPI_Transfer(0xFF);
	SPI_Transfer(0xFF);
	
	//Read the data length code
	uint8_t dlc = SPI_Transfer(0xFF) & 0x0F;
	message->length = dlc;
	//Check if this is an RTR frame
	message->rtr = (!(rx_status & (1<<3))) ? 1 : 0;
	
	//Read the Data
	uint8_t i;
	for(i = 0; i < dlc; i++){
		message->data[i] = SPI_Transfer(0xFF);
	}
	
	//Disable the SPI Line
	SPI_Disable();
	
	//Clear the General Purpose Interrupt Flag
	if(!(rx_status & (1<<6))){
		//Buffer 0 has contents/Clear the bit
		MCP2515_BitModify(CANINTF, (1<<RX0IF), 0);
	}
	else{
		//Buffer 1 has contents/Clear the bit
		MCP2515_BitModify(CANINTF, (1<<RX1IF), 0);
	}
	return (rx_status & 0x07) + 1;
}

//Puts the MCP2515 into loopback mode (for debugging)
void MCP2515_Loopback(){
	MCP2515_Write(CANCTRL, 0x40);
	//MCP2515_BitModify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0x02);
	return;
}

//Puts the MCP2515 into sleep mode
void MCP2515_Sleep(){
	MCP2515_BitModify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0x01);
	return;
}

//Puts the MCP2515 into Listen-Only mode
void MCP2515_ListenOnly(){
	MCP2515_BitModify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0x03);
	return;
}

//Puts the MCP2515 into Normal mode
void MCP2515_Normal(){
	MCP2515_BitModify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0x00);
	return;
}

//Set the baud rate of the CAN Comms
/*
Clock Rate | Bus Speed | Baud Rate Pre-scaler |	Prop Seg. | Phase Seg. 1 | Phase Seg. 2 | SJW
   8MHz	   | 1000Kb/s  |          1	          |     1	  |       1      |	     1	    |  1
   8MHz	   |  500Kb/s  |          1	          |     2	  |       3	     |       2	    |  1
   8MHz	   |  250Kb/s  |          1	          |     6	  |       5	     |       4	    |  3
   8MHz	   |  200Kb/s  |          1	          |     7	  |       7	     |       5	    |  3
   8MHz	   |  125Kb/s  |          2	          |     6	  |       5	     |       4	    |  3
   8MHz	   |  100Kb/s  |          2	          |     7	  |       7	     |       5	    |  3
   8MHz	   |   80Kb/s  |          5	          |     4	  |       3	     |       2	    |  1
   8MHz	   |   50Kb/s  |          5	          |     6	  |       5	     |       4	    |  3
   8MHz	   |   40Kb/s  |          5	          |     7	  |       7	     |       5	    |  3
   8MHz	   | 33.3Kb/s  |          6	          |     7	  |       7	     |       5	    |  3
   8MHz	   |31.25Kb/s  |          8	          |     6	  |       5	     |       4	    |  3
   8MHz	   |   20Kb/s  |         10	          |     7	  |       7	     |       5	    |  3
   8MHz	   |   10Kb/s  |         19	          |     7	  |       7	     |       5	    |  3
   8MHz	   |    5Kb/s  |         39	          |     7	  |       7	     |       5	    |  3
*/
uint8_t MCP2515_SetBaud(long clockFreq, long baud){
	const struct {
		long _clockFreq;
		long _baud;
		uint8_t _cnf[3];
	} CNF_MAP[] = {
		{  (long)8E6, (long)1000E3, { 0x00, 0x80, 0x00 } },
		{  (long)8E6,  (long)500E3, { 0x00, 0x90, 0x02 } },
		{  (long)8E6,  (long)250E3, { 0x00, 0xb1, 0x05 } },
		{  (long)8E6,  (long)200E3, { 0x00, 0xb4, 0x06 } },
		{  (long)8E6,  (long)125E3, { 0x01, 0xb1, 0x05 } },
		{  (long)8E6,  (long)100E3, { 0x01, 0xb4, 0x06 } },
		{  (long)8E6,   (long)80E3, { 0x01, 0xbf, 0x07 } },
		{  (long)8E6,   (long)50E3, { 0x03, 0xb4, 0x06 } },
		{  (long)8E6,   (long)40E3, { 0x03, 0xbf, 0x07 } },
		{  (long)8E6,   (long)20E3, { 0x07, 0xbf, 0x07 } },
		{  (long)8E6,   (long)10E3, { 0x0f, 0xbf, 0x07 } },
		{  (long)8E6,    (long)5E3, { 0x1f, 0xbf, 0x07 } },

		{ (long)16E6, (long)1000E3, { 0x00, 0xd0, 0x82 } },
		{ (long)16E6,  (long)500E3, { 0x00, 0xf0, 0x86 } },
		{ (long)16E6,  (long)250E3, { 0x41, 0xf1, 0x85 } },
		{ (long)16E6,  (long)200E3, { 0x01, 0xfa, 0x87 } },
		{ (long)16E6,  (long)125E3, { 0x03, 0xf0, 0x86 } },
		{ (long)16E6,  (long)100E3, { 0x03, 0xfa, 0x87 } },
		{ (long)16E6,   (long)80E3, { 0x03, 0xff, 0x87 } },
		{ (long)16E6,   (long)50E3, { 0x07, 0xfa, 0x87 } },
		{ (long)16E6,   (long)40E3, { 0x07, 0xff, 0x87 } },
		{ (long)16E6,   (long)20E3, { 0x0f, 0xff, 0x87 } },
		{ (long)16E6,   (long)10E3, { 0x1f, 0xff, 0x87 } },
		{ (long)16E6,    (long)5E3, { 0x3f, 0xff, 0x87 } },
	};
	uint8_t cnf[3];
	//Find the appropriate settings and place them in the cnf buffer to be written out
	for (uint8_t i = 0; i < (sizeof(CNF_MAP) / sizeof(CNF_MAP[0])); i++) {
		if (CNF_MAP[i]._clockFreq == clockFreq && CNF_MAP[i]._baud == baud) {
			strcpy((char *)cnf, (char *)CNF_MAP[i]._cnf);
			break;
		}
	}
	//If no cnf grouping was chosen then return with fail
	if(cnf == NULL){
		return 0;
	}
	//Send the baud rate prescaler and synchronization jump width (CNF1)
	MCP2515_Write(CNF1, cnf[0]); //scale and SJW
	//Send the propagation segment and phase segment 1 (CNF2)
	MCP2515_Write(CNF2, cnf[1]); //BTLMODE, PS1 7, Prop 
	//Send phase segment 2 (CNF3)
	MCP2515_Write(CNF3, cnf[2]);
	return 1; //Success
}

//Check if the general purpose interrupt is high (Message in buffer)
uint8_t MCP2515_CheckMessage(void) {
	return (!(PIN_MCP2515 & (1<<INT)));
}

//Reset the MCP2515
void MCP2515_Reset(){
	//Reset the MCP2515 via software
	SPI_Enable();
	SPI_Transfer(RESET);
	SPI_Disable();
}

//Initialize the SPI Interface and set-up the transceiver
void MCP2515_init(){
	/* Initialize the I/O Registers */
	/*				-I/O Map-
	 *	INT: PB0 (0: Input)
	 *  SPI I/O is handled in SPI.h 
	 */
	SPI_init();
	//Data Direction: 0 Input
	DDR_MCP2515 |= (0<<INT);
	//Port Input has Pull-Up Resistor
	PORT_MCP2515 |= (1<<INT);
	//Reset the MCP2515 via software
	SPI_Enable();
	SPI_Transfer(RESET);
	SPI_Disable();
	//Wait a brief second
	_delay_us(10);
	
	//Attempt to enter configuration mode
	MCP2515_Write(CANCTRL, 0x80);
	if(MCP2515_Read(CANCTRL) != 0x80){
		//Failed to enter configuration mode
		//PORTB |= (1<<PB7);
	}
	//MCP2515 is now in configuration mode
	//Set the Bus Speed for 10kb/s given an 8MHz Clock
	MCP2515_SetBaud(8E6, 500E3);Oscillator
	
	//Enable the general purpose interrupt to go high when a message is in the buffer
	MCP2515_Write(CANINTE, (1<<RX1IE)|(1<<RX0IE));
	//Do not use the buffer specific interrupts
	MCP2515_Write(BFPCTRL, 0x00);
	//Set TXnRTS as Inputs (Not used)
	MCP2515_Write(TXRTSCTRL, 0x00);
	//Add a filter/mask so this node only receives messages intended for it (based on input ID) RXMn must be set to 0,0 to use the filters to accept data TODO
	//DELETE: Turn off filters/take any message RXMn: 1, 1
	MCP2515_Write(RXB0CTRL, (1<<RXM1)|(1<<RXM0));
	MCP2515_Write(RXB1CTRL, (1<<RXM1)|(1<<RXM0));
	
	//Put the device in normal mode
	MCP2515_Write(CANCTRL, 0x00);
	if(MCP2515_Read(CANSTAT) != 0x00){
		//Failed to enter normal mode
		PORTB |= (1<<PB7);
	}
	return; //Return to call point
}

/********** Interrupt Service Routines *******************/