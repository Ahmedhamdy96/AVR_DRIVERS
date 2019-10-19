/*-------------------------------------------------------------------------------------------------
 * File Name   : keypad.c
 * Author      : Ahmed Hamdy
 * Date        : 25/9/2019
 * Description : UART Driver Source Code
 *------------------------------------------------------------------------------------------------*/

#include "uart.h"
#define BAUDRATE_PRESCALE (((F_CPU/(8UL*UART_BAUDRATE))) - 1)

/**************************************************************************************************
   [ Function Name ] : UART_init
   [ Description   ] : This function is responsible for initializing UART module .
   [ Args          ] : void
   [ Returns       ] : void
**************************************************************************************************/
void UART_init(void)
{
	/* Double Transmission Speed                                                     */
	UCSRA = (1<<U2X) ;
	/* Enable Receiver and Transmitter                                               */
	UCSRB = (1<<RXEN) | (1<<TXEN) ;
	/* URSEL   : Must be one when writing UCSRC                                      */
	/* UCSZ0:1 : Set 8-Bits Data Mode                                                */
	UCSRC = (1<<URSEL)|(1<<UCSZ0)|(UCSZ1) ;
	/* First 8 bits from the BAUDRATE_PRESCALE inside UBRRL and last 4 bits in UBRRH */
	UBRRH = BAUDRATE_PRESCALE >> 8 ;
	UBRRL = BAUDRATE_PRESCALE ;
}

/**************************************************************************************************
   [ Function Name ] : UART_sendByte
   [ Description   ] : This function is responsible for Transmitting a 1-Byte of data
   [ Args          ] : uint8 : byte of data to be send
   [ Returns       ] : void
**************************************************************************************************/
void UART_sendByte(uint8 data)
{
	UDR = data ;                      /* Put Data in Data Register           */
	while(BIT_IS_CLEAR(UCSRA , TXC)); /* wait until transmission is complete */
	SET_BIT(UCSRA , TXC) ;          /* clear flag again                    */
}
/**************************************************************************************************
   [ Function Name ] : UART_receiveByte
   [ Description   ] : This function is responsible for Receiving 1-Byte of data
   [ Args          ] : uint8 data
   [ Returns       ] : uint8 : content of UART Data Register
**************************************************************************************************/
uint8 UART_receiveByte(void)
{
	while(BIT_IS_CLEAR(UCSRA , RXC)); /* wait until receiving is complete */
	return UDR ;                      /* return contents of data register */
}
/**************************************************************************************************
   [ Function Name ] : UART_sendString
   [ Description   ] : This function is responsible for Transmiting a String
   [ Args          ] : const uint8* : a pointer to constant character arry - string - to be send
   [ Returns       ] : void
**************************************************************************************************/
void UART_sendString(const uint8 *str )
{
	uint8 i = 0 ;
	while(str[i] !='\0')
	{
		UART_sendByte(str[i]) ;
		i++ ;
	}
}
/**************************************************************************************************
   [ Function Name ] : UART_receiveString
   [ Description   ] : This function is responsible for Receiving a String
   [ Args          ] : uint8* : a pointer to  character arry - string - to hold received string
   [ Returns       ] : void
**************************************************************************************************/
void UART_receiveString(uint8 *str )
{
	uint8 i = 0 ;
	str[i] = UART_receiveByte() ;
	while(str[i] !='#')
	{
		i++ ;
		str[i] = UART_receiveByte() ;
	}
	str[i] = '\0' ;
}
