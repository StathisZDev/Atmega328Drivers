/*
 * GPIO_REG.h
 *
 * Created: 7/2/2025 12:09:53 PM
 *  Author: zoula
 */ 


 *
 * Created: 7/2/2025 10:43:32 AM
 *  Author:
 */


 #ifndef GPIO_REG_H_
 #define GPIO_REG_H_

 #include <stdint.h>
 //I/O
 //Direct Register access
 //===========================================
 //Digital Registers read/write/direction
 extern volatile uint8_t& DDRD;
 extern volatile uint8_t& PORTD;
 extern volatile uint8_t& PIND;
 //Digital/Analog Registers read/write/direction
 extern volatile uint8_t& DDRC;
 extern volatile uint8_t& PORTC;
 extern volatile uint8_t& PINC;
 //Main Register for Analog
 extern volatile uint8_t& ADCSRA;
 //Used to disable Digital input
 extern volatile uint8_t& DIDR0;
 //mux0-4 sets the analog pin to read from
 extern volatile uint8_t& ADMUX;
 //Read Only Registers for Analog
 extern volatile uint8_t& ADCL;
 extern volatile uint8_t& ADCH;
 //===========================================
 //Timer
 //Overflow Register
 extern volatile uint8_t& TCCR0A;//MODE, PWM
 extern volatile uint8_t& TCCR0B;//pre.scaler 0x33
 
 extern volatile uint8_t& TIMSK0;//enable interrupts
 
 extern volatile uint8_t& TCNT0; //the actual timer(255 then overflow)


 #endif /* GPIO_REG_H_ */
