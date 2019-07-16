/*	Author: dkwon014
 *  Partner(s) Name: Bhrayan Escobar
 *	Lab Section:
 *	Assignment: Lab #11  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#include "scheduler.h"
#include "keypad.h"
#endif

enum STATES { STATE_OUT };

unsigned char holderB = 0x00;

int tick(int state) {
  unsigned char keypad_input;
  keypad_input = GetKeypadKey();
  switch(state) {
    case STATE_OUT:
    switch(keypad_input) {
      case '\0':
      			holderB = 0x1F;
      			break;
      			case '1':
      			holderB = 0x01;
      			break;
      			case '2':
      			holderB = 0x02;
      			break;
      			case '3':
      			holderB = 0x03;
      			break;
      			case '4':
      			holderB = 0x04;
      			break;
      			case '5':
      			holderB = 0x05;
      			break;
      			case '6':
      			holderB = 0x06;
      			break;
      			case '7':
      			holderB = 0x07;
      			break;
      			case '8':
      			holderB = 0x08;
      			break;
      			case '9':
      			holderB = 0x09;
      			break;
      			case 'A':
      			holderB = 0x0A;
      			break;
      			case 'B':
      			holderB = 0x0B;
      			break;
      			case 'C':
      			holderB = 0x0C;
      			break;
      			case 'D':
      			holderB = 0x0D;
      			break;
      			case '*':
      			holderB = 0x0E;
      			break;
      			case '0':
      			holderB = 0x00;
      			break;
      			case '#':
      			holderB = 0x0F;
      			break;
      			default:
      			holderB = 0x1B;
      			break;
    }
    state = STATE_OUT;
    PORTB = holderB;
    break;
  }
  return state;
}
int main(void) {
    /* Insert DDR and PORT initializations */
    // DDRA = 0xFF; PORTA = 0x00;
    //NEW DDRA
    DDRA = 0xF0; PORTA = 0x0F;
    DDRB = 0xFF; PORTB= 0x00;
    // DDRC = 0xF0; PORTC = 0x0F;
    DDRD = 0xFF; PORTD = 0x00;

    // unsigned long int
    static task task1;
    task *tasks[] = { &task1};
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	   // Task 1
	   task1.state = 0;//Task initial state.
	   task1.period = 2;//Task Period.
	   task1.elapsedTime = 2;//Task current elapsed time.
     task1.TickFct = &tick;//Function pointer for the tick.

	   TimerSet(10);
	   TimerOn();

     unsigned short i; // Scheduler for-loop iterator
   	while(1) {
   		for ( i = 0; i < numTasks; i++ ) {
   			if ( tasks[i]->elapsedTime == tasks[i]->period ) {
   				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
   				tasks[i]->elapsedTime = 0;
   			}
   			tasks[i]->elapsedTime += 1;
   		}
   		while(!TimerFlag);
   		TimerFlag = 0;
   	}
    return 0;
}
