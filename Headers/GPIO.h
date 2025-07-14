/*
 * GPIO.h
 *
 * Created: 7/1/2025 8:35:54 PM
 *  Author: 
 */ 
#pragma once

#include "utils.h"
#include "macros.h"
#include <avr/io.h>
class GPIOManager
{
	public:
	GPIOManager();
//I/O
	void		SetDir(UINT8 PinNum, UINT8 Direction,char PinGroup);
	void		DigitalOutput(UINT8 PinNum, UINT8 Mode,char PinGroup);
	bool		DigitalRead(UINT8 PinNum,char PinGroup);
	void		AnalogRead(UINT8 bit);
	void		AnalogWriteAuto(char AB);
	void		AnalogWrite(char AB,UINT8 pulsewidthmodulation);
	void		SetClockSpeed(UINT8 bit0, UINT8 bit1, UINT8 bit2);
//SPI 
	void		SpiInit();
	UINT16		TransferSpi(); 
	void		EnableSpi();
//I2C
	void		I2cInit(); 	
	void		I2cStart();
	void		I2cStop();
	void		I2cWrite(UINT8 data);
};