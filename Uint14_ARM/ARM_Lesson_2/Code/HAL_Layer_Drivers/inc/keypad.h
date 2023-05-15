/*
 * keypad.h
 *
 *  Created on: Nov 27, 2022
 *      Author: ff
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

#include "STM32_F103C6_GPIO_Driver.h"

#define KEYPAD_PORT					GPIOA
#define KEYPAD_BYTE					GPIO_SECOND_BYTE
#define KEYPAD_COLUM_NIBBLE			GPIO_FOURTH_NIBBLE
#define KEYPAD_ROW_NIBBLE			GPIO_THIRD_NIBBLE

#define KEYPAD_R0	GPIO_PIN_8
#define KEYPAD_R1	GPIO_PIN_9
#define KEYPAD_R2   GPIO_PIN_10
#define KEYPAD_R3	GPIO_PIN_11
#define KEYPAD_C0	GPIO_PIN_12
#define KEYPAD_C1	GPIO_PIN_13
#define KEYPAD_C2	GPIO_PIN_14
#define KEYPAD_C3	GPIO_PIN_15

void KEYPAD_INIT();
uint8_t KEYPAD_GETCHAR();



#endif /* INC_KEYPAD_H_ */
