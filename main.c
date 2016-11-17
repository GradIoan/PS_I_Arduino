
#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"

#define BAUD 9600
#define MYUBRR 16000000/16/BAUD-1

int main(void)
{
//seteaza pin 2 , 6 (fade) ca si output
DDRD = 0x44;
setTimer0();
setTimer1();
setTimer2();
USART_Init(MYUBRR); // initializare USART
    /* Replace with your application code */
    while (1) 
    {
		char data = "*";
		data = USART_Receive();
		if (data == 'A')
		{
			PORTD  |= (1<<3);
		}
		else
		if ( data == 'S' )
		{
			PORTD &= ~(1<<3);
		}
    }
}

int dsec = 0;
int secunda = 1;
int _step = 0;
int _step_reverse= 61;
int _ocr=255;

void loop()
{
	
}


void setTimer0() //genereaza PWM
{
	//seteaza mod non-inverted
	TCCR0A |= (1 << COM0A1);
	
	TCCR0A |= (1 << WGM01) | (1 << WGM00); //Fast PWM
	
	TCCR0B |= (1 << CS00); // no prescaler
}

void setTimer1()
{
	cli();
	TCCR1A = 0x00;
	TCCR1B = 0x00;
	
	//  TCCR1B |= (1 << WGM12); //CTC mode
	TIMSK1 |= (1 << TOIE1);  // enable overflow interrupt
	//intrerupere la 1 secunda
	//seteaza prescaler la 1024
	TCNT1 = 0xC2F7;
	TCCR1B |= (1 << CS10);
	TCCR1B |= (1 << CS12);
	sei(); // enagle global interrupts
}

ISR(TIMER1_OVF_vect)
{
	// La fiecare intrerupere, aprinde led-ul
	// De pe pinul 1
	TCNT1 = 0xC2F7;
	PORTD ^= ( 1 << 2 ); // blink la o secunda
	dsec++;
	if ( dsec == 2)
	{
		SendString(" Hello World! ");
		dsec = 0;
	}

}

void setTimer2()
{
	cli();
	TCCR2A = 0;
	TCCR2B = 0;
	//seteaza mod CTC
	TCCR2A |= (1 << WGM21);

	OCR2A=254; //intrerupere la 16ms

	//seteaza prescalera la 1024
	TCCR2B |= (1<<CS22) | (1 << CS21) | (1<<CS20);

	//activeaza intreruperi
	TIMSK2 |= (1 << OCIE2A);
	sei();
}


void _fadeLed2()
{
	_step++;
	_step_reverse--;
	
	if( _step >= 61 && _step_reverse<=0 && secunda >= 4)
	{
		_step = 0;
		_step_reverse=61;
		secunda = 1;
	}
	if ( _step >= 61 && _step_reverse<=0 )
	{
		_step = 0;
		_step_reverse=61;
		secunda ++;
	}


	switch(secunda)
	{
		case 1:
		OCR0A = 3*_step;
		break;
		case 2:
		OCR0A = 254;
		_ocr = 254;
		break;
		case 3:
		OCR0A = 3*_step_reverse;
		break;
		case 4:
		OCR0A = 0;
		break;
		default:
		break;

		PORTD |= ( 1<<6 );
		
	}
}


ISR(TIMER2_COMPA_vect)
{
	_fadeLed2();
}




