/*	Author: dkwon014
 *  Partner(s) Name: Bhrayan Escobar
 *	Lab Section:
 *	Assignment: Lab #6 Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #ifdef _SIMULATE_
 #include "simAVRHeader.h"
 #endif

 volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

 // Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
 unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
 unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

 void TimerOn() {
   TCCR1B = 0x0B;
   OCR1A = 125;
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

#define A0 (~PINA & 0x01)
#define A1 (~PINA & 0x02)

enum STATES { START, INIT, INCREMENT, RESET, DECREMENT, WAIT1, WAIT2, WAIT3 } state;
unsigned char holder = 0x00;

void tick() {
switch(state) {
case START:
state = INIT;
break;
case INIT:
if (A1 && A0) {
  state = WAIT3;
}
else if (A0) {
  state = WAIT1;
} else if (A1) {
  state = WAIT2;
} else {
  state = INIT;
}
break;
case INCREMENT:
state = INIT;
break;
case RESET:
state = INIT;
break;
case DECREMENT:
state = INIT;
break;
case WAIT1:
if (!A0) {
  state = INCREMENT;
} else {
  state = WAIT1;
}
break;
case WAIT2:
if (!A1) {
  state = DECREMENT;
} else {
  state = WAIT2;
}
break;
case WAIT3:
if ((A1) || (!A0)) {
  state = RESET;
} else {
  state = WAIT3;
}
break;
}

switch(state) {
case START:
break;
case INIT:
break;
case INCREMENT:
if (holder < 9) {
holder++;
}
break;
case RESET:
holder = 0;
break;
case DECREMENT:
if (holder > 0) {
holder--;
}
break;
case WAIT1:
break;
case WAIT2:
break;
case WAIT3:
break;
}
}

int main(void) {
    /* Insert DDR and PORT initializations */
DDRA = 0x00; DDRC = 0xFF; PORTA = 0xFF; PORTC = 0x00;
state = START;
holder = 7;
TimerSet(300); //set timer here
TimerOn(); //turn on timer
state = START; //change to START state
    while (1) {
//	holder = 7;
	tick();
  while (!TimerFlag) {

  }
  TimerFlag = 0;
        PORTC = holder;
    }
    return 1;
}
