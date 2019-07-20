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

unsigned char customChar[8] = {
  0x1F,
   0x0E,
   0x04,
   0x04,
   0x04,
   0x00,
   0x00,
   0x00
};

// #define A1 (~PINA & 0x01)
int main(void) {
    // DDRA = 0x03;
        DDRB = 0xFF; PORTB = 0x00;
        DDRA = 0x03; PORTA = 0xFC;
      	DDRC = 0xFF; PORTC = 0x00;
        DDRD = 0xFF; PORTD = 0x00;
     // DDRD = 0xFF; PORTD = 0x00;
    // PORTA &= ~(1 << LATCH) & ~(1 << CLOCK); //sets latch and clock low
    LCD_init();
         // LCD_DisplayString(1, "huh");
    while(1) {
      // unsigned char keypad_input;
      // keypad_input = GetKeypadKey();
	    // if (keypad_input == '1') {
      //   LCD_DisplayString(1, "you pressed 1 bro");
      // } else {
      //   LCD_DisplayString(1, "waiting");
      // }
      LCD_CreateCustom(1, customChar);
	    delay_ms(1000); //<-- change this delay
	    //Display results here!
      // PORTC = holder;
      // holder++;
      // LCD_WriteData(holder + '0');
    }
}


// int main(void) {
//     DDRB = 0xFF; PORTB = 0x00;
//     DDRA = 0xF0; PORTA = 0x0F;
//   	DDRC = 0xFF; PORTC = 0x00;
//     DDRD = 0xFF; PORTD = 0x00;
//      LCD_init();
//        LCD_DisplayString(1, "Hello world!");
//      while(1) {
//        // if(START) {
//        //   LCD_DisplayString(1, "WTF YOU HIT START!");
//        // }
//        // LCD_DisplayString(1, "Hello world!");
//        continue;
//      }
    // return 0;
// }
