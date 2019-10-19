/*-------------------------------------------------------------------------------------------------
 * File Name   : keypad.c
 * Author      : Ahmed Hamdy
 * Date        : 19/9/2019
 * Description : Keypad Driver Source Code
 *------------------------------------------------------------------------------------------------*/

#include "keypad.h"

/**************************************************************************************************/
/*                                Private Functions Prototypes                                    */
/**************************************************************************************************/
static uint8 KeyPad_4x3_adjustKeyNumber(uint8 key_number) ;
static uint8 KeyPad_4x4_adjustKeyNumber(uint8 key_number) ;

/**************************************************************************************************
   [ Function Name ] : KeyPad_getPresssedKey
   [ Description   ] : This function is responsible for getting the pressed key value
   [ Args          ] : void
   [ Returns       ] : uint8
**************************************************************************************************/
uint8 KeyPad_getPresssedKey(void){
	uint8 row ;
	uint8 col ;
	while(1)
	{
		for(col = 0 ; col<COLS ; col++){
			KEYPAD_PORT_DIR = (0b00010000<<col) ;    /* only one column is output at a time  , other pins are inputs */
			KEYPAD_PORT_OUT = (~(0b00010000<<col)) ; /* turning on the internal pull up resistors                    */
			for(row = 0 ; row<ROWS; row++){
				if(BIT_IS_CLEAR(KEYPAD_PORT_IN , row)){
					#if (COLS == 3)
						return KeyPad_4x3_adjustKeyNumber((row*COLS)+col+1) ;
					#elif (COLS == 4)
						return KeyPad_4x4_adjustKeyNumber((row*COLS)+col+1) ;
					#endif
				}
			}
		}
	}
}

#if(COLS == 3 )
/*************************************************************************************************
   [ Function Name ] : KeyPad_4x3_adjustKeyNumber
   [ Description   ] : This Function is responsible for mapping the switch number in the keypad
                       to its corresponding functional number in the proteus for 4x3 keypad
   [ Args          ] : uint8
   [ Returns       ] : uint8
*************************************************************************************************/

static uint8 KeyPad_4x3_adjustKeyNumber(uint8 key_number){
	switch(key_number)
	{
		case 10 : return '*' ;
			break ;
		case 11 : return 0 ;
			break ;
		case 12 : return '#' ;
			break ;
		default : return key_number ;
	}
}
#elif (COLS == 4)
/*************************************************************************************************
   [ Function Name ] : KeyPad_4x4_adjustKeyNumber
   [ Description   ] : This Function is responsible for mapping the switch number in the keypad
                       to its corresponding functional number in the proteus for 4x4 keypad
   [ Args          ] : uint8
   [ Returns       ] : uint8
*************************************************************************************************/
static uint8 KeyPad_4x4_adjustKeyNumber(uint8 key_number){
	switch(key_number)
		{
			case 1: return 7;
					break;
			case 2: return 8;
					break;
			case 3: return 9;
					break;
			case 4: return '%'; // ASCII Code of %
					break;
			case 5: return 4;
					break;
			case 6: return 5;
					break;
			case 7: return 6;
					break;
			case 8: return '*'; /* ASCII Code of '*' */
					break;
			case 9: return  1;
					break;
			case 10: return 2;
					break;
			case 11: return 3;
					break;
			case 12: return '-'; /* ASCII Code of '-' */
					break;
			case 13: return 13;  /* ASCII of Enter */
					break;
			case 14: return 0;
					break;
			case 15: return '='; /* ASCII Code of '=' */
					break;
			case 16: return '+'; /* ASCII Code of '+' */
					break;
			default: return key_number;
		}
}
#endif
