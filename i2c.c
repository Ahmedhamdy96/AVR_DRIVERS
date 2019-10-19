/*-------------------------------------------------------------------------------------------------
 * File Name   : i2c.c
 * Author      : Ahmed Hamdy
 * Date        : 28/9/2019
 * Description : I2C (TWI) Driver Source File
 *------------------------------------------------------------------------------------------------*/

#include "i2c.h"

/**************************************************************************************************
  [ Function Name ] : I2C_init
  [ Description   ] : This function is responsible for Initializing the I2C (TWI) Module and Must be called before main .
  [ Args          ] : void
  [ Returns       ] : void
**************************************************************************************************/
void I2C_init(void)
{

	TWBR = 0x20 ; 		 /* SCL = 100K using F_CPU 8MHz and 0 Pre-scaler */
	TWSR = 0x00 ;        /* SCL = 100K using F_CPU 8MHz and 0 Pre-scaler */
	TWAR = 0b00000010 ;  /* My Address  is 1 ( Address stored in the most 7-Bits ) */
	TWCR = (1<<TWEN) ;   /* Enable I2C Module */
}

/**************************************************************************************************
  [ Function Name ] : I2C_start
  [ Description   ] : This function is responsible for sending the Start Bit .
  [ Args          ] : void
  [ Returns       ] : void
**************************************************************************************************/
void I2C_start(void)
{
   /*
	* TWINT = 1 : Clear the TWINT flag before sending the start bit .
	* TWSTA = 1 : send the start bit .
	* TWEN  = 1  : Enable I2C Module .
	*/
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN) ;
   /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while(BIT_IS_CLEAR(TWCR , TWINT)) ;
}

/**************************************************************************************************
  [ Function Name ] : I2C_stop
  [ Description   ] : This function is responsible for sending the Stop Bit .
  [ Args          ] : void
  [ Returns       ] : void
**************************************************************************************************/
void I2C_stop(void)
{
   /*
	* TWINT = 1 : Clear the TWINT flag before sending the stop bit .
	* TWSTO = 1 : send the stop bit .
	* TWEN = 1  : Enable I2C Module .
	*/
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN) ;
}

/**************************************************************************************************
  [ Function Name ] : I2C_write
  [ Description   ] : This function is responsible for sending transmiting a Byte of Data with No-Acknowledgement.
  [ Args          ] : uint8 data : the byte of data to be sent .
  [ Returns       ] : void
**************************************************************************************************/
void I2C_write(uint8 data)
{
	TWDR = data ; /* put data into TWI Data register */
	TWCR = (1 << TWINT) | (1 << TWEN) ;
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

/**************************************************************************************************
  [ Function Name ] : I2C_readWithACK
  [ Description   ] : This function is responsible for reading a received Byte of Data with Acknowledgement.
  [ Args          ] : void .
  [ Returns       ] : uint8 : the received byte of data .
**************************************************************************************************/
uint8 I2C_readWithACK(void)
{
   /*
	* TWINT = 1 : Clear the TWINT flag before reading the data .
	* TWEA = 1  : Enable sending ACK after reading or receiving data .
	* TWEN = 1  : Enable TWI Module .
	*/
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
   /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR ; /* return contents of data register */
}

/**************************************************************************************************
  [ Function Name ] : I2C_readWithNACK
  [ Description   ] : This function is responsible for reading a received Byte of Data with No-Acknowledgement.
  [ Args          ] : void .
  [ Returns       ] : uint8 : the received byte of data .
**************************************************************************************************/
uint8 I2C_readWithNACK(void)
{
   /*
	* TWINT = 1 : Clear the TWINT flag before reading the data .
	* TWEN = 1  : Enable TWI Module .
	*/
	TWCR = (1 << TWINT) | (1 << TWEN) ;
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR ; /* return contents of data register */
}

/**************************************************************************************************
  [ Function Name ] : I2C_getStatus
  [ Description   ] : This function is responsible for getting the current status of the i2c module .
  [ Args          ] : void .
  [ Returns       ] : uint8 : the current status of the TWI module .
**************************************************************************************************/
uint8 I2C_getStatus(void)
{
	uint8 status ;
	/* return last 5-Bits only which contains the status */
	status = TWSR & 0xF8 ;
	return status ;
}
