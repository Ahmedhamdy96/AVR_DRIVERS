/*-------------------------------------------------------------------------------------------------
 * File Name   : spi.c
 * Author      : Ahmed Hamdy
 * Date        : 26/9/2019
 * Description : SPI Driver Source Code
 *------------------------------------------------------------------------------------------------*/

#include "spi.h"

/**************************************************************************************************
 [ Function Name ] : SPI_initMaster
 [ Description   ] : This function is responsible for initializing  SPI for Master .
 [ Args          ] : void
 [ Returns       ] : void
**************************************************************************************************/
void SPI_initMaster(void)
{
	DDRB |= (1<<PB4) ;   /* SS as Output             */
	DDRB |= (1<<PB5) ;   /* MOSI as Output           */
	DDRB &= ~(1<<PB6) ;  /* MISO as Input            */
	DDRB |= (1<<PB7) ;   /* SPK ( clock ) as Output  */
	SPCR = (1<<SPE)|(1<<MSTR) ; /*  Enable SPI + select Master + clock : F_cpu/4  */
}

/**************************************************************************************************
 [ Function Name ] : SPI_initSlave
 [ Description   ] : This function is responsible for initializing  SPI for a Slave.
 [ Args          ] : void
 [ Returns       ] : void
**************************************************************************************************/
void SPI_initSlave(void)
{
	DDRB &= ~(1<<PB4) ;   /* SS as Input             */
	DDRB &= ~(1<<PB5) ;   /* MOSI as Input           */
	DDRB |= (1<<PB6) ;    /* MISO as Output          */
	DDRB &= ~(1<<PB7) ;   /* SPK ( clock ) as Input  */
	SPCR = (1<<SPE) ;     /*  Enable SPI + select Slave + clock : F_cpu/4  */
}

/**************************************************************************************************
 [ Function Name ] : SPI_sendByte
 [ Description   ] : This function is responsible for sending a Byte of data from Master to a Slave.
 [ Args          ] : uint8 data : hold data to be send .
 [ Returns       ] : void
**************************************************************************************************/
void SPI_sendByte(uint8 data)
{
	SPDR = data ;		                /* Put Data in SPI Data Register */
	while(BIT_IS_CLEAR(SPSR , SPIF)) ;  /* Wait Until Data is Sent Successfully */
}

/**************************************************************************************************
 [ Function Name ] : SPI_receiveByte
 [ Description   ] : This function is responsible for receiving a Byte of data from the Master .
 [ Args          ] : void
 [ Returns       ] : uint8
**************************************************************************************************/
uint8 SPI_receiveByte(void)
{
	while(BIT_IS_CLEAR(SPSR , SPIF)) ;  /* wait until transmission complete     */
	return SPDR ;                       /* return content of spi data register  */
}

/**************************************************************************************************
 [ Function Name ] : SPI_sendString
 [ Description   ] : This function is responsible for sending a String From the master to slave .
 [ Args          ] : const uint8* str : a pointer to the string to be send .
 [ Returns       ] : void
**************************************************************************************************/
void SPI_sendString(const uint8 *str)
{
	uint8 i = 0 ;
	while(str[i] !='\0')
	{
		SPI_sendByte(str[i]) ;
		i++ ;
	}
}

/**************************************************************************************************
 [ Function Name ] : SPI_receiveString
 [ Description   ] : This function is responsible for receiving a String From the master until the '#' character .
 [ Args          ] : uint8 *str : a pointer to the string to hold receiving data .
 [ Returns       ] : void
**************************************************************************************************/
void SPI_receiveString(uint8 *str)
{
	uint8 i = 0 ;
	str[i] = SPI_receiveByte() ;
	while(str[i] !='#')
	{
		i++ ;
		str[i] = SPI_receiveByte() ;
	}
	str[i] = '\0' ;
}
