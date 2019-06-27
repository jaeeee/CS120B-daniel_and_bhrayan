/*	Author: agula002
 *  Partner(s) Name: brayan escobar daniel kwong ramiro carillo
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

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRD = 0x00;
	DDRB = 0xFE;
	PORTD = 0x00;
	PORTB = 0x00;
    /* Insert your solution below */
    unsigned long weight = 0;
    
    while (1) {
		weight = PIND + PINB;
		if(weight >= 70){
			PORTB = 0x02;
		}
		else if(weight > 5){
			PORTB = 0x04;
		}
		else{
			PORTB = 0x00;
		}
    }
    
    return 1;
}
