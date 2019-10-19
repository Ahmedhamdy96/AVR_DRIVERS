/*-------------------------------------------------------------------------------------------------
 * File Name   : adc.c
 * Author      : Ahmed Hamdy
 * Date        : 19/9/2019
 * Description : ADC Driver Source File
 *------------------------------------------------------------------------------------------------*/

#include "adc.h"

/**************************************************************************************************
   [ Function Name ] : ADC_init
   [ Description   ] : This function is responsible for Initializing the ADC and Must be called before main .
   [ Args          ] : void
   [ Returns       ] : void
**************************************************************************************************/
void ADC_init(void)
{
	ADMUX = 0 ;
	ADCSRA =(1<<ADEN) | (1<<ADPS0) | (1<<ADPS1) ;
}

/**************************************************************************************************
   [ Function Name ] : ADC_readChannel
   [ Description   ] : This function is responsible for Reading the Analog Signal from an ADC Channels at PORT A.
   [ Args          ] : uint8 channelNumber : 0 , 1 , 2 , .. , 7
   [ Returns       ] : uint16              : the ADC Conversion Result ( 0 .. 1023 ).
**************************************************************************************************/
uint16 ADC_readChannel(uint8 channelNumber)
{
	channelNumber &=0x07 ;                    /* Mask Channel Number ( it must be a number from 0 : 7  */
	ADMUX = (ADMUX & 0xE0) |(channelNumber) ; /* insert channel number                                 */
	SET_BIT(ADCSRA , ADSC) ;                  /* Start Conversion                                      */
	while(BIT_IS_CLEAR(ADCSRA , ADIF));       /* wait until the flag is raised ( conversion complete ) */
	return ADC ; 						      /* ADC Data Register ( contains conversion result )      */
}
