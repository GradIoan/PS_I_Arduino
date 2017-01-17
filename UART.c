#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"
#include <string.h>

#define BAUD 9600
#define MYUBRR 16000000/16/BAUD-1

char input[20];
int counter;



/* SETUP UART */
void USART_Init( unsigned int ubrr)
{
	cli();
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	/*Enable receiver and transmitter */
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);  // enable rutina intrerupre
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
	sei();
}

void USART_Transmit( unsigned char data )
{
	while(!(UCSR0A & (1<<UDRE0)))
	{

	};
	UDR0 = data;
}


unsigned char USART_Receive( void )
{
	while( !(UCSR0A & (1<<RXC0)));
	return UDR0;
}


void SendString(char *StringPtr)
{
	while(*StringPtr++)
		USART_Transmit(*StringPtr);
}