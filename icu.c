/*-------------------------------------------------------------------------------------------------
 * File Name   : icu.c
 * Author      : Ahmed Hamdy
 * Date        : 19/9/2019
 * Description : ICU Driver Source Code
 *------------------------------------------------------------------------------------------------*/
#include "icu.h"

static volatile void (*g_callBackPtr)(void) = NULL_PTR ;


/* The Interrupt Service Routine For Input Capture                     */

ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)() ;
	}
}
/*************************************************************************************************
   [ Function Name ] : ICU_init
   [ Description   ] : This function is responsible for initializing the ICU
   	   	   	   	   	   with the Configurations of the Configurations Structure .
   [ Args          ] : const Icu_Config *Config_Ptr : a pointer to configurations structure
   [ Returns       ] : void
*************************************************************************************************/
void ICU_init(const Icu_Config *Config_Ptr)
{
	DDRD &= ~(1<<PD6) ;                                  /* configure Pin 6 of Port D as Input (ICP) */
	TCCR1A = (1<<FOC1A) | (1<<FOC1B) ;                   /* Timer Mode          : Normal             */
	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->clock) ;     /* Set Clock                                */
	TCCR1B |=(TCCR1B & 0xBF) | (Config_Ptr->edge)  ;     /* Set Edge                                 */
	TCNT1 = 0 ;                                          /* Timer Initial Value : 0                  */
	ICR1 = 0 ;											 /* Timer Capture Register Value : 0         */
	TIMSK |= (1<<TICIE1) ;                               /* Input Capture Interrupt Enable           */
}

/*************************************************************************************************
   [ Function Name ] : ICU_setCallBack
   [ Description   ] : This function is responsible for assigning the pointer of the function to be called
   	   	   	   	   	   when an interrupt happens to the icu gloabl pointer .
   [ Args          ] : void(*a_ptr)(void) : a pointer to a function which takes nothing and returns nothing
   [ Returns       ] : void
*************************************************************************************************/
void ICU_setCallBack( void(*a_ptr)(void) )
{
	g_callBackPtr = a_ptr ;
}

/*************************************************************************************************
   [ Function Name ] : ICU_setEdgeDetectionType
   [ Description   ] : This function is responsible for setting The Edge type to be detected
   [ Args          ] : void
   [ Returns       ] : void
*************************************************************************************************/
void ICU_setEdgeDetectionType(const Icu_Edge_Type a_edgeType)
{
	TCCR1B = (TCCR1B & 0xBF) | (a_edgeType<<6);
}
/*************************************************************************************************
   [ Function Name ] : ICU_clearTimer
   [ Description   ] : This function is responsible for setting timer counter register value to be ZERO
   [ Args          ] : void
   [ Returns       ] : void
*************************************************************************************************/
void ICU_clearTimer(void)
{
	TCNT1 = 0 ;
}

/*************************************************************************************************
   [ Function Name ] : ICU_getCapturedValue
   [ Description   ] : This function is responsible for getting the value of the Input Capture Register
   [ Args          ] : void
   [ Returns       ] : void
*************************************************************************************************/
uint16 ICU_getCapturedValue(void)
{
	return ICR1 ;
}
/*************************************************************************************************
   [ Function Name ] : ICU_deInit
   [ Description   ] : This function is responsible for Turning Off  the ICU
   [ Args          ] : void
   [ Returns       ] : void
*************************************************************************************************/
void ICU_deInit(void)
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;
	TIMSK &= ~(1<<TICIE1) ;
}
