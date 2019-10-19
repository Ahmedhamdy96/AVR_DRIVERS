/*-------------------------------------------------------------------------------------------------
 * File Name   : spi.h
 * Author      : Ahmed Hamdy
 * Date        : 26/9/2019
 * Description : Header File For SPI Driver
 *------------------------------------------------------------------------------------------------*/
#ifndef SPI_H_
#define SPI_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/**************************************************************************************************/
/*                                Public Functions Prototypes                                     */
/**************************************************************************************************/
void SPI_initMaster(void) ;
void SPI_initSlave(void) ;
void SPI_sendByte(uint8 data) ;
uint8 SPI_receiveByte(void) ;
void SPI_sendString(const uint8 *str) ;
void SPI_receiveString(uint8 *str) ;

#endif
