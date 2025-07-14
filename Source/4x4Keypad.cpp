/*
 * _4x4Keypad.cpp
 *
 * Created: 7/6/2025 6:00:11 PM
 *  Author: 
 */ 

#include "4X4Keypad.h"
#include "PBuzzer.h"
#include "Timers.h"
KeypadResult KPReadState(GPIOManager& GPIO,UINT8 RowOFFSET,UINT8 ColOFFSET)
{
	
	bool IsHigh;
	KeypadResult K;
	K.isPressed = false;
	for(UINT8 row = 0; row < 4; row++)
	{
		for(UINT8 c = 0;c <4; c++)
		{
			GPIO.DigitalOutput(c + RowOFFSET,HIGH,'d');//make sure all other rows are high
			GPIO.DigitalOutput(c + ColOFFSET,HIGH,'d');//make sure all other rows are high
		}
		GPIO.DigitalOutput(row + RowOFFSET,LOW,'d');//set one
		Delay(10); 
		for(UINT8 col  = 0;col  <4; col ++)
		{
			 IsHigh = GPIO.DigitalRead(col  + ColOFFSET,'d');
			if(!IsHigh)
			{
				K.indexrow = row;
				K.indexcol = col;
				K.isPressed = true;
				return K;
			}
		}
	}
	return K;
}
void WaitForInput(GPIOManager& Gpio,KeypadResult KPResult,char& InputFromUser)
{
	while(!KPResult.isPressed)
	{
		KPResult = KPReadState(Gpio,0,4);
		Delay(50);
	}
	
	InputFromUser = KEYPADMAP[KPResult.indexrow][KPResult.indexcol];
	while(KPResult.isPressed)
	{
		KPResult = KPReadState(Gpio,0,4);
		Delay(10);
		//wait for release
	}
}

void AssignState(CurrentState& state,char& InputFromUser,KeyPadState& keypadstate,const char PASSWORD[],GPIOManager& Gpio)
{
   if(InputFromUser == '\0')
   {
	   state = NO_INPUT;
   }
   if(InputFromUser == '#' && keypadstate.currentIndex >= 3)
   {
	   
	   state = TRY_ACCESS;
	   //state machine will split into GRANT or DENY ACCESS
   }
   if(InputFromUser == '*')
   {
	   state = RESET_INPUT;
   }
   if(InputFromUser >= 48 && InputFromUser <= 57 && keypadstate.currentIndex < 4)  //from 0 to 9 in ASCII dec table
   {
	   PlaySound(250,Gpio,1000);
	   state = ENTER_INPUT_NUMBER;	
   }
    HandleState(state,InputFromUser,PASSWORD,keypadstate,Gpio);
}


void HandleResetInput(KeyPadState& keypadstate,GPIOManager& Gpio)
{
	InitKeyPadState(keypadstate);
	PlaySound(100,Gpio,2000);
	return;
}
void InitKeyPadState(KeyPadState& keypadstate)
{
	keypadstate.currentIndex = 0;
	for(UINT8 i=0;i<4;i++)
	{
		keypadstate.CurrentNumInput[i] = 0;
	}
	//Clear LCD
}

void HandleTryAccess(KeyPadState& keypadstate,const char PASSWORD[],CurrentState& state)
{
	for(UINT8 i=0;i<4;i++)
	{
		if(keypadstate.CurrentNumInput[i] != PASSWORD[i])
		{
			
			state = DENY_ACCESS;
			return;
		}
	}
	state = GRANT_ACCESS;
}

void HandleGrandAccess(KeyPadState& keypadstate,GPIOManager& Gpio)
{
	//Clear LCD 
	PlaySound(100,Gpio,1000);
	Gpio.DigitalOutput(PB4,HIGH,'b');
	Delay(10000);
	Gpio.DigitalOutput(PB4,LOW,'b');
	return;
}

void HandleNoInput(KeyPadState& keypadstate)
{
	return; 
}

void HandleDenyAccess(KeyPadState& keypadstate,GPIOManager& Gpio)
{
		Gpio.DigitalOutput(PB0,HIGH,'b');
		Delay(10000);
		Gpio.DigitalOutput(PB0,LOW,'b');
	return;
	//Clear LCD 
}

void HandleEnterInputNumber(KeyPadState& keypadstate,char key,GPIOManager& Gpio)
{
	   keypadstate.CurrentNumInput[keypadstate.currentIndex] = key;
	   keypadstate.currentIndex++;
}
void HandleState(CurrentState state,char& InputFromUser,const char PASSWORD[],KeyPadState& keypadstate,GPIOManager& Gpio)
{
	switch(state)
	{
		case NO_INPUT:
		HandleNoInput(keypadstate);
		break;
		case TRY_ACCESS: //function will determine if its granted or denied (should fall down no break guaranteed to either be deny or grant)
		HandleTryAccess(keypadstate,PASSWORD,state);
		if(state == DENY_ACCESS)
		{
		   HandleDenyAccess(keypadstate,Gpio);
		}
		else if(state == GRANT_ACCESS)
		{
			HandleGrandAccess(keypadstate,Gpio);
		}
		HandleResetInput(keypadstate,Gpio);
		break;
		case RESET_INPUT:
		HandleResetInput(keypadstate,Gpio);
		break;
		case ENTER_INPUT_NUMBER:
		HandleEnterInputNumber(keypadstate,InputFromUser,Gpio);
		break;
	}
}