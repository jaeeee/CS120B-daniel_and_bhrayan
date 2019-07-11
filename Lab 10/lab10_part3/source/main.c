/*	Author: dkwon014
 *  Partner(s) Name: Bhrayan Escobar
 *	Lab Section:
 *	Assignment: Lab #10 Exercise #3
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

#define A2 (PINA & 0x04)

enum STATES { START, LIGHT_1, LIGHT_2, LIGHT_3 } state;
enum STATES_2 { START2, ON2, OFF2 } state2;
// enum STATES_3 { START3, COMBINE } state3;
enum STATES_3 { START3, OFF3, ON3 } state3;

unsigned char output = 0x00;
unsigned char output2 = 0x00;
unsigned char cnt;

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
    case START2:
    state2 = OFF2;
    break;
    case ON2:
  state2 = OFF2;
    break;
    case OFF2:
    state2 = ON2;
    break;
  }
  switch(state2) {
    case START2:
    output2 = 0x00;
    break;
    case ON2:
    output2 = 0x08;
    break;
    case OFF2:
    output2 = 0x00;
    break;
  }
}

void tick3() {
  switch(state3) {
    case START3:
    state3 = OFF3;
    break;
    case OFF3:
    cnt = 0;
    if (A2) {
    state3 = ON3;
  } else {
    state3 = OFF3;
  }
    break;
    case ON3:
    if (A2 && cnt < 2) {
    state3 = ON3;
  } else {
    cnt++
    state3 = OFF3;
  }
    break;
  }
  switch(state3) {
    case START3:
    // state3 = OFF3;
    break;
    case OFF3:
    PORTC = 0x00 | output2 | output;
    // state3 = ON3;
    break;
    case ON3:
    PORTC = 0x10 | output2 | output;
    break;
  }
}
//
// void tick3() {
//   switch(state3) {
//     case START3:
//     state3 = COMBINE;
//     break;
//     case COMBINE:
//     state3 = COMBINE;
//     break;
//   }
//   switch(state3) {
//     case START3:
//     PORTC = 0x00;
//     break;
//     case COMBINE:
//     PORTC = output2 | output;
//     break;
//   }
// }




int main(void) {
    /* Insert DDR and PORT initializations */
    DDRC = 0xFF;
    PORTC = 0x00;
    unsigned long BLINK_TIMER = 300;
    unsigned long FLASH_TIMER = 1000;
    unsigned long BUTTON_TIMER = 2;
    unsigned long PERIOD = 1;
    TimerSet(PERIOD); //set timer here
    TimerOn(); //turn on timer
    state = START; //change to START state
    state2 = START2;
    state3 = START3;
    // tick();
    // whil
    /* Insert your solution below */
    while (1) {
      if (BLINK_TIMER >= 300) {
      tick();
      BLINK_TIMER = 0;
    }
    if (FLASH_TIMER >= 1000) {
      tick2();
      FLASH_TIMER = 0;
    }
    if (BUTTON_TIMER >= 2) {
      tick3();
      BUTTON_TIMER = 0;
    }
      // tick3();
      // PORTC = output | output2;
      while (!TimerFlag) {

      }
      TimerFlag = 0;
      BLINK_TIMER += PERIOD;
      FLASH_TIMER += PERIOD;
      BUTTON_TIMER += PERIOD;
    }
    return 1;
}
