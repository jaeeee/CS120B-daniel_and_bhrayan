/*	Author: dkwon014
 *  Partner(s) Name: Bhrayan Escobar
 *	Lab Section:
 *	Assignment: Lab #3  Exercise #3
 *	Exercise Description: In addition to the above, PA4 is 1 if a key is in the ignition,
 *   PA5 is one if a driver is seated, and PA6 is 1 if the driver's seatbelt is fastened.
 *  PC7 should light a "Fasten seatbelt" icon if a key is in the ignition, the driver is seated, but the belt is not fastened.
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
		unsigned char holder = 0x00;
    /* Insert your solution below */
    while (1) {
			holder = PINA;
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
      lower = PINA & 0x0F; //lower nibble
      upper = PINA & 0xF0; //upper nibble
      if ((GetBit(upper, 4)) && (GetBit(upper, 5)) !(GetBit(upper, 6)) {
        PORTC = PORTC | 0x80;
      }
    }
    return 1;
}
