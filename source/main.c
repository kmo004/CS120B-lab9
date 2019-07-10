/*	Author: Moker Bellomo
 *  Partner(s) Name: Michael Wen
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

volatile unsigned char count = 0x00;
unsigned char power = 0x00;

void set_PWM(double frequency){
static double current_frequency;
if (frequency != current_frequency){
if (!frequency){
TCCR3B &= 0x08;
}
else {
TCCR3B |= 0x03;
}

if (frequency < 0.954){
OCR3A = 0xFFFF;
}
else if (frequency > 31250){
OCR3A = 0x0000;
}

else{
OCR3A = (short)(8000000/(128*frequency))-1;
}
TCNT3 = 0;
current_frequency = frequency;
}
}

void PWM_on(){
TCCR3A = (1 << COM3A0);
TCCR3B = (1 << WGM32)|(1 << CS31)|(1<<CS30);
set_PWM(0);
}

void PWM_off(){
TCCR3A = 0x00;
TCCR3B = 0x00;
}

enum States{INIT,C4,E,F,G,A,B,C5,WAIT} state;
unsigned char button = 0x00;

void Tick()
{
button = ~PINA & 0x07;

switch(state){
	case INIT:
	
		if((button == 0x04) & (power == 0x00)){
			PWM_on();
			power = 1;
			state = WAIT;
		}
		else if ((button == 0x04) & (power == 0x01)){
			PWM_off();
			power = 0;
			state = WAIT;
		}
		if(button == 0x01){
			if(count < 8){
				count++;
			}
		}
		else if(button == 0x02){
			if(count > 1){
				count--;
			}
		}
		
		
		if ((button == 0x01) & (count == 1)){
			state = C4;
		}
		else if ((button == 0x01) & (count == 2)){
			state = E;
		}
		else if ((button == 0x01) & (count == 3)){
			state = F;
		}
		else if ((button == 0x01) & (count == 4)){
			state = G;
		}
		else if ((button == 0x01) & (count == 5)){
			state = A;
		}
		else if ((button == 0x01) & (count == 6)){
			state = B;
		}
		else if ((button == 0x01) & (count == 7)){
			state = C5;
		}
		
		
		else if ((button == 0x02) & (count == 1)){
			state = C4;
		}
		else if ((button == 0x02) & (count == 2)){
			state = E;
		}
		else if ((button == 0x02) & (count == 3)){
			state = F;
		}
		else if ((button == 0x02) & (count == 4)){
			state = G;
		}
		else if ((button == 0x02) & (count == 5)){
			state = A;
		}
		else if ((button == 0x02) & (count == 6)){
			state = B;
		}
		else if ((button == 0x02) & (count == 7)){
			state = C5;
		}
		else{
			state = INIT;
		}
		break;
		
		case WAIT:
		if((PINA & 0xFF) == 0xFF){
			state = INIT;
		}
		break;
		
		case C4:
			state = WAIT;
		break;
		
		case E:
			state = WAIT;
		break;
		
		case F:
			state = WAIT;
		break;
		
		case G:
			state = WAIT;
		break;
		
		case A:
			state = WAIT;
		break;
		
		case B:
			state = WAIT;
		break;
		
		case C5:
			state = WAIT;
		break;
		
	default: state = INIT;
	break;
}

switch(state){
	
	case WAIT:
	break;
	
	case INIT:
		//set_PWM(0);
	break;

	case C4:
		set_PWM(261.63);
	break;

	case E:
		set_PWM(329.63);
	break;

	case F:
		set_PWM(349.23);
	break;
	
	case G:
		set_PWM(392.00);
	break;
	
	case A:
		set_PWM(440.00);
	break;
	
	case B:
		set_PWM(493.88);
	break;
	
	case C5:
		set_PWM(523.25);
	break;
}
}


int main(void) {
    /* Insert DDR and PORT initializations */
DDRA = 0x00; PORTA = 0xFF;
DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    
	
    state = INIT;
    
    while (1) {
		Tick();
    }
    return 1;
}


