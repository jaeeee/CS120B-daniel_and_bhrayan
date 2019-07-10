/*	Author: dkwon014
 *  Partner(s) Name: Bhrayan Escobar
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
//
// #include <avr/io.h>
// #ifdef _SIMULATE_
// #include "simAVRHeader.h"
// #endif
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

void set_PWM(double frequency) {
  static double current_frequency;
  if (frequency != current_frequency) {
    if (!frequency) { TCCR3B &= 0x08; }
    else { TCCR3B |= 0x03; }
    if (frequency < 0.954) { OCR3A = 0xFFFF; }
    else if (frequency > 31250) { OCR3A = 0x0000; }
    else { OCR3A = (short) (8000000 / (1280 * frequency)) - 1; }
    TCNT3 = 0;
    current_frequency = frequency;
  }
}

void PWM_on() {
  TCCR3A = (1 << COM3A0);
  TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
  set_PWM(0);
}

void PWM_off() {
  TCCR3A = 0x00;
  TCCR3B = 0x00;
}

#define button (~PINA & 0x07)
double NOTES[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
// enum STATES { OFF, ON, HOLDON, HOLDOFF, PLAY, UP, WAITUP, DOWN, WAITDOWN } state;
enum STATES { FIRST, SECOND, THIRD, FOURTH, FIFTH, OFF } state;
unsigned char i;

void tick() {
	switch(state) {
    case FIRST:
    set_PWM(NOTES[0]);
    state = SECOND;
    // i++;
    break;
    case SECOND:
    // set_PWM(i++);
    set_PWM(NOTES[1]);
    // i++;
    state = THIRD;
    break;
    case THIRD:
      // set_PWM(i++);
      set_PWM(NOTES[2]);
      // i++;
      state = FOURTH;
    break;
    case FOURTH:
      // set_PWM(i++);
      set_PWM(NOTES[3]);
      // i+=2;
      state = FIFTH;
    break;
    case FIFTH:
    set_PWM(NOTES[4]);
    // i--;
      // set_PWM(i++);
state = OFF;
    break;
    case OFF:
    PWM_off();
    break;
  }
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	PWM_on();
  TimerSet(50);
  TimerOff();
	state = FIRST;
  i = 0;
	while(1) {
		tick();
    while (!TimerFlag) {}
    TimerFlag = 0;
	}
}
