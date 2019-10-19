/*-------------------------------------------------------------------------------------------------
 * File Name   : i2c.h
 * Author      : Ahmed Hamdy
 * Date        : 28/9/2019
 * Description : Header File For I2C (TWI) Driver
 *------------------------------------------------------------------------------------------------*/

#ifndef I2C_H_
#define I2C_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/**************************************************************************************************/
/*                                     Preprocessor Macros                                        */
/**************************************************************************************************/
/*------------------------------------------------------------------------------------------------*/
/*                             I2C Status Bits in the TWSR Register                               */
/*------------------------------------------------------------------------------------------------*/
#define I2C_START 0x08          /* START Bit has been sent                                       */
#define I2C_REPEATED_START 0x10 /* Repeated Start Bit has been sent                              */
#define I2C_MT_SLA_W_ACK 0x18   /* Master Transmit ( Slave Address + Write Request ) + ACK received from slave */
#define I2C_MT_SLA_W_NACK 0x20  /* Master Transmit ( Slave Address + Write Request )                           */
#define I2C_MT_DATA_ACK 0x28    /* Master Transmit  Data and ACK Bit Received by the Slave                     */
#define I2C_MT_DATA_NACK 0x30   /* Master Transmit  Data and ACK Bit Hasn't been received                      */
#define I2C_MT_SLA_R_ACK 0x40   /* Master Transmit ( Slave Address + Read Request ) + ACK received from slave  */
#define I2C_MT_SLA_R_NACK 0x48  /* Master Transmit ( Slave Address + Read Request )                            */
#define I2C_MR_DATA_ACK 0x50    /* Master Received Data and Send ACK                                           */
#define I2C_MR_DATA_NACK 0x58   /* Master Received Data and dosen't send ACK to Slave                          */

/**************************************************************************************************/
/*                                Public Functions Prototypes                                     */
/**************************************************************************************************/
void I2C_init(void);
void I2C_start(void);
void I2C_stop(void);
void I2C_write(uint8 data);
uint8 I2C_readWithACK(void);
uint8 I2C_readWithNACK(void);
uint8 I2C_getStatus(void);

#endif
