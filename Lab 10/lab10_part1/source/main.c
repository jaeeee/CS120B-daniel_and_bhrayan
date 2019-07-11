/*	Author: dkwon014
 *  Partner(s) Name: Bhrayan Escobar
 *	Lab Section:
 *	Assignment: Lab #6 Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <timer.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum STATES { START, LIGHT_1, LIGHT_2, LIGHT_3 } state;
enum STATES_2 { START, ON, OFF } state2;
unsigned char output = 0x00;
unsigned char output2 = 0x00;

void tick() {
  switch(state) {
    case START:
    state = LIGHT_1;
    break;
    case LIGHT_1:
    state = LIGHT_2;
    break;
    case LIGHT_2:
    state = LIGHT_3;
    break;
    case LIGHT_3:
    state = LIGHT_1;
    break;
  }
  switch(state) {
    case START:
    break;
    case LIGHT_1:
    output = 0x01;
    break;
    case LIGHT_2:
    output = 0x02;
    break;
    case LIGHT_3:
    output = 0x04;
    break;
  }
}

void tick2() {
  switch(state2) {
    case START:
    state2 = ON;
    break;
    case ON:
    state2 = OFF;
    break;
    case OFF:
    state2 = ON;
    break;
  }
  switch(state) {
    case START:
    break;
    case ON:
    output2 = 0x08;
    break;
    case OFF:
    break;
  }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRC = 0xFF;
    PORTC = 0x00;
    TimerSet(1000); //set timer here
    TimerOn(); //turn on timer
    state = START; //change to START state
    state2 = START;
    // tick();
    // whil
    /* Insert your solution below */
    while (1) {
      tick();
      tick2();
      while (!TimerFlag) {

      }
      TimerFlag = 0;
            PORTC = output | output2;
    }
    return 1;
}
