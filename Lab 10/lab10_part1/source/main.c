

#include <avr/io.h>
#include <avr/interrupt.h>
// #include "timer.h"


volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

// enum STATES { START, LIGHT_1, LIGHT_2, LIGHT_3 } state;
// unsigned char output = 0x00;

void TimerOn() {
  TCCR1B = 0x0B;
  OCR1A = 100;
  TIMSK1 = 0x02;
  TCNT1 = 0;
  _avr_timer_cntcurr = _avr_timer_M;
  SREG |= 0x80;
}

void TimerOff() {
  TCCR1B = 0x00;
}

void TimerISR() {
  TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}
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
