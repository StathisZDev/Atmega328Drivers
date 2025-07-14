/*
 * utils.cpp
 *
 * Created: 7/1/2025 8:45:08 PM
 *  Author: 
 */ 
#include "utils.h"

UINT8 ClearBit(UINT8 OriginalByte, UINT8 bit)
{
	UINT8 mask = 1 << bit;
	mask = ~mask;
	OriginalByte &= mask;
	return OriginalByte;
}

UINT8 SetBit(UINT8 OriginalByte, UINT8 bit)
{
	return OriginalByte |= (1 << bit);      //DDRB |= (1 << 4);     
}

float ConvertToRadians(float degrees)
{
	float temp = PI / 180;
	float resultinrads = degrees * temp;
	return resultinrads;
}

FloatPair PolarToCartesian(float degrees, float distance)
{
	float Radian_equivalent = ConvertToRadians(degrees);
	float x = distance * cosine(Radian_equivalent);
	float y = distance * sine(Radian_equivalent);
	return { x,y };
}

float cosine(float Radians)
{
	return 1 - pow(Radians,2) / factorial(2) + pow(Radians, 4) / factorial(4) - pow(Radians, 6) / factorial(6);
}

float sine(float Radians)
{
	return  pow(Radians, 1) / factorial(1) - pow(Radians, 3) / factorial(3) + pow(Radians, 5) / factorial(5);
}

UINT16 factorial(UINT8 value)
{
	if (value == 1 || value == 0)
	{
		return 1;
	}
	UINT16 High = value;
	UINT16 Low = --value;
	UINT16 sum = High * Low;
	while (Low > 1) //bigger than 1 so it does not zero out.
	{
		--Low;
		sum = sum * Low;
	}
	return sum;
}

UINT16 pow(UINT8 value, UINT8 power)
{
	UINT8 Times = power;
	UINT16 sum = value;
	while (Times > 0)
	{
		sum *= power;
		Times--;
	}
	return sum;
}


