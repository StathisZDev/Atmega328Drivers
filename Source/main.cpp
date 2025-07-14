/*
 * DriversFor328.cpp
 *
 * Created: 7/1/2025 8:33:37 PM
 * Author : 
 */ 

#include <avr/io.h>
#include "macros.h"
#include "GPIO.h"
#include "globals.h"
#include "PBuzzer.h"
#include "4X4Keypad.h"

//KeyPad Demo 
GPIOManager  Gpio;
KeyPadState  KPstate;
CurrentState KPcurrentState;
KeypadResult KPResult;
char KPInput;
	
void SetUp()
{
	InitKeyPadState(KPstate);
	KPResult.isPressed = false;
	
	Gpio.SetDir(PB4,OUTPUT,'b');
	//LED
	Gpio.SetDir(PB0,OUTPUT,'b');
	//Passive Buzzer
	Gpio.SetDir(PB3,OUTPUT,'b');
	Gpio.DigitalOutput(PB3,LOW,'b');
	//Rows
	Gpio.SetDir(PD0,OUTPUT,'d');
	Gpio.SetDir(PD1,OUTPUT,'d');
	Gpio.SetDir(PD2,OUTPUT,'d');
	Gpio.SetDir(PD3,OUTPUT,'d');
	//Columns
	Gpio.SetDir(PD4,INPUT,'d');
	Gpio.SetDir(PD5,INPUT,'d');
	Gpio.SetDir(PD6,INPUT,'d');
	Gpio.SetDir(PD7,INPUT,'d');
}

void Entry()
{
	SetUp();
	while(1)
	{
		WaitForInput(Gpio,KPResult,KPInput);		
		AssignState(KPcurrentState,KPInput,KPstate,password1234,Gpio);
		Gpio.Delay(50);
	}
}



int main()
{
	Entry();
}
