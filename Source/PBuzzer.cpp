/*
 * PBuzzer.cpp
 *
 * Created: 7/8/2025 5:01:53 PM
 *  Author: 
 */ 
#include "GPIO.h"
#include "Timers.h"
void PlaySound(UINT8 number,GPIOManager& Gpio,const UINT8 PlayDurationMs)
{
	while(number > 255)
	{
		number /= 4;
	}

	    TCCR2A = (1 << COM2A0);               // Toggle OC2A on compare match
	    TCCR2B = (1 << WGM22) | (1 << CS21);  // CTC mode, prescaler 8
	    OCR2A = number;                       // Set frequency (lower = higher pitch)

	    // Wait for sound duration
	    Delay(PlayDurationMs);

	    // Turn off the buzzer
	    TCCR2A &= ~((1 << COM2A0) | (1 << COM2A1)); // Stop toggling OC2A
	    TCCR2B = 0;                                 // Stop timer
	    PORTB &= ~(1 << PB3);
}
