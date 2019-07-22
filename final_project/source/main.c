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
#include <util/delay.h>
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
#define F_CPU 1000000UL
#define BUTTON1 (~PIND & 0x01) //up (p1)
#define BUTTON2 (~PIND & 0x02) //down (p1)
#define BUTTON3 (~PINA & 0x04) //up (p2)
#define BUTTON4 (~PINA & 0x08) //down (p2)
#define BUTTON5 (~PINA & 0x10) //reset?

unsigned char highScore;
unsigned char myPlayer; //0x00, 0x01, 0x02, 0x03
unsigned char bestPlayer;
unsigned char playerX = 0;
unsigned char playerY = 0;
unsigned char currentDirection = 1;
unsigned char gameState; //status of the game
unsigned char mousePos;
unsigned char score;

/**
GAME DATA (MATRIX)
ROWS[1] and COLUMNS[1] designated for player
ROWS[0] and COLUMNS[0] designated for BOT
**/
unsigned char ROWS[2];

unsigned char COLUMNS[2];

unsigned char FALLING_SEQUENCE[8] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };

enum STATES { STATE_OUT };

enum MENU_STATES { START, WAIT1, INC, WAIT2, START_GAME } m_state;

void menu_tick() {
  switch(m_state) { //transitions
    case START:
    if (BUTTON2 && !BUTTON1) {
      m_state = WAIT1;
    }
    else if (!BUTTON2 && BUTTON1) {
      m_state = WAIT2;
    } else {
      m_state = START;
    }
    break;
    case WAIT1:
    if (!BUTTON2) {
      m_state = INC;
    } else {
      m_state = WAIT1;
    }
    break;
    case INC:
    m_state = START;
    break;
    case WAIT2:
    if (!BUTTON1) {
      m_state = START_GAME;
    } else {
      m_state = WAIT2;
    }
    break;
    case START_GAME:
    // gameState = 0x01;
    if (gameState == 0x01) {
      m_state = START_GAME;
    } else {
      m_state = START;
    }
    break;
  }
  switch(m_state) { //actions
    case START:
    EEPROM_Write(0x01, 7); //write highscore
    EEPROM_Write(0x00, 0); //write top player
    // sendMenu();
    break;
    case WAIT1:
    break;
    case INC:
    if (mousePos < 10) {
      mousePos++;
    } else {
      mousePos = 7;
    }
    sendMenu();
    // mousePos++;
    break;
    case WAIT2:
    break;
    case START_GAME:
    gameState = 0x01;
    switch(mousePos) {
      case 7:
      myPlayer = 0x00;
      break;
      case 8:
      myPlayer = 0x01;
      break;
      case 9:
      myPlayer = 0x02;
      break;
      case 10:
      myPlayer = 0x04;
      break;
    }
        sendInGame();
    break;
  }
}

void EEPROM_Write(unsigned char address, unsigned char data)
{
	eeprom_write_byte(address,data);
}

unsigned char EEPROM_Read(unsigned char address)
{
	return eeprom_read_byte(address);
}

void displayLEDMatrix() { //updates the matrix?
  for (int i = 0; i < 2; i++) {
    _delay_us(500);
    PORTA = ROWS[i];
    PORTB = COLUMNS[i];
  }
}

void printPos() {
  LCD_init();
  LCD_ClearScreen();
  LCD_DisplayString(18, "curentY: ");
  LCD_Cursor(29);
  LCD_WriteData(('0' + playerY));
  LCD_Cursor(31);
}

int tick(int state) {
  switch(state) {
    case STATE_OUT:
    updateMatrixSingle(playerX, playerY);
      if(BUTTON1) { //left
        moveCharacter(1);
        // printPos();
      }
      if (BUTTON2) { //right
        moveCharacter(0);
        // printPos();
      }
            // updateMatrixSingle(playerX, playerY);
      // moveCharacter(1);
    break;
  }
  return state;
}

//updates PLAYER
void updateMatrixSingle(unsigned char x, unsigned char y) {
  if (currentDirection == 1) {
  y = ROW_VALUES[y] + ROW_VALUES[y+1];
} else {
  y = ROW_VALUES[y-1] + ROW_VALUES[y];
}
  // x = HEX_VALUES[x];
  unsigned char convertedY = ~y;
  // unsigned char hexVal1, unsigned char hexVal2;
  ROWS[1] = x;
  COLUMNS[1] = convertedY;
  // ROWS[0] = 0x80;
  // COLUMNS[0] = ~0x80;
}


void moveCharacter(unsigned char pos) {
switch(pos) {
  case 0:
  if (playerY > 0) {
    playerY--;
  }
  // else {
  //   // currentDirection = 1;
  //   // moveCharacter(1);
  // }
  break;
  case 1: //move right
  if (playerY < 6) {
    playerY++;
  }
  // else {
  //   // currentDirection = 0;
  //   // moveCharacter(0);
  // }
  break;
}
updateMatrixSingle(playerX, playerY);
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
  LCD_Cursor(mousePos); //cursor pos
}

void sendInGame() {
  LCD_init();
  LCD_ClearScreen();
  LCD_DisplayString(1, "Score");
  LCD_DisplayString(21, "Player: ");
  LCD_Cursor(28);
  LCD_WriteData(myPlayer);
  LCD_Cursor(30);
  LCD_Cursor(1);
  LCD_WriteData('0' + score);
}

int main(void) {
  DDRA = 0xFF; PORTD = 0x00;
  DDRB = 0xFF; PORTB = 0x00;
  DDRC = 0xFF; PORTC = 0x00;
  DDRD = 0xC0; PORTD = 0x7F;
    static task task1;
    task *tasks[] = { &task1};
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	   task1.state = 0;//Task initial state.
	   task1.period = 10;//Task Period.
	   task1.elapsedTime = 10;//Task current elapsed time.
     task1.TickFct = &tick;//Function pointer for the tick.
              mousePos = 7;
	   TimerSet(30);
	   TimerOn();
     sendMenu();
     unsigned short i; // Scheduler for-loop iterator
     playerX = 1;
     playerY = 0;
         // PORTB = 0x10;
         m_state = START;
         PORTA = 0xFF;
   	while(1) {
      if (gameState == 0x00) { //game not going on rn
             // sendMenu();
             menu_tick();
      }
      if (gameState == 0x01) { //playing
      displayLEDMatrix();
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
  }
    return 0;
}
