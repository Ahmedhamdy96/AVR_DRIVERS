/*-------------------------------------------------------------------------------------------------
 * File Name   : lcd.c
 * Author      : Ahmed Hamdy
 * Date        : 18/9/2019
 * Description : LCD Driver Source Code
 *------------------------------------------------------------------------------------------------*/


#include "lcd.h"

/**************************************************************************************************
   [ Function Name ] : LCD_init
   [ Description   ] : This function is responsible for Initializing the LCD and Must be called before main .
   [ Args          ] : void
   [ Returns       ] : void
**************************************************************************************************/
void LCD_init(void)
{
	LCD_CONTROL_PORT_DIR |= (1<<RS) | (1<<RW) | (1<<E) ; /* RS , RW , E ad Output Pins */
	/* 4 Bits Mode Static Configurations */
	#if(DATA_BITS_MODE == 4)
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT_DIR |=0xF0 ;  			               /* pins number 4..5..6..7 as output         */
		#else
			LCD_DATA_PORT_DIR |=0x0F ;                             /* pins number 0..1..2..3 as output         */
		#endif
		LCD_sendCommand(FOUR_BITS_DATA_MODE) ;                     /* initializing LCD to 4-Bits Mode          */
		LCD_sendCommand(TWO_LINES_LCD_FOUR_BITS_MODE) ;
	/* 8 Bits Mode Static Configurations */
	#elif(DATA_BITS_MODE == 8)
		LCD_DATA_PORT_DIR = 0xFF ;                                  /* All Data Port Pins as Output            */
		LCD_sendCommand(TWO_LINES_LCD_EIGHT_BITS_MODE) ;            /* 2-Lines , 8-Bits Mode and 5*7 Dots LCD  */
	#endif
	LCD_sendCommand(CLEAR_DISPLAY) ;                                /* Clearing the LCD at the beginning       */
	LCD_sendCommand(CURSOR_ON) ;                                   /* Turning OFF the Cursor at the beginning */
}
/**************************************************************************************************
   [ Function Name ] : LCD_sendCommand
   [ Description   ] : This function is responsible for Sending a given Command to LCD .
   [ Args          ] : uint8 command : the ascii code for the command
   [ Returns       ] : void
**************************************************************************************************/
void LCD_sendCommand(uint8 command)
{
	/* this steps must be executed one after one according to timing diagram   */
	CLEAR_BIT(LCD_CONTROL_PORT,RS); /* RS=0 .. Instruction Mode                */
	CLEAR_BIT(LCD_CONTROL_PORT,RW); /* RW=0 .. Write data to LCD               */
	_delay_ms(1);                   /* delay for processing tas = 50ns         */
	SET_BIT(LCD_CONTROL_PORT,E);    /* E=1  .. Enable LCD                      */
	_delay_ms(1);                   /* delay for processing tpw - tdws = 190ns */
	#if (DATA_BITS_MODE == 4)
		/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((command & 0xF0) >> 4);
		#endif
		_delay_ms(1);                  /* delay for processing tdsw = 100ns       */
		CLEAR_BIT(LCD_CONTROL_PORT,E); /* E=0 .. Disable LCD                      */
		_delay_ms(1);                  /* delay for processing th = 13ns          */
		SET_BIT(LCD_CONTROL_PORT,E);   /* E=1 .. Enable LCD                       */
		_delay_ms(1);                  /* delay for processing Tpw - Tdws = 190ns */
	   /* out the lowest 4 bits of the required command to the data bus D4 --> D7 */
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0x0F) << 4);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (command & 0x0F);
		#endif
		_delay_ms(1);                  /* delay for processing tdsw = 100ns        */
		CLEAR_BIT(LCD_CONTROL_PORT,E); /* E=0 .. disable LCD                       */
		_delay_ms(1);                  /* delay for processing th = 13ns           */
	#elif (DATA_BITS_MODE == 8)
		LCD_DATA_PORT = command;       /* out the required command to the data bus D0 --> D7 */
		_delay_ms(1);                  /* delay for processing tdsw = 100ns                  */
		CLEAR_BIT(LCD_CONTROL_PORT,E); /* E=0 .. disable LCD                                 */
		_delay_ms(1);                  /* delay for processing th = 13ns                     */
	#endif
}
/**************************************************************************************************
   [ Function Name ] : LCD_displayCharacter
   [ Description   ] : This function is responsible for Displaying a given Character on the LCD .
   [ Args          ] : uint8 character : the character to be displayed
   [ Returns       ] : void
**************************************************************************************************/
void LCD_displayCharacter(uint8 character)
{
	SET_BIT(LCD_CONTROL_PORT,RS);        /* RS=1 .. Data Mode                                 */
	CLEAR_BIT(LCD_CONTROL_PORT,RW);      /* RW=0 .. Write data to LCD                         */
	_delay_ms(1);                        /* delay for processing tas = 50ns                   */
	SET_BIT(LCD_CONTROL_PORT,E);         /* E=1  .. Enable LCD                                */
	_delay_ms(1);                        /* delay for processing tpw - tdws = 190ns           */
	#if (DATA_BITS_MODE == 4)
		/* out the highest 4 bits of the required data to the data bus D4 --> D7 */
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (character & 0xF0);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((character & 0xF0) >> 4);
		#endif
		_delay_ms(1);                    /* delay for processing tdsw = 100ns                  */
		CLEAR_BIT(LCD_CONTROL_PORT,E);   /* E=0 .. disable LCD                                 */
		_delay_ms(1);                    /* delay for processing th = 13ns                     */
		SET_BIT(LCD_CONTROL_PORT,E);     /* E=1 .. Enable LCD                                  */
		_delay_ms(1);                    /* delay for processing tpw - tdws = 190ns            */
		/* out the lowest 4 bits of the required data to the data bus D4 --> D7 */
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((character & 0x0F) << 4);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (character & 0x0F);
		#endif
		_delay_ms(1);                    /* delay for processing tdsw = 100ns                   */
		CLEAR_BIT(LCD_CONTROL_PORT,E);   /* E=0 .. disable LCD                                  */
		_delay_ms(1);                    /* delay for processing th = 13ns                      */
	#elif (DATA_BITS_MODE == 8)
		LCD_DATA_PORT = character;       /* out the required character to the data bus D0 --> D7 */
		_delay_ms(1);                    /* delay for processing tdsw = 100ns                    */
		CLEAR_BIT(LCD_CONTROL_PORT,E);      /* E=0 .. disable LCD                                   */
		_delay_ms(1);                    /* delay for processing th = 13ns                       */
	#endif
}
/**************************************************************************************************
   [ Function Name ] : LCD_displayString
   [ Description   ] : This function is responsible for Displaying a given String at the current location
   [ Args          ] : const uint8 *str : a pointer to the constant string to be displayed
   [ Returns       ] : void
**************************************************************************************************/
void LCD_displayString(const uint8 *str)
{
	uint8 i = 0 ;
	while(str[i] != '\0')
	{
		LCD_displayCharacter(str[i]);
		i++ ;
	}
}
/**************************************************************************************************
   [ Function Name ] : LCD_displayStringRowCol
   [ Description   ] : This function is responsible for Displaying a given String at a specific location
   [ Args          ] : uint8 row : should Be 0 , 1 , 2 or 3 in case of 4 Lines LCD.
   	   	   	   	   	   uint8 col : should Be 0 , 1 , .. , 15 .
   	   	   	   	   	   const uint8 *str : a pointer to the constant string to be displayed
   [ Returns       ] : void
**************************************************************************************************/
void LCD_displayStringRowCol(uint8 row , uint8 col , const uint8 *str)
{
	LCD_goToRowCol(row , col ) ;
	LCD_displayString(str) ;
}

/**************************************************************************************************
   [ Function Name ] : LCD_goToRowCol
   [ Description   ] : This function is responsible for Moving the Cursor to a specific location
   [ Args          ] : uint8 row : should Be 0 , 1 , 2 or 3 in case of 4 Lines LCD.
   	   	   	   	   	   uint8 col : should Be 0 , 1 , .. , 15 .
   [ Returns       ] : void
**************************************************************************************************/
void LCD_goToRowCol(uint8 row , uint8 col )
{
	uint8 address ;  /* will store the LCD Cell Mapped Address */
	switch(row)
	{
		case 0 : address = col ;
			break ;
		case 1 : address = col + 0x40 ;
			break ;
		case 2 : address = col + 0x10 ;
			break ;
		case 3 : address = col + 0x50 ;
			break ;
	}
	/* To write at a specific address we must send this command to LCD : 0b1000 0000 + address */
	LCD_sendCommand(SET_CURSOR_POSITION | address ) ;
}
/**************************************************************************************************
   [ Function Name ] : LCD_clearDisplay
   [ Description   ] : This function is responsible for Clearing the LCD
   [ Args          ] : void
   [ Returns       ] : void
**************************************************************************************************/
void LCD_clearDisplay(void)
{
	LCD_sendCommand(CLEAR_DISPLAY) ;
}
/**************************************************************************************************
   [ Function Name ] : LCD_integerToString
   [ Description   ] : This function is responsible for Displaying Numbers on the LCD
   [ Args          ] : int
   [ Returns       ] : void
**************************************************************************************************/
void LCD_integerToString(int number)
{
	char buffer[16] ;
	itoa(number , buffer , 10 ) ;
	LCD_displayString(buffer) ;
}
