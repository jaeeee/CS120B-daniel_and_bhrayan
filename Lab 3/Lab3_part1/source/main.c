/*	Author: dkwon014
 *  Partner(s) Name: Bhrayan Escobar
 *	Lab Section:
 *	Assignment: Lab #3  Exercise #1
 *	Exercise Description: Count the number of 1s on ports A and B and output that number on port C.
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
    PORTB = 0xFF;
    PORTC = 0x00;
    unsigned char count, tempA, tempB = 0x00;
    /* Insert your solution below */
    while (1) {
      tempA = PINA;
      tempB = PINB;
      for (unsigned char i = 0; i < 8; i++) {
        count += GetBit(tempA, i) + GetBit(tempB, i);
      }
      PORTC = count;
      count = 0;
    }
    return 1;
}
