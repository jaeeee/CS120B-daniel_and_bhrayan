/*	Author: dkwon014
 *  Partner(s) Name: Bhrayan Escobar
 *	Lab Section:
 *	Assignment: Lab #11  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#ifdef _SIMULATE_
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "io.c"
#include "keypad.h"
#include "scheduler.h"
// #include "./.."
// #include "io.h"
// #include "simAVRHeader.h"
// #include "timer.h"
// #include "scheduler.h"
// #include "keypad.h"
#endif

enum STATES { STATE_OUT };

unsigned char holderB = 0x00;
unsigned char i;
const unsigned char bruh[10] = {'i', 'l', 'o', 'v', 'e', ',', ',', ',' ,'C', 'S'};

int tick(int state) {
  // unsigned char keypad_input;
  // keypad_input = GetKeypadKey();
  switch(state) {
    case STATE_OUT:
    // for (i = 1; i < 10; i++) {
      // LCD_Cursor(i);
      LCD_ClearScreen();
      LCD_Cursor(1);
      LCD_DisplayString(1, "HELLO WORLD!!");
    // }
    break;
    }
  return state;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0xFF; PORTA = 0x00;
    DDRB = 0xFF; PORTB= 0x00;
    DDRC = 0xF0; PORTC = 0x0F;
    DDRD = 0xFF; PORTD = 0x00;

    // unsigned long int
    static task task1;
    task *tasks[] = { &task1};
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	   // Task 1
	   task1.state = 0;//Task initial state.
	   task1.period = 200;//Task Period.
	   task1.elapsedTime = 200;//Task current elapsed time.
     task1.TickFct = &tick;//Function pointer for the tick.

	   TimerSet(1);
	   TimerOn();
     LCD_init();

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
