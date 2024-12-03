/*
 * fan.c
 *
 *  Created on: Sep 6, 2022
 *      Author: Omar
 */
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#define SET_BIT(REG,BIT_NUM) (REG |=(1<<BIT_NUM))
#define TOGGLE_BIT(REG,BIT_NUM) (REG ^=(1<<BIT_NUM))

unsigned int count=0,check,speed=0;
ISR(TIMER1_OVF_vect){
	switch (check){
	case 1:
		if(count++==54){
			TOGGLE_BIT(PORTB,PB1);
		}
		break;
	case 2:
		if(count++==107){
			TOGGLE_BIT(PORTB,PB1);
		}
		break;
	case 3:
		if(count++==161){
			TOGGLE_BIT(PORTB,PB1);
				}
		break;
	}

}
ISR(INT0_vect){
	TOGGLE_BIT(PORTB,PB1);
}
ISR(INT1_vect){
	check++;
	if (check==4){
			check=0;
	}
}
int main(void){
	SET_BIT(TCCR0,WGM01);SET_BIT(TCCR0,WGM00);SET_BIT(TCCR0,COM01);
	SET_BIT(TCCR0,CS00);SET_BIT(PORTB,PB3);
	SET_BIT(TCCR1B,CS12);SET_BIT(TCCR1B,CS10);
	TCNT1L=0;TCNT1H=0;
	SET_BIT(TIMSK,TICIE1);
	SET_BIT(SREG,7);SET_BIT(GICR,INT0); SET_BIT(MCUCR,ISC01);SET_BIT(MCUCR,ISC00);
	SET_BIT(GICR,INT1); SET_BIT(MCUCR,ISC11); SET_BIT(MCUCR,ISC10);
	DDRC=0x0F;DDRB=0x0F;DDRD=0x00;
	SET_BIT(PORTD,PD2);
	OCR0=250;
	check=0;
	while(1){

		if((PINA & (1<<PA0))){
    	  OCR0=250;
    	 speed=3;
      }
      if((PINA & (1<<PA1))){
          	  OCR0=100;
          	speed=2;
            }
      if((PINA & (1<<PA2))){
          	  OCR0=50;
          	speed=1;
            }
      SET_BIT(PORTB,PB6);
      PORTC=speed;
      _delay_ms(4);
      TOGGLE_BIT(PORTB,PB6);

      SET_BIT(PORTB,PB7);
      PORTC=check;
      _delay_ms(4);
      TOGGLE_BIT(PORTB,PB7);
	}
	}
