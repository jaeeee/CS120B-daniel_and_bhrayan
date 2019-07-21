/*	Author: dkwon014
 *  Partner(s) Name: Bhrayan Escobar
 *	Lab Section:
 *	Assignment: FINAL PROJECT
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
// #include "snes_controller.h"
#include "io.c"
#endif

unsigned char player1[8] = {
  0x1F,
  0x1F,
  0x15,
  0x1F,
  0x00,
  0x1F,
  0x1F,
  0x1F
};

unsigned char player2[8] = {
  0x11,
    0x0A,
    0x04,
    0x0E,
    0x00,
    0x0A,
    0x00,
    0x0A
};

unsigned char player3[8] = {
  0x04,
  0x04,
  0x11,
  0x00,
  0x1F,
  0x00,
  0x15,
  0x04
};

unsigned char player4[8] = {
  0x11,
  0x09,
  0x04,
  0x02,
  0x05,
  0x0A,
  0x11,
  0x00
};

enum STATES { STATE_OUT };

int tick(int state) {
  switch(state) {
    case STATE_OUT:
    // PORTA--;
    if (PORTA == 0) {
      PORTA = 0xFF;
    }
    // if (PORTB == 0) {
    //   PORTB = 0xFF;
    // }
    // PORTA = PORTA >> 1;
    // PORTB = PORTB << 1;
    break;
  }
  return state;
}

// #define A1 (~PINA & 0x01)
int main(void) {
    // DDRA = 0x03;
        DDRB = 0x00; PORTB = 0xFF;
        // DDRA = 0x03; PORTA = 0xFC; //KEYPAD AS keypad_input
        DDRA = 0xFF; PORTA = 0x00;
      	DDRC = 0xFF; PORTC = 0x00;
        DDRD = 0xFF; PORTD = 0x00;  //ORIGINAL
        // DDRD = 0x40; PORTD = 0xBF;
    // PORTA &= ~(1 << LATCH) & ~(1 << CLOCK); //sets latch and clock low
    LCD_init();
    LCD_DisplayString(18, "Let's get it");
    //load acharacters
    LCD_createChar(0, player1);
    LCD_createChar(1, player2);
    LCD_createChar(3, player4);
    LCD_Cursor(7);
    LCD_WriteData(0x00);
    LCD_WriteData(0x01);
    LCD_WriteData(0x02);
    LCD_WriteData(0x03);
    static task task1;
    task *tasks[] = { &task1};
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

    PORTA = 0xFF;
    // PORTB = 0xFF;
	   // Task 1
	   task1.state = 0;//Task initial state.
	   task1.period = 30;//Task Period.
	   task1.elapsedTime = 10;//Task current elapsed time.
     task1.TickFct = &tick;//Function pointer for the tick.

	   TimerSet(10);
	   TimerOn();
     // LCD_init();

     unsigned short i; // Scheduler for-loop iterator
   	// while(1) {
   	// 	for ( i = 0; i < numTasks; i++ ) {
   	// 		if ( tasks[i]->elapsedTime == tasks[i]->period ) {
   	// 			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
   	// 			tasks[i]->elapsedTime = 0;
   	// 		}
   	// 		tasks[i]->elapsedTime += 1;
   	// 	}
    //   // LCD_Cursor(1);
    //   // LCD_WriteData(holderB + '0');
   	// 	while(!TimerFlag);
   	// 	TimerFlag = 0;
   	// }
    return 0;
}
