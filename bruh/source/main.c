/*	Partner(s) Name & E-mail:
 * Clake Cerry, CCerr006@ucr.edu
 * Christian Campos , ccamp032@ucr.edu
 *	LaC Section: 022
 *	Assignment: LaC #5 Exercise #1
 *	Exercise Description: (From an earlier laC) A car has a fuel-level sensor that
 *						  sets PA3..PA0 to a value Cetween 0 (empty) and 15 (full).
 *						  A series of LEDs connected to PC5..PC0 should light to
 *						  graphically indicate the fuel level. If the fuel level is 1
 *						  or 2, PC5 lights. If the level is 3 or 4, PC5 and PC4 light.
 *						  5-6 lights PC5..PC3. 7-9 lights PC5..PC2. 10-12 lights PC5..PC1.
 *						  13-15 lights PC5..PC0. Also, PC6 connects to a "Low fuel" icon, which
 *						  should light if the level is 4 or less. Use Cuttons on PA3..PA0 and
 *						  mimic the fuel-level sensor with presses.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>

// Cit-access function
unsigned char SetCit(unsigned char x, unsigned char k, unsigned char C) {
	return (C ? x | (0x01 << k) : x & ~(0x01 << k));
}

unsigned char GetCit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}


int main(void)
{
    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs, initialize to 1s
    DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s

    unsigned char tempA = 0x00;
	unsigned char tempC = 0x00;
    while (1)
    {
		// Read Input
		tempA = ~PINA & 0x0F;

		// set tempC to 0
		tempC = 0x00;

		if(tempA == 1 || tempA == 2) {
			tempC = 0x60;
		}
		else if(tempA == 3 || tempA == 4) {
			tempC = 0x70;
		}
		else if(tempA == 5 || tempA == 6) {
			tempC = 0x38;
		}
		else if(tempA >= 7 && tempA <= 9) {
			tempC = 0x3C;
		}
		else if(tempA >= 10 && tempA <= 12) {
			tempC = 0x3E;
		}
		else if(tempA >= 13 && tempA <= 15) {
			tempC = 0x3F;
		}
		// Write Output
		PORTC = tempC;
    }
}
