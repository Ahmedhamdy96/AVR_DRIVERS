/*-------------------------------------------------------------------------------------------------
 * File Name   : lcd.h
 * Author      : Ahmed Hamdy
 * Date        : 18/9/2019
 * Description : Header File For LCD Driver
 *------------------------------------------------------------------------------------------------*/

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/**************************************************************************************************/
/*                                   Preprocessor Macros                                          */
/**************************************************************************************************/
/*------------------------------------------------------------------------------------------------*/
/*                              LCD Control Port Configurations                                   */
/*------------------------------------------------------------------------------------------------*/
#define LCD_CONTROL_PORT_DIR DDRC
#define LCD_CONTROL_PORT PORTC

#define RS PC0
#define RW PC1
#define E PC2
/*------------------------------------------------------------------------------------------------*/
/*                              LCD Data Port Configurations                                      */
/*------------------------------------------------------------------------------------------------*/
#define DATA_BITS_MODE 4

#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS
#endif

#define LCD_DATA_PORT_DIR DDRD
#define LCD_DATA_PORT PORTD
/*-----------------------------------------------------------------------------------------------*/
/*                                    LCD Commands                                               */
/*-----------------------------------------------------------------------------------------------*/
#define CLEAR_DISPLAY 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINES_LCD_FOUR_BITS_MODE 0x28
#define TWO_LINES_LCD_EIGHT_BITS_MODE 0x38
#define CURSOR_ON 0x0E
#define CURSOR_OFF 0x0C
#define CURSOR_BLINKING 0x0F
#define CURSOR_SHIFT_RIGHT 0x14
#define CURSOR_SHIFT_LEFT 0x10
#define SET_CURSOR_POSITION 0x80

/**************************************************************************************************/
/*                                Public Functions Prototypes                                     */
/**************************************************************************************************/
void LCD_init(void);
void LCD_sendCommand(uint8 command) ;
void LCD_displayCharacter(uint8 character) ;
void LCD_displayString(const uint8 *str) ;
void LCD_displayStringRowCol(uint8 row , uint8 col , const uint8 *str) ;
void LCD_goToRowCol(uint8 row , uint8 col );
void LCD_clearDisplay(void) ;
void LCD_integerToString(int number) ;

#endif
