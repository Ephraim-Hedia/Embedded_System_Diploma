/*
 * lcd.c
 *
 * Created: 11/2/2022 10:36:35 PM
 *  Author: Guirguis
 */ 

#include "lcd.h"


GPIO_PinConfig_t PinCfg;

void delay (uint32_t time)
{
	uint32_t i,j;

	for (i=0 ; i <time;i++)
		for(j=0;j<256;j++);
}

void LCD_KICK(void)
{
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, ENABLE_SWITCH, GPIO_PIN_SET);
	delay(30);//Enable instruction Delay
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, ENABLE_SWITCH, GPIO_PIN_RESET);
	delay(30);
}


void LCD_INIT(void)
{
	delay(100);

	//Initialize The Control Pins
	//ENABLE_SWITCH--> OUTPUT Push/Pull / 10M Speed //Enable Switch
	PinCfg.GPIO_PinNumber=ENABLE_SWITCH;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PinCfg);

	//RW_SWITCH--> OUTPUT Push/Pull / 10M Speed //RW Switch
	PinCfg.GPIO_PinNumber=RW_SWITCH;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PinCfg);


	//RS_SWITCH--> OUTPUT Push/Pull / 10M Speed //RS Switch
	PinCfg.GPIO_PinNumber=RS_SWITCH;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_CTRL_PORT, &PinCfg);

	//Set RW in Write Mode
	//Set RS in Command Mode
	//Set LOW to Enable
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, ENABLE_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, RS_SWITCH, GPIO_PIN_RESET);


	//Initialize The Data Pins
	//Px7 --> OUTPUT Push/Pull / 10M Speed
	PinCfg.GPIO_PinNumber=GPIO_PIN_7;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//Px6 --> OUTPUT Push/Pull / 10M Speed
	PinCfg.GPIO_PinNumber=GPIO_PIN_6;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//Px5 --> OUTPUT Push/Pull / 10M Speed
	PinCfg.GPIO_PinNumber=GPIO_PIN_5;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//Px4 --> OUTPUT Push/Pull / 10M Speed
	PinCfg.GPIO_PinNumber=GPIO_PIN_4;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);


#ifdef LCD_EIGHT_BIT_MODE
	//Px3 --> OUTPUT Push/Pull / 10M Speed
	PinCfg.GPIO_PinNumber=GPIO_PIN_3;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//Px2 --> OUTPUT Push/Pull / 10M Speed
	PinCfg.GPIO_PinNumber=GPIO_PIN_2;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//Px1 --> OUTPUT Push/Pull / 10M Speed
	PinCfg.GPIO_PinNumber=GPIO_PIN_1;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//Px0 --> OUTPUT Push/Pull / 10M Speed
	PinCfg.GPIO_PinNumber=GPIO_PIN_0;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);
#endif

	//if 8bit Mode
#ifdef LCD_EIGHT_BIT_MODE
	LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
#endif


	//if 4 bit Mode
#ifdef LCD_FOUR_BIT_MODE
	LCD_WRITE_COMMAND(0x02);
	LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
#endif
	//General configuration
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
	LCD_CLR_SCREEN();
}

void LCD_WRITE_COMMAND(unsigned char command)
{
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, RS_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, RW_SWITCH, GPIO_PIN_RESET);

#ifdef LCD_EIGHT_BIT_MODE
	MCAL_GPIO_WriteByte(LCD_PORT,GPIO_FIRST_BYTE, command);//Send Command
	LCD_KICK();//Set and Reset E bin
#endif

#ifdef LCD_FOUR_BIT_MODE
	MCAL_GPIO_Write_Nibble(LCD_CTRL_PORT, LCD_NIBBLE, (command &0xF0)>>4);//Send first nibble of command
	LCD_KICK();//Set and Reset E bin
	delay(1);

	MCAL_GPIO_Write_Nibble(LCD_CTRL_PORT, LCD_NIBBLE, (command &0x0F));//Send Second Nibble command
	LCD_KICK();//Set and Reset E bin
	delay(1);
#endif
}

void LCD_WRITE_CHAR(unsigned char data)
{
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL_PORT, RS_SWITCH, GPIO_PIN_SET);

	//If LCD in 8bit MODE
#ifdef LCD_EIGHT_BIT_MODE

	MCAL_GPIO_WriteByte(LCD_PORT,GPIO_FIRST_BYTE, data);//Send Data to LCD
	LCD_KICK();//Set and Reset E bin
#endif

	//If LCD in 4bit MODE
#ifdef LCD_FOUR_BIT_MODE

	MCAL_GPIO_Write_Nibble(LCD_PORT, LCD_NIBBLE, (data &0xF0)>>4);
	LCD_KICK();//Set and Reset E bin
	delay(1);

	MCAL_GPIO_Write_Nibble(LCD_PORT, LCD_NIBBLE,(data & 0x0F));
	LCD_KICK();//Set and Reset E bin
	delay(1);
#endif

}

void LCD_WRITE_STRING(char* data)
{
	int counter=0;
	while(*data !=0)
	{
		LCD_WRITE_CHAR(*data++);
		counter++;
		if(counter == 16)
		{
			LCD_GOTO_XY(2,0);
		}
		else if(counter ==32)
		{
			LCD_CLR_SCREEN();
			LCD_GOTO_XY(1,0);
			counter=0;
		}
	}
}

void LCD_CLR_SCREEN(void)
{
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}

void LCD_GOTO_XY(int line , int position)
{
	if(line ==1)
	{
		if(position >=0 && position < 16)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW+position);
		}
	}
	else if (line ==2){
		if(position >=0 && position < 16)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW+position);
		}
	}
}
void LCD_isbusy(void)
{
	//Initialize The Control Pins
	//PA10 --> OUTPUT Push/Pull / 10M Speed //Enable Switch
	PinCfg.GPIO_PinNumber=ENABLE_SWITCH;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA8 --> OUTPUT Push/Pull / 10M Speed //RS Switch
	PinCfg.GPIO_PinNumber=RS_SWITCH;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA9 --> OUTPUT Push/Pull / 10M Speed //RW_SWITCH
	PinCfg.GPIO_PinNumber=RW_SWITCH;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);


	//Initialize The Data Pins
	//PA7 --> INPUT Floating
	PinCfg.GPIO_PinNumber=GPIO_PIN_7;
	PinCfg.GPIO_Mode=GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA6 -->INPUT Floating
	PinCfg.GPIO_PinNumber=GPIO_PIN_6;
	PinCfg.GPIO_Mode=GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA5 --> INPUT Floating
	PinCfg.GPIO_PinNumber=GPIO_PIN_5;
	PinCfg.GPIO_Mode=GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);


	//PA4 --> INPUT Floating
	PinCfg.GPIO_PinNumber=GPIO_PIN_4;
	PinCfg.GPIO_Mode=GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA3 --> INPUT Floating
	PinCfg.GPIO_PinNumber=GPIO_PIN_3;
	PinCfg.GPIO_Mode=GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA2 --> INPUT Floating
	PinCfg.GPIO_PinNumber=GPIO_PIN_2;
	PinCfg.GPIO_Mode=GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA1 --> INPUT Floating
	PinCfg.GPIO_PinNumber=GPIO_PIN_1;
	PinCfg.GPIO_Mode=GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA0 --> INPUT Floating
	PinCfg.GPIO_PinNumber=GPIO_PIN_0;
	PinCfg.GPIO_Mode=GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);


	MCAL_GPIO_WritePin(GPIOA, RW_SWITCH, GPIO_PIN_SET);// set Read Mode
	MCAL_GPIO_WritePin(GPIOA, RS_SWITCH, GPIO_PIN_RESET);//set Command Mode

	LCD_KICK();//Reset and Set The Enable


	//Now reset The Initial Mode
	//Initialize The Data Pins
	//PA7 --> OUTPUT Push/Pull / 10M Speed
	PinCfg.GPIO_PinNumber=GPIO_PIN_7;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA6 --> OUTPUT Push/Pull / 10M Speed
	PinCfg.GPIO_PinNumber=GPIO_PIN_6;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA5 --> OUTPUT Push/Pull / 10M Speed
	PinCfg.GPIO_PinNumber=GPIO_PIN_5;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);


	//PA4 --> OUTPUT Push/Pull / 10M Speed
	PinCfg.GPIO_PinNumber=GPIO_PIN_4;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA3 --> OUTPUT Push/Pull / 10M Speed
	PinCfg.GPIO_PinNumber=GPIO_PIN_3;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA2 --> OUTPUT Push/Pull / 10M Speed
	PinCfg.GPIO_PinNumber=GPIO_PIN_2;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA1 --> OUTPUT Push/Pull / 10M Speed
	PinCfg.GPIO_PinNumber=GPIO_PIN_1;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	//PA0 --> OUTPUT Push/Pull / 10M Speed
	PinCfg.GPIO_PinNumber=GPIO_PIN_0;
	PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
	MCAL_GPIO_Init(LCD_PORT, &PinCfg);

	MCAL_GPIO_WritePin(LCD_CTRL_PORT, RW_SWITCH, GPIO_PIN_RESET);
}


