/*
 * utils.h
 *
 * Created: 7/1/2025 8:35:42 PM
 *  Author: 
 */ 

#pragma once

#include "macros.h"
//Binary Helpers

struct FloatPair
{
	float x;
	float y;
	
};

UINT8 ClearBit(UINT8 OriginalByte, UINT8 bit);

UINT8 SetBit(UINT8 OriginalByte, UINT8 bit);

UINT8 ToggleBit(UINT8 OriginalByte, UINT8 bit);//no implementation yet

//Math Helpers

float ConvertToRadians(float degress);

FloatPair PolarToCartesian(float rads,float distance);

float cosine(float Radians);

float sine(float Radians);

UINT16 factorial(UINT8 value);

UINT16 pow(UINT8 value, UINT8 power);

