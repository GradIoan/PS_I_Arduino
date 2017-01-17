#include <avr/io.h>
#include <avr/interrupt.h>
/*
 * UART.h
 *
 * Created: 14-Nov-16 9:00:44 PM
 *  Author: Ionut Grad
 */
  
#ifndef UART_H_
#define UART_H_


void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
void SendString(char *StringPtr);




#endif /* UART_H_ */