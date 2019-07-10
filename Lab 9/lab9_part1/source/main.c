/*	Partner(s) Name & E-mail:
* Blake Berry, bberr006@ucr.edu
* Christian Campos , ccamp032@ucr.edu
*	Lab Section: 022
*	Assignment: Lab #9 Exercise #1
*
* Using the ATmega1284’s PWM functionality, design a system that uses three buttons to select one of
* three tones to be generated on the speaker.
* When a button is pressed, the tone mapped to it is generated on the speaker.
*
*	I acknowledge all content contained herein, excluding template or example
*	code, is my own original work.
*/




#include <avr/io.h>
#include <avr/interrupt.h>

// 0.954 hz is lowest frequency possible with this function,
// based on settings in PWM_on()
// Passing in 0 as the frequency will stop the speaker from generating sound
void set_PWM(double frequency) {
	static double current_frequency; // Keeps track of the currently set frequency
	// Will only update the registers when the frequency changes, otherwise allows
	// music to play uninterrupted.
	if (frequency != current_frequency) {
		if (!frequency) { TCCR0B &= 0x08; } //stops timer/counter
		else { TCCR0B |= 0x03; } // resumes/continues timer/counter

		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) { OCR0A = 0xFFFF; }

		// prevents OCR0A from underflowing, using prescaler 64					// 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) { OCR0A = 0x0000; }

		// set OCR3A based on desired frequency
		else { OCR0A = (short)(8000000 / (128 * frequency)) - 1; }

		TCNT0 = 0; // resets counter
		current_frequency = frequency; // Updates the current frequency
	}
}

void PWM_on() {
	TCCR0A = (1 << COM0A0 | 1 << WGM00);
	// COM3A0: Toggle PB3 on compare match between counter and OCR0A
	TCCR0B = (1 << WGM02) | (1 << CS01) | (1 << CS00);
	// WGM02: When counter (TCNT0) matches OCR0A, reset counter
	// CS01 & CS30: Set a prescaler of 64
	set_PWM(0);
}

void PWM_off() {
	TCCR0A = 0x00;
	TCCR0B = 0x00;
}


enum States{wait, cFour, dFour, eFour}state;

unsigned char button = 0x00;

void Tick(){

	switch(state){
		case wait:
		if(button == 0x01){
			state = cFour;
		}
		else if(button == 0x02){
			state = dFour;
		}
		else if(button == 0x04){
			state = eFour;
		}
		else{
			state = wait;
		}
		break;
		case cFour:
		if(button == 0x01){
			state = cFour;
		}
		else{
			state = wait;
		}
		break;
		case dFour:
		if(button == 0x02){
			state = dFour;
		}
		else{
			state = wait;
		}
		break;
		case eFour:
		if(button == 0x04){
			state = eFour;
		}
		else{
			state = wait;
		}
		break;
		default:
		break;
	}

	switch(state){
		case wait:
		set_PWM(0);
		break;
		case cFour:
		set_PWM(261.63);
		break;
		case dFour:
		set_PWM(293.66);
		break;
		case eFour:
		set_PWM(329.63);
		break;
		default:
		break;
	}
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs, initialize to 1s
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s

	PWM_on();

	state = wait;

	while(1){
		button = ~PINA & 0x07;
		Tick();
	}
}
