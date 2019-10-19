/*-------------------------------------------------------------------------------------------------
 * File Name   : common_macros.h
 * Author      : Ahmed Hamdy
 * Date        : 18/9/2019
 * Description : This File Contains Commonly Used Macros
 *------------------------------------------------------------------------------------------------*/

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_
/* Set    a Bit at   any Register                                  */
#define SET_BIT(REG , BIT) ( REG |= (1<<BIT))
/* Clear  a Bit at   any Register                                  */
#define CLEAR_BIT(REG, BIT) ( REG &=(~(1<<BIT)))
/* Toggle a Bit at   any Register                                  */
#define TOGGLE_BIT(REG , BIT) ( REG ^=(1<<BIT))
/* Rotate Right any register value with specific number of rotates */
#define ROR(REG , NUM) (REG = (REG>>NUM)| (REG<<(8-NUM)))
/* Rotate Left  any register value with specific number of rotates */
#define ROL(REG , NUM) (REG = (REG<<NUM) | (REG>>8-NUM))
/* Check if a specific Bit is Set     and returns True if Yes      */
#define BIT_IS_SET(REG , BIT) (REG & (1<<BIT))
/* Check if a specific Bit is Cleared and returns True if Yes      */
#define BIT_IS_CLEAR(REG , BIT) (!(REG & (1<<BIT)))
#endif
