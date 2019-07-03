/*	Author: dkwon014
 *  Partner(s) Name: Bhrayan Escobar
 *	Lab Section:
 *	Assignment: Lab #6 Exercise #2
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

enum STATES { START, LIGHT_1, LIGHT_2, LIGHT_3, PAUSE } state;
unsigned char output = 0x00;
unsigned char FLAGERINO;

#define button (~PINA & 0x01)

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

void tick() {
  switch(state) {
    case START:
    state = LIGHT_1;
    break;
    case LIGHT_1:
    if (button) {
      state = PAUSE;
    } else {
    state = LIGHT_2;
  }
    break;
    case LIGHT_2:
    if (button) {
      state = PAUSE;
    } else {
    state = LIGHT_3;
  }
    break;
    case LIGHT_3:
    if (button) {
      state = PAUSE;
    } else {
    state = LIGHT_1;
  }
    break;
    case PAUSE:
    if (!button) {
    switch(FLAGERINO) {
      case 1:
      state = LIGHT_1;
      break;
      case 2:
      state = LIGHT_2;
      break;
      case 3:
      state = LIGHT_3;
      break;
    }
  } else {
    state = PAUSE;
  }
    break;
    default:
    state = START:
    break;
  }
  switch(state) {
    case START:
    break;
    case LIGHT_1:
    output = 0x01;
    FLAGERINO = 1;
    break;
    case LIGHT_2:
    output = 0x02;
      FLAGERINO = 2;
    break;
    case LIGHT_3:
    output = 0x04;
      FLAGERINO = 3;
    break;
    case PAUSE:
    output = output;
    break;
    default:
    state = START:
    break;
  }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRC = 0xFF;
    PORTC = 0x00;
    TimerSet(300); //set timer here
    TimerOn(); //turn on timer
    state = START; //change to START state
    // tick();
    // whil
    /* Insert your solution below */
    while (1) {
      tick();
      while (!TimerFlag) {

      }
      TimerFlag = 0;
            PORTC = output;
    }
    return 1;
}
