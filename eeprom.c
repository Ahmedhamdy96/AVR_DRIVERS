/*-------------------------------------------------------------------------------------------------
 * File Name   : eeprom.c
 * Author      : Ahmed Hamdy
 * Date        : 29/9/2019
 * Description : External EEPROM Driver Source Code
 *------------------------------------------------------------------------------------------------*/
#include "eeprom.h"
/**************************************************************************************************
 [ Function Name ] : EEPROM_init
 [ Description   ] : This function is responsible for initializing the interfacing with EEPROM .
 [ Args          ] : void
 [ Returns       ] : void
**************************************************************************************************/
void EEPROM_init(void)
{
	/*Initializing I2C Communication */
	I2C_init() ;
}

/**************************************************************************************************
 [ Function Name ] : EEPROM_writeByte
 [ Description   ] : This function is responsible for Writing a Byte Of Data at a specific memory address .
 [ Args          ] : uint16 address , uint8 data
 [ Returns       ] : uint8
**************************************************************************************************/
uint8 EEPROM_writeByte(uint16 address , uint8 data)
{
	I2C_start();										 /* Sending Start Bit      */
	if(I2C_getStatus() != I2C_START)
		return ERROR ;

	I2C_write((uint8)(0xA0 | ((address & 0x0700)>>7))) ; /* Sending Device Address */
	if(I2C_getStatus() != I2C_MT_SLA_W_ACK)
		return ERROR ;

	I2C_write((uint8)address) ;							 /* Sending The Memory Location Address */
	if(I2C_getStatus() != I2C_MT_DATA_ACK)
		return ERROR ;

	I2C_write(data) ;									 /* Sending the Byte Of Data to be written in the EEPROM */
	if(I2C_getStatus() != I2C_MT_DATA_ACK)
		return ERROR ;

	I2C_stop() ;									     /* Sending the Stop Bit   */
	return SUCCESS ;
}

/**************************************************************************************************
 [ Function Name ] : EEPROM_readByte
 [ Description   ] : This function is responsible for Reading a Byte Of Data from a specific memory address .
 [ Args          ] : uint16 address , uint8 * ptrData
 [ Returns       ] : uint8
**************************************************************************************************/
uint8 EEPROM_readByte(uint16 address , uint8 *ptrData)
{
	I2C_start() ; 						   				 /* Sending Start Bit      */
	if(I2C_getStatus() != I2C_START)
		return ERROR ;

	I2C_write((uint8)(0xA0 | ((address & 0x0700)>>7))) ; /* Sending Device Address */
	if(I2C_getStatus() != I2C_MT_SLA_W_ACK)
		return ERROR ;

	I2C_write((uint8)address) ; 						 /* Sending The Memory Location Address */
	if(I2C_getStatus() != I2C_MT_DATA_ACK)
		return ERROR ;

	I2C_start() ;                                        /* Sending another Start Bit ( Repeated Start )*/
	if(I2C_getStatus() != I2C_REPEATED_START)
		return ERROR ;

    I2C_write((uint8)((0xA0) | ((address & 0x0700)>>7) | 1)); /* Sending Device Address */
    if (I2C_getStatus() != I2C_MT_SLA_R_ACK)
        return ERROR;

    *ptrData = I2C_readWithNACK();							 /* Read the Byte Of Data at this location */
    if(I2C_getStatus() != I2C_MR_DATA_NACK)
    	return ERROR ;

	I2C_stop();	      										/* Sending the Stop Bit   */
	return SUCCESS ;
}
