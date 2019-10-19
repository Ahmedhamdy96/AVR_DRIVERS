/*-------------------------------------------------------------------------------------------------
 * File Name   : keypad.c
 * Author      : Ahmed Hamdy
 * Date        : 25/9/2019
 * Description : Header File For UART Driver
 *------------------------------------------------------------------------------------------------*/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/**************************************************************************************************/
/*                                     Preprocessor Macros                                        */
/**************************************************************************************************/
#define UART_BAUDRATE 9600

/**************************************************************************************************/
/*                                Public Functions Prototypes                                     */
/**************************************************************************************************/
void UART_init(void);
void UART_sendByte(uint8 data) ;
uint8 UART_receiveByte(void) ;
void UART_sendString(const uint8 *str ) ;
void UART_receiveString( uint8 *str ) ;

#endif
