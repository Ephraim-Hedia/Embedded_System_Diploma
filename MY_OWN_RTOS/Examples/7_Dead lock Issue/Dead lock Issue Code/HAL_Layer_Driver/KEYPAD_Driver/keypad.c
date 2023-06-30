/*
 * keypad.c
 *
 *  Created on: Nov 27, 2022
 *      Author: Guirguis
 */


#include  "keypad.h"
GPIO_PinConfig_t pinconfig;


static uint8_t KeypadContent[4][4]={
		{'7'  ,  '8' , '9' , '/'},
		{'4'  ,  '5' , '6' , '*'},
		{'1'  ,  '2' , '3' , '-'},
		{'C'  ,  '0' , '=' , '+'}
};

void KEYPAD_INIT()
{

	//Define Rows as input
	pinconfig.GPIO_PinNumber =KEYPAD_R0;
	pinconfig.GPIO_Mode=GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfig);

	pinconfig.GPIO_PinNumber =KEYPAD_R1;
	pinconfig.GPIO_Mode=GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfig);

	pinconfig.GPIO_PinNumber =KEYPAD_R2;
	pinconfig.GPIO_Mode=GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfig);

	pinconfig.GPIO_PinNumber =KEYPAD_R3;
	pinconfig.GPIO_Mode=GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfig);


	//Define Colums as OUPUT
	pinconfig.GPIO_PinNumber =KEYPAD_C0;
	pinconfig.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfig);

	pinconfig.GPIO_PinNumber =KEYPAD_C1;
	pinconfig.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfig);

	pinconfig.GPIO_PinNumber =KEYPAD_C2;
	pinconfig.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfig);

	pinconfig.GPIO_PinNumber =KEYPAD_C3;
	pinconfig.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	pinconfig.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfig);



}
uint8_t KEYPAD_GETCHAR()
{
	int i =0;
	for(i=0;i<4;i++)
	{
		MCAL_GPIO_Write_Nibble(KEYPAD_PORT, KEYPAD_COLUM_NIBBLE, 0x0F);
		switch (i)
		{
		case 0:
			MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_C0, 0);
			break;
		case 1:
			MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_C1, 0);
			break;
		case 2:
			MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_C2, 0);
			break;
		case 3:
			MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_C3, 0);
			break;
		default:
			break;
		}

		if(!MCAL_GPIO_ReadPin(KEYPAD_PORT, KEYPAD_R0))
		{
			while(!MCAL_GPIO_ReadPin(KEYPAD_PORT, KEYPAD_R0));
			return KeypadContent[0][i];
		}

		if(!MCAL_GPIO_ReadPin(KEYPAD_PORT, KEYPAD_R1))
		{
			while(!MCAL_GPIO_ReadPin(KEYPAD_PORT, KEYPAD_R1));
			return KeypadContent[1][i];
		}

		if(!MCAL_GPIO_ReadPin(KEYPAD_PORT, KEYPAD_R2))
		{
			while(!MCAL_GPIO_ReadPin(KEYPAD_PORT, KEYPAD_R2));
			return KeypadContent[2][i];
		}

		if(!MCAL_GPIO_ReadPin(KEYPAD_PORT, KEYPAD_R3))
		{
			while(!MCAL_GPIO_ReadPin(KEYPAD_PORT, KEYPAD_R3));
			return KeypadContent[3][i];
		}

	}
	return 'N';

}
