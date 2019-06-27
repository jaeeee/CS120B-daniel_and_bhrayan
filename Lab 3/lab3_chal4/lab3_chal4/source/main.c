/*	Author: agula002
 *  Partner(s) Name: Daniel Kwong, Bhrayan Escobar
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

unsigned char lowerToUpperNibble(char input){
	 return (input << 4) & 0xF0;
}

unsigned char upperToLowerNibble(char input){
	return (input >> 4) & 0x0F;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; 
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    while (1) {
		PORTB = upperToLowerNibble(PINA); 
		PORTC = lowerToUpperNibble(PINA);
		
			
    }
    return 1;
}
