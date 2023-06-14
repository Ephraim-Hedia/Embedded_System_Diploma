/*
 * STM32_F103C6_GPIO_Driver.h
 *
 *  Created on: Oct 24, 2022
 *      Author: ff
 */

#ifndef INC_STM32_F103C6_GPIO_DRIVER_H_
#define INC_STM32_F103C6_GPIO_DRIVER_H_

//Includes
#include "stm32f103x6.h"

//=================================================

//Config Structure

typedef struct
{
	uint16_t GPIO_PinNumber;//Specifies The GPIO PINs to be Configured
							//This Parameter must be Set based on  @ref GPIO_PINS_define

	uint8_t  GPIO_Mode ;	//Specifies The Operation mode for The Selected Pins
							//This Parameters Can be a value of @ref GPIO_MODE_define


	uint8_t GPIO_Output_Speed ;	//Specifies The Speed for The Selected Pins
								//This Parameters Can be a value of @ref GPIO_SPEED_define

}GPIO_PinConfig_t;







//==============================
//Macros Configuration Reference
//==============================

//@ref GPIO_PINS_define
#define GPIO_PIN_0			((uint16_t)0x0001) /*Pin 0 Selected */
#define GPIO_PIN_1			((uint16_t)0x0002) /*Pin 1 Selected */
#define GPIO_PIN_2			((uint16_t)0x0004) /*Pin 2 Selected */
#define GPIO_PIN_3			((uint16_t)0x0008) /*Pin 3 Selected */
#define GPIO_PIN_4			((uint16_t)0x0010) /*Pin 4 Selected */
#define GPIO_PIN_5			((uint16_t)0x0020) /*Pin 5 Selected */
#define GPIO_PIN_6			((uint16_t)0x0040) /*Pin 6 Selected */
#define GPIO_PIN_7			((uint16_t)0x0080) /*Pin 7 Selected */
#define GPIO_PIN_8			((uint16_t)0x0100) /*Pin 8 Selected */
#define GPIO_PIN_9			((uint16_t)0x0200) /*Pin 9 Selected */
#define GPIO_PIN_10			((uint16_t)0x0400) /*Pin 10 Selected */
#define GPIO_PIN_11			((uint16_t)0x0800) /*Pin 11 Selected */
#define GPIO_PIN_12			((uint16_t)0x1000) /*Pin 12 Selected */
#define GPIO_PIN_13			((uint16_t)0x2000) /*Pin 13 Selected */
#define GPIO_PIN_14			((uint16_t)0x4000) /*Pin 14 Selected */
#define GPIO_PIN_15			((uint16_t)0x8000) /*Pin 15 Selected */
#define GPIO_PIN_ALL		((uint16_t)0xFFFF) /*All Pins is Selected */

#define GPIO_PIN_MASK		0x0000FFFFu 	/*PIN mask for assert test*/



//@ref GPIO_MODE_define

//0: Analog mode
//1: Floating input (reset state)
//2: Input with pull-up
//3: pull-down
//4: General purpose output push-pull
//5: General purpose output Open-drain
//6: Alternate function output Push-pull
//7: Alternate function output Open-drain
//8: Alternate function INPUT

#define GPIO_MODE_Analog					0x00000000u	//Analog mode
#define GPIO_MODE_INPUT_FLO					0x00000001u	//Floating input (reset state)
#define GPIO_MODE_INPUT_PU					0x00000002u	//Input with pull-up
#define GPIO_MODE_INPUT_PD					0x00000003u	//pull-down
#define GPIO_MODE_OUTPUT_PP					0x00000004u	//General purpose output push-pull
#define GPIO_MODE_OUTPUT_OD					0x00000005u	//General purpose output Open-drain
#define GPIO_MODE_OUTPUT_AF_PP				0x00000006u	//Alternate function output Push-pull
#define GPIO_MODE_OUTPUT_AF_OD				0x00000007u	//Alternate function output Open-drain
#define GPIO_MODE_AF_INPUT					0x00000008u	//Alternate function INPUT



//@ref GPIO_SPEED_define
//01: Output mode, max speed 10 MHz.
//10: Output mode, max speed 2 MHz.
//11: Output mode, max speed 50 MHz.
#define GPIO_SPEED_10M	0x00000001u //01: Output mode, max speed 10 MHz.
#define GPIO_SPEED_2M	0x00000002u //10: Output mode, max speed 2 MHz.
#define GPIO_SPEED_50M	0x00000003u //11: Output mode, max speed 50 MHz.



//@ref GPIO_PIN_state
#define GPIO_PIN_SET	1
#define GPIO_PIN_RESET	0



//@ref GPIO_RETURN_LOCK
#define GPIO_RETURN_LOCK_OK			1
#define GPIO_RETURN_LOCK_ERROR		0


//@ref GPIO_Byte_Number_define

#define GPIO_FIRST_BYTE					0
#define GPIO_SECOND_BYTE				1


//@ref GPIO_Byte_Number_define

#define GPIO_FIRST_NIBBLE					0
#define GPIO_SECOND_NIBBLE					1
#define GPIO_THIRD_NIBBLE					2
#define GPIO_FOURTH_NIBBLE					3

/*
 *
 * =======================================================================
 * 						APIS Supported by "MCAL GPIO DRIVER"
 * =======================================================================
 */


void MCAL_GPIO_Init(GPIO_TypeDef * GPIOx , GPIO_PinConfig_t* PinConfig);
void MCAL_GPIO_DeInit(GPIO_TypeDef * GPIOx);


uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef * GPIOx,uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef * GPIOx);

void MCAL_GPIO_WritePin(GPIO_TypeDef * GPIOx,uint16_t PinNumber ,uint8_t Value);
void MCAL_GPIO_WritePort(GPIO_TypeDef * GPIOx ,uint16_t Value);//Done


void MCAL_GPIO_TogglePin(GPIO_TypeDef * GPIOx,uint16_t PinNumber);

uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef * GPIOx,uint16_t PinNumber);

void MCAL_GPIO_WriteByte(GPIO_TypeDef * GPIOx ,uint8_t GPIO_Byte_Number,uint8_t Value);

void MCAL_GPIO_Write_Nibble(GPIO_TypeDef * GPIOx ,uint8_t GPIO_Nibble_Number,uint8_t Value);

#endif /* INC_STM32_F103C6_GPIO_DRIVER_H_ */
