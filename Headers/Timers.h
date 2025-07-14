/*
 * Timers.h
 *
 * Created: 7/14/2025 4:49:43 PM
 *  Author: 
 */ 

#include "macros.h"

#ifndef TIMERS_H_
#define TIMERS_H_
	
void		Timer0Init();
void		SetTimerPsc(UINT8 bit0, UINT8 bit1, UINT8 bit2);
void		AutoConfigurePsc2();
void		Timer2Init();
void		DelayMicro(UINT16 miliseconds);
void		Delay(UINT16 miliseconds);
uint32_t	Elapsed();
uint32_t	ElapsedMicro();

#endif /* TIMERS_H_ */