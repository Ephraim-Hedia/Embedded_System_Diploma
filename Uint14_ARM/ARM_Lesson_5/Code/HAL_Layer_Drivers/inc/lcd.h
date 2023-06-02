/*
 * lcd.h
 *
 * Created: 11/2/2022 10:36:28 PM
 *  Author: ff
 */ 


#ifndef LCD_H_
#define LCD_H_

//Includes
#include "stm32f103x6.h"
#include "STM32_F103C6_GPIO_Driver.h"


#define LCD_PORT			GPIOA
#define LCD_CTRL_PORT		GPIOA
#define LCD_NIBBLE			GPIO_SECOND_NIBBLE
#define LCD_BYTE			GPIO_FIRST_BYTE

#define RS_SWITCH		GPIO_PIN_1
#define RW_SWITCH		GPIO_PIN_2
#define ENABLE_SWITCH	GPIO_PIN_3

//#define LCD_EIGHT_BIT_MODE
#define LCD_FOUR_BIT_MODE

#define LCD_FUNCTION_8BIT_2LINES		(0x38)
#define LCD_FUNCTION_4BIT_2LINES		(0x28)
#define LCD_MOVE_DISP_RIGHT				(0x1C)
#define LCD_MOVE_DISP_LEFT				(0x18)
#define LCD_MOVE_CURSOR_RIGHT			(0x14)
#define LCD_MOVE_CURSOR_LEFT			(0x10)
#define LCD_DISP_OFF					(0x08)
#define LCD_DISP_ON_CURSOR		   		(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   		(0x0F)
#define LCD_DISP_ON_BLINK		   		(0x0D)
#define LCD_DISP_ON						(0x0C)
#define LCD_ENTRY_DEC					(0x04)
#define LCD_ENTRY_DEC_SHIFT				(0x05)
#define LCD_ENTRY_INC					(0x06)
#define LCD_ENTRY_INC_SHIFT				(0x07)
#define LCD_BEGIN_AT_FIRST_ROW			(0x80)
#define LCD_BEGIN_AT_SECOND_ROW			(0xC0)
#define LCD_CLEAR_SCREEN				(0x01)
#define LCD_ENTRY_MODE					(0x06)






//APIs for LCD
void LCD_INIT(void);
void LCD_WRITE_COMMAND(unsigned char command);
void LCD_WRITE_CHAR(unsigned char data);
void LCD_WRITE_STRING(char* data);
void LCD_isbusy(void);
void LCD_CLR_SCREEN();
void LCD_GOTO_XY(int line , int position);
void delay(uint32_t time);

#endif /* LCD_H_ */
