/*
 * GPIO_REG.cpp
 *
 * Created: 7/2/2025 12:11:54 PM
 *  Author: zoula
 */ 

 #include "GPIO_REG.h"

 volatile uint8_t& DDRD = *reinterpret_cast<volatile UINT8*>(0x2A);;
 volatile uint8_t& PORTD = *reinterpret_cast<volatile UINT8*>(0x2B);;
 volatile uint8_t& PIND = *reinterpret_cast<volatile UINT8*>(0x29);;
 //Digital/Analog Registers read/write/direction
 volatile uint8_t& DDRC = *reinterpret_cast<volatile UINT8*>(0x27);;
 volatile uint8_t& PORTC = *reinterpret_cast<volatile UINT8*>(0x28);;
 volatile uint8_t& PINC = *reinterpret_cast<volatile UINT8*>(0x26);;
 //Main Register for Analog
 volatile uint8_t& ADCSRA = *reinterpret_cast<volatile UINT8*>(0x7A);;
 //Used to disable Digital input
 volatile uint8_t& DIDR0 = *reinterpret_cast<volatile UINT8*>(0x7E);;
 //mux0-4 sets the analog pin to read from
 volatile uint8_t& ADMUX = *reinterpret_cast<volatile UINT8*>(0x7C);;
 //Read Only Registers for Analog
 volatile uint8_t& ADCL = *reinterpret_cast<volatile UINT8*>(0x78);;
 volatile uint8_t& ADCH = *reinterpret_cast<volatile UINT8*>(0x79);;
 //===========================================
 //Timer
 //Overflow Register
 volatile uint8_t& TCCR0A  = *reinterpret_cast<volatile UINT8*>(0x24);;//MODE,        PWM
 volatile uint8_t& TCCR0B = *reinterpret_cast<volatile UINT8*>(0x25);;//pre.scaler 0x33
 
 volatile uint8_t& TIMSK0 = *reinterpret_cast<volatile UINT8*>(0x6E);;//enable interrupts
 
 volatile uint8_t& TCNT0 = *reinterpret_cast<volatile UINT8*>(0x26);
