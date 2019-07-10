/*	Author: dkwon014
 *  Partner(s) Name: Bhrayan Escobar
 *	Lab Section:
 *	Assignment: Lab #9  Exercise #1
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
// // 0.954 hz is lowest frequency possible with this function,
// // based on settings in PWM_on()
// // Passing in 0 as the frequency will stop the speaker from generating sound
// void set_PWM(double frequency) {
// 	static double current_frequency; // Keeps track of the currently set frequency
// 	// Will only update the registers when the frequency changes, otherwise allows
// 	// music to play uninterrupted.
// 	if (frequency != current_frequency) {
// 		if (!frequency) { TCCR3B &= 0x08; } //stops timer/counter
// 		else { TCCR3B |= 0x03; } // resumes/continues timer/counter
//
// 		// prevents OCR3A from overflowing, using prescaler 64
// 		// 0.954 is smallest frequency that will not result in overflow
// 		if (frequency < 0.954) { OCR3A = 0xFFFF; }
//
// 		// prevents OCR0A from underflowing, using prescaler 64					// 31250 is largest frequency that will not result in underflow
// 		else if (frequency > 31250) { OCR3A = 0x0000; }
//
// 		// set OCR3A based on desired frequency
// 		else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }
//
// 		TCNT3 = 0; // resets counter
// 		current_frequency = frequency; // Updates the current frequency
// 	}
// }
//
// void PWM_on() {
// 	TCCR3A = (1 << COM3A0);
// 	// COM3A0: Toggle PB3 on compare match between counter and OCR0A
// 	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
// 	// WGM02: When counter (TCNT0) matches OCR0A, reset counter
// 	// CS01 & CS30: Set a prescaler of 64
// 	set_PWM(0);
// }
//
// void PWM_off() {
// 	TCCR0A = 0x00;
// 	TCCR0B = 0x00;
// }

void set_PWM(double frequency) {
  static double current_frequency;
  if (frequency != current_frequency) {
    if (!frequency) { TCCR3B &= 0x08; }
    else { TCCR3B |= 0x03; }
    if (frequency < 0.954) { OCR3A = 0xFFFF; }
    else if (frequency > 31250) { OCR3A = 0x0000; }
    else { OCR3A = (short) (8000000 / (128 * frequency)) - 1; }
    TCNT3 = 0;
    current_frequency = frequency;
  }
}

void PWM_on() {
  TCCR3A = (1 << COM3A0);
  TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
  set_PWM(0);
}
//part 1 code
#define button (~PINA & 0x07)
enum STATES { WAIT, PLAYC, PLAYD, PLAYE } state;

void tick() {
	switch(state) {
		case WAIT:
		switch(button) {
			case 0x01:
			state = PLAYC;
			break;
			case 0x02:
			state = PLAYD;
			break;
			case 0x04:
			state = PLAYE;
			break;
			default:
			state = WAIT;
			break;
		}
    break;
		case PLAYC:
		if (button == 0x01) {
			state = PLAYC;
		} else {
			state = WAIT;
		}
		break;
		case PLAYD:
		if (button == 0x02) {
			state = PLAYD;
		} else {
			state = WAIT;
		}
		break;
		case PLAYE:
		if (button == 0x04) {
			state = PLAYE;
		} else {
			state = WAIT;
		}
		break;
	}
	switch(state) {
		case WAIT:
		set_PWM(0);
		break;
		case PLAYC:
		set_PWM(261.63);
		break;
		case PLAYD:
		set_PWM(293.66);
		break;
		case PLAYE:
		set_PWM(329.63);
		break;
	}
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	PWM_on();
	state = WAIT;
	while(1) {
		tick();
	}
      // set_PWM(261.63);
  return 1;
}
