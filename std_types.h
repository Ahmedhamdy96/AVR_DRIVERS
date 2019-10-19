/*-------------------------------------------------------------------------------------------------
 * File Name   : std_types.h
 * Author      : Ahmed Hamdy
 * Date        : 18/9/2019
 * Description : This File Contains Common Platform Types Abstraction
 *------------------------------------------------------------------------------------------------*/


#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef signed char        sint8  ; /*                 -128 .. +127                   */
typedef unsigned char      uint8  ; /*                    0 .. +255                   */
typedef signed short       sint16 ; /*               -32768 .. +32767                 */
typedef unsigned short     uint16 ; /*                    0 .. +65535                 */
typedef signed long        sint32 ; /*          -2147483648 .. +2147483647            */
typedef unsigned long      uint32 ; /*                    0 .. +4294967295            */
typedef signed long long   sint64 ; /* −9223372036854775807 .. +9223372036854775807   */
typedef unsigned long long uint64 ; /*                    0 .. +18446744073709551615  */
typedef float              float32;
typedef double             float64;

typedef unsigned char bool ;
#ifndef TRUE
#define TRUE  (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef HIGH
#define HIGH  (1)
#endif

#ifndef LOW
#define LOW   (0)
#endif

#endif
