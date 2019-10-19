/*-------------------------------------------------------------------------------------------------
 * File Name   : adc.h
 * Author      : Ahmed Hamdy
 * Date        : 19/9/2019
 * Description : Header File For ADC Driver
 *------------------------------------------------------------------------------------------------*/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/**************************************************************************************************/
/*                                Public Functions Prototypes                                     */
/**************************************************************************************************/
void ADC_init(void) ;
uint16 ADC_readChannel(uint8 channelNumber) ;

#endif
