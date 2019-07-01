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
    // PORTB = 0xFF;
    PORTC = 0x00;
		// unsigned char (!PINA) = 0x00;
    /* Insert your solution below */
    while (1) {
			// (!PINA) = !(PINA);
			if (((!PINA) >= 0x0E) && ((!PINA) <= 0x0F)) {
				PORTC = 0x3F;
			}
			if (((!PINA) >= 0x0A) && ((!PINA) <= 0x0D)) {
				PORTC = 0x3E;
			}
			if (((!PINA) >= 0x07) && ((!PINA) <= 0x09)) {
				PORTC = 0x3C;
			}
			if (((!PINA) >= 0x05) && ((!PINA) <= 0x06)) {
				PORTC = 0x38;
			}
			if (((!PINA) >= 0x03) && ((!PINA) <= 0x04)) {
				PORTC = 0x70;
			}
			if (((!PINA) >= 0x01) && ((!PINA) <= 0x02)) {
				PORTC = 0x60;
			}
			// PORTC = 0x0F;
    }
    return 1;
}
