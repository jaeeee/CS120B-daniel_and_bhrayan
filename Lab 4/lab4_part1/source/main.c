/*	Author: dkwon014
 *  Partner(s) Name: bhrayan escobar, akshay gulabrao, ramiro carrillo
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #1
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
enum states { START, INIT, WAIT1, SWITCH_LIGHTS, WAIT2 } state;
DDRA = 0x00; DDRB = 0xFF; PORTA = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    while (1) {
switch(states) { //transitions
case START:
state = INIT;
break;
case INIT:
if ((PINA & 0x01) == 1) {
state = WAIT1;
} else {
state = INIT;
}
break;
case WAIT1:
if (PINA == 0) {
state = SWITCH_LIGHTS;
} else {
state = WAIT1;
}
break;
case SWITCH_LIGHTS:
if ((PINA & 0x01) == 1) {
state = WAIT2;
} else {
state = SWITCH_LIGHTS;
}
break;
case WAIT2:
if ((PINA == 0)) {
state = INIT;
} else {
state = WAIT2;
}
break;
}
switch (states) { //actions
case START:
break;
case INIT:
PORTB = 0x01;
break;
case WAIT1:
//nothing
break;
case SWITCH_LIGHTS:
PORTB = 0x02;
break;
case WAIT2:
//nothing
break;
}
    }
    return 1;
}
