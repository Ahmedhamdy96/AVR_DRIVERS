/*-------------------------------------------------------------------------------------------------
 * File Name   : micro_config.h
 * Author      : Ahmed Hamdy
 * Date        : 18/9/2019
 * Description : This File Contains Microcontroller Configurations and libraries
 *------------------------------------------------------------------------------------------------*/

#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_
/**************************************************************************************************/
/*                                Preprocessor Macros                                             */
/**************************************************************************************************/
#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#endif
