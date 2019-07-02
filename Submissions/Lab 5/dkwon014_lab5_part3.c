/*	Author: dkwon014
 *  Partner(s) Name: Bhrayan Escobar
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

unsigned char holder = 0x00;

#define A0 (~PINA & 0x01)
#define A1 (~PINA & 0x02)
#define output PORTC
enum STATES{ START, INIT, WAIT1, SET1, WAIT2, SET2, WAIT3, SET3, WAIT4, SET4, WAIT5, WAIT6, SET5} state;

void tick() {
  switch(state) { //transitions
    case START:
    state = INIT;
    break;
    case INIT:
    if (A0) {
      state = WAIT1;
    } else {
      state = INIT;
    }
    // }    state = WAIT1;
    break;
    case WAIT1:
    if (!A0) {
      state = SET1;
    } else {
      state = WAIT1;
    }
    break;
    case SET1:
    if (A0) {
      state = WAIT2;
    } else {
      state = SET1;
    }
    break;
    case WAIT2:
    if (!A0) {
      state = SET2;
    } else {
      state = WAIT2;
    }
    break;
    case SET2:
    if (A0) {
      state = WAIT3;
    } else {
      state = SET2;
    }
    break;
    //
    case WAIT3:
    if (!A0) {
      state = SET3;
    } else {
      state = WAIT3;
    }
    break;
    case SET3:
    if (A0) {
      state = WAIT4;
    } else {
      state = SET3;
    }
    break;
    case WAIT4:
    if (!A0) {
      state = SET4;
    } else {
      state = WAIT4;
    }
    break;
    case SET4:
    if (A0) {
      state = WAIT5;
    } else {
      state = SET4;
    }
    break;
    case WAIT5:
    if (!A0) {
      state = SET5;
    } else {
      state = WAIT5;
    }
    break;
    case SET5:
    if (A0) {
    state = WAIT6;
  } else {
    state = SET5;
  }
    break;
    case WAIT6:
    if (!A0) {
    state = INIT;
  } else {
    state = WAIT6;
  }
    break;
  }
  switch (state) { //actions
    // enum STATES{ START, INIT, WAIT1, SET1, WAIT2, SET2, WAIT3, SET3, WAIT4, SET4, WAIT5, WAIT6, SET5} state;
    case START:
    break;
    case INIT:
    output = 0x00;
      break;
    case WAIT1:
      break;
    case SET1:
    output = 0x15;
      break;
    case WAIT2:
  break;
    case SET2:
output = 0x29;
  break;
    case WAIT3:
  break;
    case SET3:
    output = 0x33;
  break;
    case WAIT4:
  break;
    case SET4:
    output = 0x0C;
  break;
    case WAIT5:
  break;
    case SET5:
    output = 0x2D;
  break;
    case WAIT6:
  break;

  }
}


int main(void) {
    DDRA = 0x00; DDRC = 0xFF;
    PORTA = 0xFF; PORTC = 0x00;
    /* Insert DDR and PORT initializations */
    /* Insert your solution below */
    while (1) {
      tick();
    }
    return 1;
}
