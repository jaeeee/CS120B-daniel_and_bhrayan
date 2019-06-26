/*	Author: dkwon014
 *  Partner(s) Name: Bhrayan Escobar
 *	Lab Section:
 *	Assignment: Lab #3  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;
    DDRB = 0x00;
    DDRC = 0xFF;
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
