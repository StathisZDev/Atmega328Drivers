/*
 * GPIO.cpp
 *
 * Created: 7/1/2025 8:44:50 PM
 *  Author: 
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "GPIO.h"
#include "globals.h"
#include "utils.h"
GPIOManager::GPIOManager()
{
	SetClockSpeed(1,1,1);
	 ADCSRA |= (1 << ADEN); 
	PWMT2enabled = false;
	Timer0Init();
	Timer2Init();
}
//Use this function To Configure the Direction of all Pins (INPUT/OUTPUT)
void GPIOManager::SetDir(UINT8 PinNum, UINT8 Direction,char PinGroup)
{
	if(PinNum > MAXPINS) return;					   
	if(Direction > OUTPUT || Direction < INPUT) return;//error (If not 1 or 0 )
	
	if(PinGroup == 'D' || PinGroup == 'd')
	{
		if (Direction == INPUT)
		{
			DDRD = ClearBit(DDRD,PinNum);
		}
	    else if (Direction == OUTPUT) 
		{
			DDRD = SetBit(DDRD,PinNum);
		}
	}
	else if(PinGroup == 'C' || PinGroup == 'c')
	{
		if (Direction == INPUT)
		{
			DDRC = ClearBit(DDRC,PinNum);
		}
		else if (Direction == OUTPUT)
		{
			DDRC = SetBit(DDRC, PinNum);
		}
	}
	else if (PinGroup == 'B' || PinGroup == 'b')
	{
		if (Direction == INPUT)
		{
			DDRB = ClearBit(DDRB,PinNum);
		}
		else if (Direction == OUTPUT)
		{
			DDRB = SetBit(DDRB,PinNum);
		}
	}
	return;
}

void GPIOManager::DigitalOutput(UINT8 PinNum, UINT8 Mode,char PinGroup)
{
	if (PinNum > MAXPINS)return;
	if(PinGroup == 'D' || PinGroup == 'd')
	{
		if (Mode == HIGH)
		{
			PORTD = SetBit(PORTD,PinNum);
		}
		else if (Mode == LOW)
		{
			PORTD = ClearBit(PORTD, PinNum);
		}
	}
	else if(PinGroup == 'B' || PinGroup == 'b')
	{
		if (Mode == HIGH)
		{
			PORTB = SetBit(PORTB,PinNum);
		}
		else if (Mode == LOW)
		{
			PORTB = ClearBit(PORTB, PinNum);
		}
	}
	else if(PinGroup == 'C' || PinGroup == 'C')
	{
		if (Mode == HIGH)
		{
			PORTC = SetBit(PORTC,PinNum);
		}
		else if (Mode == LOW)
		{
			PORTC = ClearBit(PORTC, PinNum);
		}
	}
	return;
}

bool GPIOManager::DigitalRead(UINT8 PinNum,char PinGroup)
{
	if (PinNum > MAXPINS)return false; 
	UINT8 mask = 1 << PinNum;
	if(PinGroup == 'D' || PinGroup == 'd')
	{
		if ((PIND & mask) != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(PinGroup == 'B' || PinGroup == 'b')
	{
		if ((PINB & mask) != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(PinGroup == 'C' || PinGroup == 'c')
	{
		if ((PINC & mask) != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	return false;
}

void GPIOManager::AnalogRead(UINT8 bit)
{
	if (bit > MAXPINS)return;
	DIDR0 |= (1 <<bit);										//disable Digital
	DDRC &= ~(1 << bit);									//set pin as input
	ADMUX = (1 << REFS0);									//Set voltage mode 3.3-5v
	ADMUX  |= bit;											//Set MUX to read input from.
	ADCSRA |= (1 << ADSC);									//Start Conversion
	while (ADCSRA & (1 << ADSC));							//wait until conversion is done
	UINT16 result = ADCL;									//combine H L and read 10 bit result 
	result |= (ADCH << 8);
	AdcResult = result;
	return;
}

void GPIOManager::AnalogWriteAuto(char AB)
{
    if(PWMT2enabled == false)return;
	if(AB == 'A' || AB == 'a')
	{
		OCR2A  = (AdcResult /4); 
	}
	else if (AB == 'B' || AB == 'b')
	{
		OCR2B = (AdcResult /4);
	}
}

void GPIOManager::AnalogWrite(char AB,UINT8 pulsewidthmodulation)
{
  if(PWMT2enabled == false)return;
  if(AB == 'A' || AB == 'a')
  {
	  OCR2A  = pulsewidthmodulation;
  }
  else if (AB == 'B' || AB == 'b')
  {
	  OCR2B = pulsewidthmodulation;
  }
}

void GPIOManager::SetClockSpeed(UINT8 bit0, UINT8 bit1, UINT8 bit2)
{
	if(bit0 > 1 || bit1 > 1 || bit2 > 1 )return; 
	ADCSRA |= (bit0 << ADPS0);
	ADCSRA |= (bit1 << ADPS1);
	ADCSRA |= (bit2 << ADPS2);
}

void GPIOManager::SetTimerPsc(UINT8 bit2 , UINT8 bit1, UINT8  bit0)
{
	if(bit0 > 1 || bit1 > 1 || bit2 > 1 )return; 
	TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
	TCCR0B |=  bit0 << CS00;
	TCCR0B |=  bit1 << CS01;
	TCCR0B |=  bit2 << CS02;
}

void GPIOManager::Timer0Init()
{
	TCCR0A = 0;													 //Normal Mode
	SetTimerPsc(TIMERKHZ250);									 //set clock to 250.000hz
	TCNT0 = 0;													 //zero counter
	TIMSK0 |= (1 << TOIE0);										 //enables interrupts and calls ISR(TIMED_OVF_vect) on overflow{}
	sei();														 //enables global interrupts
}

ISR(TIMER0_OVF_vect)
{
	timeoverflowstack++;
}

uint32_t GPIOManager::Elapsed()
{
	uint32_t ms = 0;
	cli();														 //stops global interrupts for safer read
	ms = timeoverflowstack; 
	sei();														 //re enables global interrupts
	uint32_t overflowPeriod_us = 1024;
	return	(ms * overflowPeriod_us) / 1000;
}
uint32_t GPIOManager::ElapsedMicro()
{
	uint32_t ms = 0;
	cli();														 //stops global interrupts for safer read
	ms = timeoverflowstack;
	sei();														 //re enables global interrupts
	uint32_t overflowPeriod_us = 1024;
	return	(ms * overflowPeriod_us);
}

void GPIOManager::Timer2Init()
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

void GPIOManager::AutoConfigurePsc2()
{
   TCCR2B |=   0x03; 
}

void GPIOManager::Delay(UINT16 miliseconds)
{
	uint32_t startingTime = Elapsed();
	uint32_t MaxWaitTime = startingTime + miliseconds;
	while(startingTime < MaxWaitTime)
	{
		startingTime = Elapsed();
	}	
	return;
}
void GPIOManager::DelayMicro(UINT16 miliseconds)
{
	uint32_t startingTime = ElapsedMicro();
	uint32_t MaxWaitTime = startingTime + miliseconds;
	while(startingTime < MaxWaitTime)
	{
		startingTime = ElapsedMicro();
	}
	return;
}

void GPIOManager::I2cInit()
{
   TWBR = ((F_CPU/SCKL) -16) / 2;								 //sets bitrate and prescaler
   TWSR = 0;   
}

void GPIOManager::I2cStart()
{
    TWCR =  (1 << TWEN) | (1 << TWSTA) | (1 << TWINT);
    while(!(TWCR & 1 << TWINT));								 //clear interrupt and wait till it goes to 1 again
}

void GPIOManager::I2cStop()
{
	TWCR = (1 << TWEN) | (1 << TWSTO) | (1 << TWINT);
}

void GPIOManager::I2cWrite(UINT8 data)
{
    TWDR = data;
	TWCR = (1 << TWEN);
	TWCR |=  (1 << TWINT);
	while(!(TWCR & (1 << TWINT)));
}

void GPIOManager::SpiInit()
{
	SPCR =  (1 <<MSTR) | (1 <<SPR1) | (1 <<SPR0) | (1 << SPE);	 //SPIE Off.use polling
	SPSR = 1 <<  SPI2X;											 //doubles the clock cycles.
}

UINT16 GPIOManager::TransferSpi()
{
	UINT16 result = 0;
	SPDR = 0x00;
	while(!(SPSR & (1 << SPIF))){};
		result = SPDR << 8;
	SPDR = 0x00;
	while(!(SPSR & (1 << SPIF))){};
		result |= SPDR;
	return result;
}

void  GPIOManager::EnableSpi()
{
	GPIOManager::SpiInit();
}