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
#include "io.c"
#endif

enum STATES { STATE_OUT, BUTTON_PRESSED };

unsigned char holderB;
unsigned char flag;
unsigned char saved;
int tick(int state) {
  unsigned char keypad_input;
  keypad_input = GetKeypadKey();
  switch(state) {
    case STATE_OUT:
    // if (flag && keypad_input == NULL) {
    //   LCD_Cursor(1);
    //   LCD_WriteData(holderB + '0');
    // }
    if (flag == 0) {
      			holderB = 0x1F;
            // flag = 1;
            // LCD_WriteData
            LCD_Cursor(1);
            LCD_WriteData(holderB + '0');
    }
    switch(keypad_input) {
      // case '\0':
      // 			// holderB = 0x1F;
      //       flag = 1;
      //       // LCD_WriteData
      //       LCD_Cursor(1);
      //       LCD_WriteData(holderB + '0');
      // 			break;
      			case '1':
            flag = 1;
      			holderB = 0x01;
            LCD_Cursor(1);
            LCD_WriteData(holderB + '0');
      			break;
      			case '2':
            flag = 1;
      			holderB = 0x02;
            LCD_Cursor(1);
            LCD_WriteData(holderB + '0');
      			break;
      			case '3':
            flag = 1;
      			holderB = 0x03;
            LCD_Cursor(1);
            LCD_WriteData(holderB + '0');
      			break;
      			case '4':
            flag = 1;
      			holderB = 0x04;
            LCD_Cursor(1);
            LCD_WriteData(holderB + '0');
      			break;
      			case '5':
      			holderB = 0x05;
            LCD_Cursor(1);
            LCD_WriteData(holderB + '0');
      			break;
      			case '6':
            flag = 1;
      			holderB = 0x06;
            LCD_Cursor(1);
            LCD_WriteData(holderB + '0');
      			break;
      			case '7':
            flag = 1;
      			holderB = 0x07;
            LCD_Cursor(1);
            LCD_WriteData(holderB + '0');
      			break;
      			case '8':
            flag = 1;
      			holderB = 0x08;
            LCD_Cursor(1);
            LCD_WriteData(holderB + '0');
      			break;
      			case '9':
            flag = 1;
      			holderB = 0x09;
            LCD_Cursor(1);
            LCD_WriteData(holderB + '0');
      			break;
      			case 'A':
            flag = 2;
      			holderB = 0x0A;
            LCD_Cursor(1);
            LCD_WriteData(holderB + 0x37);
      			break;
      			case 'B':
            flag = 2;
      			holderB = 0x0B;
            LCD_Cursor(1);
            LCD_WriteData(holderB + 0x37);
      			break;
      			case 'C':
            flag = 2;
      			holderB = 0x0C;
            LCD_Cursor(1);
            LCD_WriteData(holderB + 0x37);
      			break;
      			case 'D':
            flag = 2;
      			holderB = 0x0D;
            LCD_Cursor(1);
            LCD_WriteData(holderB + 0x37);
      			break;
      			case '*':
            flag = 3;
      			holderB = 0x0E;
            LCD_Cursor(1);
            LCD_WriteData(holderB + 0x1C);
      			break;
      			case '0':
            flag = 1;
      			holderB = 0x00;
            LCD_Cursor(1);
            LCD_WriteData(holderB + '0');
      			break;
      			case '#':
            flag = 4;
      			holderB = 0x0F;
            LCD_Cursor(1);
            LCD_WriteData(holderB + 0x14);
      			break;
      			default:
      			// holderB = 0x1B;
            // LCD_Cursor(1);
            // LCD_WriteData(holderB + '0');
      			break;
    }
    state = BUTTON_PRESSED;
    PORTB = holderB;
    // holderB = PORTB;
    saved = holderB;
    break;
    case BUTTON_PRESSED:
    LCD_Cursor(1);
    switch(flag) {
      case 1:
      LCD_WriteData(saved + '0');
      break;
      case 2:
      LCD_WriteData(saved + 0x37);
      break;
      case 3:
      LCD_WriteData(saved + 0x1C);
      break;
      case 4:
      LCD_WriteData(saved + 0x14);
      break;
    }
    // LCD_Cursor(1);
    // LCD_WriteData(saved + '0');
    // LCD_WriteData(holderB + '0');
    if (keypad_input != NULL) {
      state = STATE_OUT;
    } else {
      state = BUTTON_PRESSED;
    }
    // state =
    break;
  }
  // flag;
  // if (PORTB != 0x00) {
    // flag = 1;
  // }
  return state;
}
int main(void) {
    /* Insert DDR and PORT initializations */
    // DDRA = 0xFF; PORTA = 0x00;
    //NEW DDRA
    DDRB = 0xFF; PORTB = 0x00;
    DDRA = 0xF0; PORTA = 0x0F;
  	// DDRC = 0xF0; PORTC = 0x0F; // PC7..4 outputs init 0s, PC3..0 inputs init 1s
  	DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    // unsigned long int
    static task task1;
    task *tasks[] = { &task1};
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	   // Task 1
	   task1.state = 0;//Task initial state.
	   task1.period = 10;//Task Period.
	   task1.elapsedTime = 10;//Task current elapsed time.
     task1.TickFct = &tick;//Function pointer for the tick.

	   TimerSet(10);
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
      // LCD_Cursor(1);
      // LCD_WriteData(holderB + '0');
   		while(!TimerFlag);
   		TimerFlag = 0;
   	}
    return 0;
}
