/********************************************************************************/
/* Author 			: Guirguis Hedia 											*/
/* Date 			: 27 Feb 2023												*/
/* Version 			: V01														*/
/********************************************************************************/

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H



				/*Options for Ports*/
#define GPIOA													0
#define GPIOB													1
#define GPIOC													2

				/*Options for PINS*/
#define GPIO_PIN0												0
#define GPIO_PIN1												1
#define GPIO_PIN2												2
#define GPIO_PIN3												3
#define GPIO_PIN4												4
#define GPIO_PIN5												5
#define GPIO_PIN6												6
#define GPIO_PIN7												7
#define GPIO_PIN8												8
#define GPIO_PIN9												9
#define GPIO_PIN10												10
#define GPIO_PIN11												11
#define GPIO_PIN12												12
#define GPIO_PIN13												13
#define GPIO_PIN14												14
#define GPIO_PIN15												15

				/*Options for Input Modes*/
#define GPIO_INPUT_ANALOG										0b0000
#define GPIO_INPUT_FLOATING										0b0100
#define GPIO_INPUT_PULL_UP										0b1000
#define GPIO_INPUT_PULL_DOWN									0b1000


		/*Options for OUTPUT Modes with 10MHz Speed*/
#define GPIO_OUTPUT_SPEED_10MHz_PP								0b0001
#define GPIO_OUTPUT_SPEED_10MHz_OP								0b0101
#define GPIO_ALTER_OUTPUT_SPEED_10MHz_PP						0b1001
#define GPIO_ALTER_OUTPUT_SPEED_10MHz_OP						0b1101

		/*Options for OUTPUT Modes with 2MHz Speed*/
#define GPIO_OUTPUT_SPEED_2MHz_PP								0b0010
#define GPIO_OUTPUT_SPEED_2MHz_OP								0b0110
#define GPIO_ALTER_OUTPUT_SPEED_2MHz_PP							0b1010
#define GPIO_ALTER_OUTPUT_SPEED_2MHz_OP							0b1110

		/*Options for OUTPUT Modes with 50MHz Speed*/
#define GPIO_OUTPUT_SPEED_50MHz_PP								0b0011
#define GPIO_OUTPUT_SPEED_50MHz_OP								0b0111
#define GPIO_ALTER_OUTPUT_SPEED_50MHz_PP						0b1011
#define GPIO_ALTER_OUTPUT_SPEED_50MHz_OP						0b1111

				/*Options for Pin Value*/
#define GPIO_HIGH												1
#define GPIO_LOW												0





				/*Options for Byte Position*/
#define GPIO_BYTE_POSITION_HIGH		1
#define GPIO_BYTE_POSITION_LOW		0

				/*Options for Byte Dir Value*/

				/*Options for Input Modes*/
#define GPIO_BYTE_INPUT_ANALOG									(u32)0x00000000
#define GPIO_BYTE_INPUT_FLOATING								(u32)0x44444444
#define GPIO_BYTE_INPUT_PULL_UP									(u32)0x88888888
#define GPIO_BYTE_INPUT_PULL_DOWN								(u32)0b88888888


		/*Options for OUTPUT Modes with 10MHz Speed*/
#define GPIO_BYTE_OUTPUT_SPEED_10MHz_PP							(u32)0x11111111
#define GPIO_BYTE_OUTPUT_SPEED_10MHz_OP							(u32)0x55555555
#define GPIO_BYTE_ALTER_OUTPUT_SPEED_10MHz_PP					(u32)0x99999999
#define GPIO_BYTE_ALTER_OUTPUT_SPEED_10MHz_OP					(u32)0xDDDDDDDD

		/*Options for OUTPUT Modes with 2MHz Speed*/
#define GPIO_BYTE_OUTPUT_SPEED_2MHz_PP							(u32)0x22222222
#define GPIO_BYTE_OUTPUT_SPEED_2MHz_OP							(u32)0x66666666
#define GPIO_BYTE_ALTER_OUTPUT_SPEED_2MHz_PP					(u32)0xAAAAAAAA
#define GPIO_BYTE_ALTER_OUTPUT_SPEED_2MHz_OP					(u32)0xEEEEEEEE

		/*Options for OUTPUT Modes with 50MHz Speed*/
#define GPIO_BYTE_OUTPUT_SPEED_50MHz_PP							(u32)0x33333333
#define GPIO_BYTE_OUTPUT_SPEED_50MHz_OP							(u32)0x77777777
#define GPIO_BYTE_ALTER_OUTPUT_SPEED_50MHz_PP					(u32)0xBBBBBBBB
#define GPIO_BYTE_ALTER_OUTPUT_SPEED_50MHz_OP					(u32)0xFFFFFFFF


				/*Options for Nibble Position*/
#define GPIO_NIBBLE_LOW_BYTE_LOW								0
#define GPIO_NIBBLE_HIGH_BYTE_LOW								1
#define GPIO_NIBBLE_LOW_BYTE_HIGH								2
#define GPIO_NIBBLE_HIGH_BYTE_HIGH								3

				/*Options for Nibble Dir Value*/

				/*Options for Input Modes*/
#define GPIO_NIBBLE_INPUT_ANALOG								(u16)0x0000
#define GPIO_NIBBLE_INPUT_FLOATING								(u16)0x4444
#define GPIO_NIBBLE_INPUT_PULL_UP								(u16)0x8888
#define GPIO_NIBBLE_INPUT_PULL_DOWN								(u16)0b8888


		/*Options for OUTPUT Modes with 10MHz Speed*/
#define GPIO_NIBBLE_OUTPUT_SPEED_10MHz_PP						(u16)0x1111
#define GPIO_NIBBLE_OUTPUT_SPEED_10MHz_OP						(u16)0x5555
#define GPIO_NIBBLE_ALTER_OUTPUT_SPEED_10MHz_PP					(u16)0x9999
#define GPIO_NIBBLE_ALTER_OUTPUT_SPEED_10MHz_OP					(u16)0xDDDD

		/*Options for OUTPUT Modes with 2MHz Speed*/
#define GPIO_NIBBLE_OUTPUT_SPEED_2MHz_PP						(u16)0x2222
#define GPIO_NIBBLE_OUTPUT_SPEED_2MHz_OP						(u16)0x6666
#define GPIO_NIBBLE_ALTER_OUTPUT_SPEED_2MHz_PP					(u16)0xAAAA
#define GPIO_NIBBLE_ALTER_OUTPUT_SPEED_2MHz_OP					(u16)0xEEEE

		/*Options for OUTPUT Modes with 50MHz Speed*/
#define GPIO_NIBBLE_OUTPUT_SPEED_50MHz_PP						(u16)0x3333
#define GPIO_NIBBLE_OUTPUT_SPEED_50MHz_OP						(u16)0x7777
#define GPIO_NIBBLE_ALTER_OUTPUT_SPEED_50MHz_PP					(u16)0xBBBB
#define GPIO_NIBBLE_ALTER_OUTPUT_SPEED_50MHz_OP					(u16)0xFFFF





void MGPIO_voidSetPinDir(u8 Copy_u8PortId,u8 Copy_u8PinId,u8 Copy_u8PinMode);

void MGPIO_voidSetPinVal(u8 Copy_u8PortId,u8 Copy_u8PinId,u8 Copy_u8PinVal);

u16 MGPIO_voidGetPinVal(u8 Copy_u8PortId,u8 Copy_u8PinId);

void MGPIO_voidTogglePin(u8 Copy_u8PortId,u8 Copy_u8PinId);


void MGPIO_voidSetNibbleDir(u8 Copy_u8PortId,u8 Copy_NibblePosition,u16 Copy_u8NibbleDir);

void MGPIO_voidSetNibbleVal(u8 Copy_u8PortId,u8 Copy_NibblePosition,u8 Copy_u8NibbleVal);



void MGPIO_voidSetByteDir(u8 Copy_u8PortId,u8 Copy_BytePosition,u32 Copy_u8ByteDir);

void MGPIO_voidSetByteVal(u8 Copy_u8PortId,u8 Copy_BytePosition,u8 Copy_u8ByteVal);

u8 MGPIO_voidGetByteVal(u8 Copy_u8PortId,u8 Copy_BytePosition);


#endif
