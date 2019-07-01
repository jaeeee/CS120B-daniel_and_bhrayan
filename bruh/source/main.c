/*	Author: dkwon014
 *  Partner(s) Name: Bhrayan Escobar
 *	Lab Section:
 *	Assignment: Lab #3  Exercise #2
 *	Exercise Description: A car has a fuel-level sensor that sets PA3..PA0 to a value between 0 (empty) and 15 (full).
 *  A series of LEDs connected to PC5..PC0 should light to graphically indicate the fuel level.
 *  If the fuel level is 1 or 2, PC5 lights. If the level is 3 or 4, PC5 and PC4 light.
 *  Level 5-6 lights PC5..PC3. 7-9 lights PC5..PC2. 10-12 lights PC5..PC1. 13-15 lights PC5..PC0.
 *  Also, PC6 connects to a "Low fuel" icon, which should light if the level is 4 or less.  (The example below shows the display for a fuel level of 3).
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char SetBit(char pin, char bit_position, char bit_value) {
	return (bit_value ? pin | (0x01 << bit_position)
			: pin & ~(0x01 << bit_position));
}

unsigned char GetBit(char port, char bit_position) {
	return ( (port >> bit_position) & 0x01 );
}

int main(void) {
    /* Insert DDR and PORT initializations */
		DDRA = 0x00; //input
    DDRB = 0x00; //input
    DDRC = 0xFF; //output
    PORTA = 0xFF;
    // PORTC = 0xFF;
    PORTC = 0x00;
		unsigned char holder = 0x00;
    /* Insert your solution below */
    while (1) {
			holder = (~PINA & 0x0F);
			if ((holder >= 0x0E) && (holder <= 0x0F)) {
				PORTC = 0x3F;
			}
			if ((holder >= 0x0A) && (holder <= 0x0D)) {
				PORTC = 0x3E;
			}
			if ((holder >= 0x07) && (holder <= 0x09)) {
				PORTC = 0x3C;
			}
			if ((holder >= 0x05) && (holder <= 0x06)) {
				PORTC = 0x38;
			}
			if ((holder >= 0x03) && (holder <= 0x04)) {
				PORTC = 0x70;
			}
			if ((holder >= 0x01) && (holder <= 0x02)) {
				PORTC = 0x60;
			}
			// PORTC = 0x0F;
    }
    return 1;
}

/*	Partner(s) Name & E-mail:
 * Blake Berry, bberr006@ucr.edu
 * Christian Campos , ccamp032@ucr.edu
 *	Lab Section: 022
 *	Assignment: Lab #5 Exercise #1
 *	Exercise Description: (From an earlier lab) A car has a fuel-level sensor that
 *						  sets PA3..PA0 to a value between 0 (empty) and 15 (full).
 *						  A series of LEDs connected to PB5..PB0 should light to
 *						  graphically indicate the fuel level. If the fuel level is 1
 *						  or 2, PB5 lights. If the level is 3 or 4, PB5 and PB4 light.
 *						  5-6 lights PB5..PB3. 7-9 lights PB5..PB2. 10-12 lights PB5..PB1.
 *						  13-15 lights PB5..PB0. Also, PB6 connects to a "Low fuel" icon, which
 *						  should light if the level is 4 or less. Use buttons on PA3..PA0 and
 *						  mimic the fuel-level sensor with presses.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>

// Bit-access function
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}

unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}


int main(void)
{
    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs, initialize to 1s
    DDRB = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s

    unsigned char tempA = 0x00;
	unsigned char tempB = 0x00;
    while (1)
    {
		// Read Input
		tempA = ~PINA & 0x0F;

		// set tempB to 0
		tempB = 0x00;

		if(tempA == 1 || tempA == 2) {
			tempB = 0x60;
		}
		else if(tempA == 3 || tempA == 4) {
			tempB = 0x70;
		}
		else if(tempA == 5 || tempA == 6) {
			tempB = 0x38;
		}
		else if(tempA >= 7 && tempA <= 9) {
			tempB = 0x3C;
		}
		else if(tempA >= 10 && tempA <= 12) {
			tempB = 0x3E;
		}
		else if(tempA >= 13 && tempA <= 15) {
			tempB = 0x3F;
		}
		// Write Output
		PORTC = tempB;
    }
}
