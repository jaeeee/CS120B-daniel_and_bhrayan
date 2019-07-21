/*	Author: dkwon014
 *  Partner(s) Name:
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
#include <avr/eeprom.h>
#include "io.c"
#endif


//button configuration
/** MENU SELECTION (1-5) **/
#define BUTTON1 (~PINA & 0x01) //up (p1)
#define BUTTON2 (~PINA & 0x02) //down (p1)
#define BUTTON3 (~PINA & 0x04) //up (p2)
#define BUTTON4 (~PINA & 0x08) //down (p2)
#define BUTTON5 (~PINA & 0x10) //reset?

unsigned char highScore;
unsigned char myPlayer; //0x00, 0x01, 0x02, 0x03
unsigned char bestPlayer;

enum STATES { STATE_OUT };

enum MENU_STATES { WAIT, WAIT1, WAIT2, WAIT3, WAIT4, WAIT5, SEL1, SEL2, SEL3, SEL4, SEL5 } ;

int tickMenu(int state) {
  switch(state) {
    case WAIT:
    if (BUTTON1 && !BUTTON2 && !BUTTON3 && !BUTTON4 && !BUTTON5) {
        state = WAIT1;
    } else if (!BUTTON1 && BUTTON2 && !BUTTON3 && !BUTTON4 && !BUTTON5) {
      state = WAIT2;
    } else if (!BUTTON1 && !BUTTON2 && BUTTON3 && !BUTTON4 && !BUTTON5) {
      state = WAIT3;
    } else if (!BUTTON1 && !BUTTON2 && !BUTTON3 && BUTTON4 && !BUTTON5) {
      state = WAIT4;
    } else if (!BUTTON1 && !BUTTON2 && !BUTTON3 && !BUTTON4 && BUTTON5) {
      state = WAIT5;
    } else {
      state = WAIT;
    }
    break;
    case WAIT1:
    if (!BUTTON1) {
      state = SEL1;
    } else {
      state = WAIT1;
    }
    break;
    case WAIT2:
    if (!BUTTON2) {
      state = SEL2;
    } else {
      state = WAIT2;
    }
    break;
    case WAIT3:
    if (!BUTTON3) {
      state = SEL3;
    } else {
      state = WAIT3;
    }
    break;
    case WAIT4:
    if (!BUTTON4) {
      state = SEL4;
    } else {
      state = WAIT4;
    }
    break;
    case WAIT5:
    if (!BUTTON5) {
      state = SEL5;
    } else {
      state = WAIT5;
    }
    break;
    case SEL1:
    //TODO
    break;
    case SEL2:
    //TODO
    break;
    case SEL3:
    //TODO
    break;
    case SEL4:
    //TODO
    break;
    case SEL5:
    //TODO
    break;
  }
  return state;
}

void EEPROM_Write(unsigned char address, unsigned char data)
{
	eeprom_write_byte(address,data);
}

unsigned char EEPROM_Read(unsigned char address)
{
	return eeprom_read_byte(address);
}

// unsigned char readHighScore = eeprom_read_byte(0x01);

void transmit_data(unsigned char data) {
  data = ~data;
	int i;
	for (i = 0; i < 8 ; ++i) {
		// Sets SRCLR to 1 allowing data to be set
		// Also clears SRCLK in preparation of sending data
		// does this mean it sets SRCLK low?
		// does this set RCLK low?
		PORTB = 0x08;
		// set SER = next bit of data to be sent.
		PORTB |= ((data >> i) & 0x01);
		// set SRCLK = 1. Rising edge shifts next bit of data into the shift register
		PORTB |= 0x02;
	}
	// set RCLK = 1. Rising edge copies data from “Shift” register to “Storage” register
	PORTB |= 0x04;
	// clears all lines in preparation of a new transmission
	PORTA = 0x00;
}

// void transmit_data (unsigned char data) {
//     /* BOT_SR uses A0 - A3  -- controls  GREEN (x), use '~' on data */
//     // if (SR == BOT_SR) {
//         // data = ~data;
//         for (int i = 7; i >= 0; --i) {
//             // Sets SRCLR to 1 allowing data to be set
//             // Also clears SRCLK in preparation of sending data
//             PORTA &= 0xF8; PORTA |= 0x08;
//             // set SER = next bit of data to be sent.
//             PORTA |= ((data >> i) & 0x01);
//             // set SRCLK = 1. Rising edge shifts next bit of data into the shift register
//             PORTA |= 0x04;
//         }
//         // set RCLK = 1. Rising edge copies data from the “Shift” register to the “Storage” register
//         PORTA |= 0x02;
//         // clears all lines in preparation of a new transmission
//         PORTA &= 0xF0;
//     }
//
// //A4-A7
//     void transmit_data2(unsigned char data) {
//       data = ~data;
//       for (int i = 7; i >= 0; --i) {
//           // Sets SRCLR to 1 allowing data to be set
//           // Also clears SRCLK in preparation of sending data
//           PORTA &= 0x8F; PORTA |= 0x80;
//           // set SER = next bit of data to be sent.
//           PORTA |= ((data >> i) & 0x01) << 4;
//           // set SRCLK = 1. Rising edge shifts next bit of data into the shift register
//           PORTA |= 0x40;
//       }
//       // set RCLK = 1. Rising edge copies data from the “Shift” register to the “Storage” register
//       PORTA |= 0x20;
//       // clears all lines in preparation of a new transmission
//       PORTA &= 0x0F;
//     }

// void transmit_data(unsigned char data) {
// 	int i;
// 	for (i = 7; i >= 0 ; --i) {
// 		// Sets SRCLR to 1 allowing data to be set
// 		// Also clears SRCLK in preparation of sending data
// 		PORTA = 0x08;
// 		// set SER = next bit of data to be sent.
// 		PORTA |= ((data >> i) & 0x01);
// 		// set SRCLK = 1. Rising edge shifts next bit of data into the shift register
// 		PORTA |= 0x04;
// 	}
//
// 	// set RCLK = 1. Rising edge copies data from the “Shift” register to the “Storage” register
// 	PORTA |= 0x02;
// 	// clears all lines in preparation of a new transmission
// 	PORTA = 0x00;
// }

int tick(int state) {
  switch(state) {
    case STATE_OUT:
        EEPROM_Write(0x01, 7); //write highscore
        EEPROM_Write(0x00, 0); //write top player
        // sendMenu();
    PORTA = 0xFF;
    transmit_data(0x00);
    // PORTA = 0xFF;
    // transmit_data(0x2E);
    // transmit_data2(0x38);
    break;
  }
  return state;
}

void sendMenu() {
  LCD_init();
  LCD_ClearScreen();
  LCD_DisplayString(18, "highscore: ");
  LCD_Cursor(29);
  // EEPROM_Write(0x01, 5);
  highScore = EEPROM_Read(0x01);
  bestPlayer = EEPROM_Read(0x00);
  LCD_WriteData(('0' + highScore));
  LCD_Cursor(31);
  LCD_WriteData(bestPlayer);
  //load acharacters
  LCD_createChar(0, player1);
  LCD_createChar(1, player2);
  LCD_createChar(3, player4);
  LCD_Cursor(7);
  LCD_WriteData(0x00);
  LCD_WriteData(0x01);
  LCD_WriteData(0x02);
  LCD_WriteData(0x03);
}

// #define A1 (~PINA & 0x01)
int main(void) {
    // DDRA = 0x03;
        DDRB = 0xFF; PORTB = 0x00;
        // DDRA = 0x03; PORTA = 0xFC; //KEYPAD AS keypad_input
        DDRA = 0xFF; PORTA = 0x00;
      	DDRC = 0xFF; PORTC = 0x00;
        DDRD = 0xFF; PORTD = 0x00;  //ORIGINAL
        // DDRD = 0x40; PORTD = 0xBF;
    // PORTA &= ~(1 << LATCH) & ~(1 << CLOCK); //sets latch and clock low

    static task task1;
    task *tasks[] = { &task1};
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

    // PORTA = 0x3F;
    // PORTB = 0xFF;
	   // Task 1
	   task1.state = 0;//Task initial state.
	   task1.period = 30;//Task Period.
	   task1.elapsedTime = 10;//Task current elapsed time.
     task1.TickFct = &tick;//Function pointer for the tick.

	   TimerSet(10);
	   TimerOn();
     // LCD_init();
     sendMenu();
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
