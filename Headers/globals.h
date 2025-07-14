/*
 * globals.h
 *
 * Created: 7/1/2025 8:36:09 PM
 *  Author: 
 */ 


#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>
#include "macros.h"

extern volatile UINT16 AdcResult;

extern volatile uint32_t timeoverflowstack;  //every time the TNCT0 overflows it adds one

extern const char password1234[4]; 

extern bool PWMT2enabled;
#endif