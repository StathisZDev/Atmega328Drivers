/*
 * Timers.cpp
 *
 * Created: 7/14/2025 4:49:58 PM
 *  Author: 
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timers.h"
#include "globals.h"

void Delay(UINT16 miliseconds)
{
	uint32_t startingTime = Elapsed();
	uint32_t MaxWaitTime = startingTime + miliseconds;
	while(startingTime < MaxWaitTime)
	{
		startingTime = Elapsed();
	}
	return;
}

void DelayMicro(UINT16 miliseconds)
{
	uint32_t startingTime = ElapsedMicro();
	uint32_t MaxWaitTime = startingTime + miliseconds;
	while(startingTime < MaxWaitTime)
	{
		startingTime = ElapsedMicro();
	}
	return;
}

uint32_t Elapsed()
{
	uint32_t ms = 0;
	cli();														 //stops global interrupts for safer read
	ms = timeoverflowstack;
	sei();														 //re enables global interrupts
	uint32_t overflowPeriod_us = 1024;
	return	(ms * overflowPeriod_us) / 1000;
}
uint32_t ElapsedMicro()
{
	uint32_t ms = 0;
	cli();														 //stops global interrupts for safer read
	ms = timeoverflowstack;
	sei();														 //re enables global interrupts
	uint32_t overflowPeriod_us = 1024;
	return	(ms * overflowPeriod_us);
}

void Timer2Init()
{
	TCCR2A |= 1 << COM2A1;										 //set non inverted mode
	TCCR2A |= 1 << WGM21;										 //set fast PWM
	TCCR2A |= 1 << WGM20;
	TCCR2B &= ~(1 << WGM22);
	TCNT2 = 0;													 //start counter from 0
	AutoConfigurePsc2();
	PWMT2enabled = true;
	TCCR2A &= ~((1 << COM2A0) | (1 << COM2A1));
}

void Timer0Init()
{
	TCCR0A = 0;													 //Normal Mode
	SetTimerPsc(TIMERKHZ250);									 //set clock to 250.000hz
	TCNT0 = 0;													 //zero counter
	TIMSK0 |= (1 << TOIE0);										 //enables interrupts and calls ISR(TIMED_OVF_vect) on overflow{}
	sei();														 //enables global interrupts
}

void AutoConfigurePsc2()
{
	TCCR2B |=   0x03;
}

void SetTimerPsc(UINT8 bit2 , UINT8 bit1, UINT8  bit0)
{
	if(bit0 > 1 || bit1 > 1 || bit2 > 1 )return;
	TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
	TCCR0B |=  bit0 << CS00;
	TCCR0B |=  bit1 << CS01;
	TCCR0B |=  bit2 << CS02;
}
