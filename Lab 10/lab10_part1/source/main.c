

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

enum BL_States { BL_SMStart, BL_LedOff, BL_LedOn } BL_State;
enum TL_States { TL_SMStart, TL_T0, TL_T1, TL_T2 } TL_State;
enum CL_States { CL_SMStart, Combine} CL_State;

unsigned char threeLed = 0x00;
unsigned char blinkLed = 0x00;

void TickFct_BlinkLed() {
	switch(BL_State){
		case BL_SMStart:
		BL_State = BL_LedOff;
		break;
		case BL_LedOff:
		BL_State = BL_LedOn;
		break;
		case BL_LedOn:
		BL_State = BL_LedOff;
		break;
		default:
		break;
	}
	switch(BL_State){
		case BL_SMStart:
		blinkLed = 0x00;
		break;
		case BL_LedOff:
		blinkLed = 0x00;
		break;
		case BL_LedOn:
		blinkLed = 0x01;
		break;
		default:
		break;
	}
}

void TickFct_ThreeLeds() {
	switch(TL_State){
		case TL_SMStart:
		TL_State = TL_T0;
		break;
		case TL_T0:
		TL_State = TL_T1;
		break;
		case TL_T1:
		TL_State = TL_T2;
		break;
		case TL_T2:
		TL_State = TL_T0;
		break;
		default:
		break;
	}
	switch(TL_State){
		case TL_SMStart:
		threeLed = 0x00;
		break;
		case TL_T0:
		threeLed = 0x01;
		break;
		case TL_T1:
		threeLed = 0x02;
		break;
		case TL_T2:
		threeLed = 0x04;
		break;
		default:
		break;
	}
}

void TickFct_CombineLeds() {
	switch(CL_State){
		case CL_SMStart:
		CL_State = Combine;
		break;
		case Combine:
		CL_State = Combine;
		break;
		default:
		break;
	}
	switch(CL_State){
		case CL_SMStart:
		PORTC = 0x00;
		break;
		case Combine:
		PORTC = (blinkLed << 3) | threeLed;
		break;
		default:
		break;
	}
}

int main(void)
{
	DDRC = 0xFF; PORTC = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s

	TimerSet(1000);
	TimerOn();
	BL_State = BL_SMStart;
	TL_State = TL_SMStart;
	CL_State = CL_SMStart;
	while (1) {
		TickFct_BlinkLed();    // Tick the BlinkLed synchSM
		TickFct_ThreeLeds();   // Tick the threeLed synchSM
		TickFct_CombineLeds();
		while (!TimerFlag){}   // Wait for timer period
		TimerFlag = 0;         // Lower flag raised by timer
	}
}
