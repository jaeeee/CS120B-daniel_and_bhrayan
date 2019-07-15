/*	Author: dkwon014
 *  Partner(s) Name: Bhrayan Escobar
 *	Lab Section:
 *	Assignment: Lab #10 Exercise #4
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

#define A0 (~PINA & 0x01)
#define A1 (~PINA & 0x02)
#define A2 (~PINA & 0x04)

enum STATES { START, LIGHT_1, LIGHT_2, LIGHT_3 } state;
enum STATES_2 { START2, ON2, OFF2 } state2;
// enum STATES_3 { START3, COMBINE } state3;
enum STATES_3 { START3, OFF3, ON3 } state3;
enum STATES_4 { START4, WAIT4, UP4, WAITUP4, DOWN4, WAITDOWN4 } state4;
const double NOTES[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
unsigned char output = 0x00;
unsigned char output2 = 0x00;
unsigned char cnt;
unsigned char i;


void set_PWM(double frequency) {
  static double current_frequency;
  if (frequency != current_frequency) {
    if (!frequency) { TCCR3B &= 0x08; }
    else { TCCR3B |= 0x03; }
    if (frequency < 0.954) { OCR3A = 0xFFFF; }
    else if (frequency > 31250) { OCR3A = 0x0000; }
    else { OCR3A = (short) (8000000 / (128 * frequency)) - 1; }
    TCNT3 = 0;
    current_frequency = frequency;
  }
}

void PWM_on() {
  TCCR3A = (1 << COM3A0);
  TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
  set_PWM(0);
}

void PWM_off() {
  TCCR3A = 0x00;
  TCCR3B = 0x00;
}

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
    cnt++;
    state3 = OFF3;
  }
    break;
  }
  switch(state3) {
    case START3:
    // state3 = OFF3;
    break;
    case OFF3:
		set_PWM(0);
    PORTB = output2 | output;
    // PORTB = 0x00 | output2 | output;
    // state3 = ON3;
    break;
    case ON3:
    set_PWM(NOTES[i]);
    PORTB = output2 | output;
    // PORTB = 0x10 | output2 | output;
    break;
  }
}

// enum STATES_4 { START4, WAIT4, UP4, WAITUP4, DOWN4, WAITDOWN4 } state4;
void tick4() {
switch(state4) {
  case START4:
  state4 = WAIT4;
  break;
  case WAIT4:
  if (A0) {
    state4 = WAITUP4;
  } else if (A1) {
    state4 = WAITDOWN4;
  } else {
    state4 = WAIT4;
  }
  break;
  case UP4:
  state4 = WAIT4;
  break;
  case WAITUP4:
  if (A0) {
    state4 = WAITUP4;
  } else {
    state4 = UP4;
  }
  break;
  case DOWN4:
  // if (A1) {
    // state4
  // }
  state4 = WAIT4;
  break;
  case WAITDOWN4:
  if (A1) {
    state4 = WAITDOWN4;
  } else {
    state4 = DOWN4;
  }
  break;
}
switch(state4) {
  case START4:
  i = 0;
  break;
  case WAIT4:
  break;
  case UP4:
  if (i < 7) {
    i++;
  }
  break;
  case WAITUP4:
  break;
  case DOWN4:
  if (i > 0) {
    i--;
  }
  break;
  case WAITDOWN4:
  break;
}
}


int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF;
    PORTB = 0x00;
    unsigned long BLINK_TIMER = 300;
    unsigned long FLASH_TIMER = 1000;
    unsigned long BUTTON_TIMER = 2;
    unsigned long PERIOD = 1;
    TimerSet(PERIOD); //set timer here
    TimerOn(); //turn on timer
    PWM_on();
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
      tick4();
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
