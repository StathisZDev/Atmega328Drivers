/*
 * _4X4Keypad.h
 *
 * Created: 7/6/2025 5:56:03 PM
 *  Author: 
 */ 
#include "GPIO.h"

struct KeypadResult
{
	UINT8  indexrow;	
	UINT8  indexcol;
	bool   isPressed;	
};
#ifndef X4KEYPAD_H_
#define X4KEYPAD_H_


KeypadResult KPReadState(GPIOManager& GPIO,UINT8 RowOFFSET,UINT8 ColOFFSET);

const char KEYPADMAP[4][4] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'}
};

struct KeyPadState
{
	UINT8 currentIndex;
	UINT8 CurrentNumInput[4];
};

void SetPassword(KeyPadState State,char Digit1,char Digit2);
void ResetState(KeyPadState State);

enum CurrentState
{
    TRY_ACCESS,	
	GRANT_ACCESS,
	DENY_ACCESS,
	RESET_INPUT,
	ENTER_INPUT_NUMBER, 
	NO_INPUT
};

void WaitForInput(GPIOManager& Gpio,KeypadResult KPResult,char& InputFromUser);
void AssignState(CurrentState& state,char& InputFromUser,KeyPadState& State,const char PASSWORD[],GPIOManager& Gpio);
void HandleState(CurrentState state,char& InputFromUser,const char PASSWORD[],KeyPadState& keypadstate,GPIOManager& Gpio);

void InitKeyPadState(KeyPadState& keypadstate);
void HandleTryAccess(KeyPadState& keypadstate,const char PASSWORD[],CurrentState& state);
void HandleGrandAccess(KeyPadState& keypadstate,GPIOManager& Gpio);
void HandleNoInput(KeyPadState& keypadstate);
void HandleDenyAccess(KeyPadState& keypadstate,GPIOManager& Gpio);
void HandleResetInput(KeyPadState& keypadstate,GPIOManager& Gpio);
void HandleEnterInputNumber(KeyPadState& keypadstate,char key,GPIOManager& Gpio);


#endif /* 4X4KEYPAD_H_ */