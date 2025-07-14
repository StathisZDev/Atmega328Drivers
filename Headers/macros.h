/*
 * macros.h
 *
 * Created: 7/1/2025 8:39:14 PM
 *  Author: 
 */ 
#pragma once
#include <stdint.h>


//Used to disable/enable specific analog pins digital side ADC0-5, PD6-7 --DIDR0
#define ADC0  0
#define ADC1  1
#define ADC2  2
#define ADC3  3
#define ADC4  4
#define ADC5  5
#define AIN0  6
#define AIN1  7
//ADCSRA
//ADPS2 PRESCALAR BITS 0-2
#define ADPS0 0
#define ADPS1 1
#define ADPS2 2
#define ADIE  3  //Interrupt Enable
#define ADIF  4  //Interrupt Flag
#define ADATE 5  //Auto Trigger Enable
#define ADSC  6  //Start Conversion
#define ADEN  7  //Enable
//ADMUX used for analog Reads
#define MUX0  0 //mux0-4 handles from which adc0-5 it should read from
#define MUX1  1
#define MUX2  2
#define MUX3  3
#define MUX4  4
#define ADLAR 5
#define REFS0 6  //Volts 6-7
#define REFS1 7  

//TCCR0B
//ClockSpeed Pre-scaler
#define CS00  0
#define CS01  1
#define CS02  2
//========================
#define INPUT  0   
#define OUTPUT 1

#define LOW   0
#define HIGH  1

#define MAXPINS 7  //(0-7)

#define PI 3.14159265359

#define ADCKHZ125     1,1,1
#define ADCKHZ250     1,1,0
#define ADCKHZ500	  1,0,1
#define MHZDefault	  0,0,0
#define TIMERKHZ250   0,1,1  //64 divisions  250.000hz

#define ETPOF    0.00102f;  //elapsed time per overflow (expecting 250khz) 1000
//TIMSK0
#define TOIE0 0 //enables interrupts for Timer0
typedef uint8_t UINT8;
typedef uint16_t UINT16;

#define F_CPU  16000000UL
#define SCKL   100000UL
