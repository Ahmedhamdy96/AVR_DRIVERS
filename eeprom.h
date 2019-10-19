/*-------------------------------------------------------------------------------------------------
 * File Name   : eeprom.h
 * Author      : Ahmed Hamdy
 * Date        : 29/9/2019
 * Description : Header File For External EEPROM Driver
 *------------------------------------------------------------------------------------------------*/

#ifndef EEPROM_H_
#define EEPROM_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"
#include "i2c.h"

/**************************************************************************************************/
/*                                     Preprocessor Macros                                        */
/**************************************************************************************************/
#define SUCCESS 1
#define ERROR 0

/**************************************************************************************************/
/*                                Public Functions Prototypes                                     */
/**************************************************************************************************/

void EEPROM_init(void) ;
uint8 EEPROM_writeByte(uint16 address , uint8 data) ;
uint8 EEPROM_readByte(uint16 address , uint8 *ptrData) ;

#endif
