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
