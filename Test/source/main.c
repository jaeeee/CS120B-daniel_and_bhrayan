/*	Author: dkwon014
 *  Partner(s) Name: Bhrayan Escobar
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif



 enum STATES { START, INIT, STEP_1, STEP_2, STEP_3, OPEN} state;
	//unsigned char holder = 0x00;


    void tick(){

    switch(state) {
    case START:
    state = INIT;
    break;

        case INIT:
        
            if( PINA == 1){
                state= STEP_1;
            }
            else{
                state= INIT;
            }
           break;

        case STEP_1:
          if(PINA == 1){
              state= STEP_1;
          }
            else if(PINA == 0){
                state= STEP_2;
            }
            else{
                state= INIT;
            }
            break;

        case STEP_2:
            if (PINA == 0){
                state= STEP_2;
            }
            else if(PINA == 2){
                state =STEP_3;
            }
            else {
                state= INIT;
            }
            break;

        case STEP_3:
            if ( PINA == 2){
                state = STEP_3;
            }
            else if (PINA == 0){
                state= OPEN;
            }
            else{
                state = INIT;
            }
            break;

        case OPEN:
            if ( PINA == 0x80){
                state= INIT;
            }
            else{
                state = OPEN;
            }
            break;
    }

    switch(state) {
    case START:
    break;
    case INIT:
            PORTB= 0x00;
    break;

        case STEP_1:
            break;
        case STEP_2:
            break;
        case STEP_3:
            break;
        case OPEN:
            PORTB=0x01;
            break;

    }
    }
int main(void) {
    /* Insert DDR and PORT initializations */
DDRA= 0xFF; PORTA=0x00;
DDRB= 0x00; PORTB = 0xFF;

    /* Insert your solution below */



    while (1) {
            tick();
    }
    return 1;
}
