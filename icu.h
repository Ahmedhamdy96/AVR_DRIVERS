/*-------------------------------------------------------------------------------------------------
 * File Name   : icu.c
 * Author      : Ahmed Hamdy
 * Date        : 19/9/2019
 * Description : Header File For ICU Driver .
 *------------------------------------------------------------------------------------------------*/
#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

#define NULL_PTR ((void*)(0))
/**************************************************************************************************/
/*                                 Types Definitions For ICU                                      */
/**************************************************************************************************/
typedef enum{
	NO_CLOCK , F_CPU_CLOCK , F_CPU_8 , F_CPU_64 , F_CPU_256 , F_CPU_1024 , EXTERNAL_FALLING , EXTERNAL_RISING
}Icu_Clock ;

typedef enum{
	FALLING_EDGE , RISING_EDGE
}Icu_Edge_Type;

typedef struct{
	Icu_Clock clock ;
	Icu_Edge_Type edge ;
}Icu_Config;

/**************************************************************************************************/
/*                                    Functions Prototypes                                        */
/**************************************************************************************************/
void ICU_init(const Icu_Config *Config_Ptr) ;
void ICU_setCallBack( void(*a_ptr)(void) )  ;
void ICU_setEdgeDetectionType(const Icu_Edge_Type a_edgeType) ;
void ICU_clearTimer(void) ;
uint16 ICU_getCapturedValue(void) ;
void ICU_deInit(void) ;

#endif
