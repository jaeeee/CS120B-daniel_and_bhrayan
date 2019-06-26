/*	Author: dkwon014
 *  Partner(s) Name: Bhrayan Escobar
 *	Lab Section:
 *	Assignment: Lab #2 Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

 #include <avr/io.h>
 #ifdef _SIMLATE_
 #include "simAVRHeader.h"
 #endif


 int main(void) {
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRB = 0xFF;
    PORTB = 0x00;
    unsigned char tmp1 = 0x00;
    unsigned char tmp2 = 0x00;
    unsigned char tmp3 = 0x00;
    while (1)
    {
 	   tmp1 = PINA & 0x01;
 	   tmp2 = PINA & 0x02;
 	   if( tmp1 == 0x01 && tmp2 == 0x00)
 	   {
 		   tmp3 = (tmp3 & 0xFE) | 0x01;
 	   }
 	   else
 	   {
 		   tmp3 = (tmp3 & 0xFE) | 0x00;
 	   }
 	   PORTB = tmp3;
   }
 // }
 	return 1;
 }
