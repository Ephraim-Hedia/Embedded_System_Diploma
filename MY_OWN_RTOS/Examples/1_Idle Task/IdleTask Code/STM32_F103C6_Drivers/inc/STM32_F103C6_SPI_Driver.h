/*
 * STM32_F103C6_SPI_Driver.h
 *
 *  Created on: Dec 2, 2022
 *      Author: Guirguis
 */

#ifndef INC_STM32_F103C6_SPI_DRIVER_H_
#define INC_STM32_F103C6_SPI_DRIVER_H_

#include "stm32f103x6.h"
#include "STM32_F103C6_GPIO_Driver.h"

struct S_IRQ_SRC
{
	uint8_t TXE:1; 		//TX buffer empty interrupt
	uint8_t RXNE:1;		//RX buffer not empty interrupt
	uint8_t ERRI:1;		//Error interrupt
	uint8_t Reserved:5;
};

//Configuration
typedef struct
{
	uint16_t		Device_Mode ;				//Specifies the SPI Operating Mode @ref SPI_Device_Mode

	uint16_t 		Communication_Mode;			//Specifies the SPI bidirectional mode state @ref SPI_Communication_Mode

	uint16_t		Frame_Format;				//Specifies LSB or MSB @ref SPI_Frame_Format

	uint16_t		DataSize;					//@ref SPI_DataSize

	uint16_t		CLKPolarity;				//@ref SPI_CLKPolarity

	uint16_t		CLKPhase;					//@ref SPI_CLKPhase

	uint16_t		NSS;						//@ref SPI_NSS

	uint16_t		SPI_BAUDRATEPRESCALER;		/*Specifies the Baud Rate prescaler value which will be
												used to configure the transmit and receive SCK clock .
												This parameter can be a value of @ref SPI_BAUDRATEPRESCALER
												@note the communication clock is derived from the master clock.
												The Slave clock doesn't need to be set .*/
												//Take care you have to configure RCC to enter the correct clock to APB2 ->SPI1 or APB1 -->SPI2


	uint16_t		IRQ_Enable;					//@ref SPI_IRQ_Enable

	void (* P_IRQ_CallBack)(struct S_IRQ_SRC irq_src);					//Set the C Function() which will be called once the IRQ Happen
}SPI_Config;


//======================================================
//					Reference Macros
//======================================================

//@ref SPI_Device_Mode
//Bit MSTR: Master selection
#define SPI_Device_Mode_SLAVE				(0x00000000U)
#define SPI_Decive_Mode_MASTER				(0x1U<<2) 								//CP1.MSTR :1-->Master Configuration


//@ref SPI_Communication_Mode
#define SPI_DIRECTION_2LINES					(0x00000000U)
#define SPI_DIRECTION_2LINES_RXONLY				(0x1U << 10)						//CP1.Bit 10 RXONLY:Receive Only
#define SPI_DIRECTION_1LINE_receive_only		(0x1U << 15)						//CP1.BIt 15 BITMODE:bidirectional data mode enable
#define SPI_DIRECTION_1LINE_transmit_only		((0x1U << 15) | (0x1U << 14))		//CP1.Bit 15 BITMODE:bidirectional data mode enable & Bit 14 BIDIOE :OUTPUT enable in bidirectional mode

//@ref SPI_Frame_Format
#define SPI_Frame_Format_MSB_transmitted_first	(0x00000000U)
#define SPI_Frame_Format_LSB_transmitted_first	(0x1U<<7)		//Bit 7 LSBFIRST : Frame Format

//@ref SPI_DataSize
#define SPI_DataSize_8BIT						(0x00000000U)
#define SPI_DataSize_16BIT						(0x1U<<11)		//CR1. bit 11 DFF:Data Frame Format

//@ref SPI_CLKPolarity
#define SPI_CLKPolarity_LOW_when_idle			(0x00000000U)
#define SPI_CLKPolarity_HIGH_when_idle			(0x1U<<1)  		//Bit1 CR1.CPOL:Clock Polarity

//@ref SPI_CLKPhase
#define SPI_Clock_Phase_1EDGE_first_data_capture_edge			(0x00000000U)
#define SPI_Clock_phase_2EDGE_first_data_capture_edge			(0x1U<<0) //BIT 0 CR1.CPHA : CLock Phase

//@ref SPI_NSS		SPI Slave Select Management
//=======================NSS============================
//Hardware
#define SPI_NSS_Hard_Slave						(0x00000000U)
#define SPI_NSS_Hard_Master_SS_ouput_enable		(0x1U<<2)		//SPI_CR2	bit2 SSOE:SS output enable
#define SPI_NSS_Hard_Master_SS_ouput_disable	~(0x1U<<2)	//SPI_CR2	bit2 SSOE:SS output enable

//NSS is Driven SW (Master or Slave)
#define SPI_NSS_Soft_NSSInternalSoft_Reset		(0x1U<<9)
#define SPI_NSS_Soft_NSSInternalSoft_Set		((0x1U<<9)|(0x1U<<8))	//for Master & Slave
//=====================================================

//@ref SPI_BAUDRATEPRESCALER
#define SPI_BAUDRATEPRESCALER_2				(0x00000000U)
#define SPI_BAUDRATEPRESCALER_4				(0b001U<<3)
#define SPI_BAUDRATEPRESCALER_8				(0b010U<<3)
#define SPI_BAUDRATEPRESCALER_16			(0b011U<<3)
#define SPI_BAUDRATEPRESCALER_32			(0b100U<<3)
#define SPI_BAUDRATEPRESCALER_64			(0b101U<<3)
#define SPI_BAUDRATEPRESCALER_128			(0b110U<<3)
#define SPI_BAUDRATEPRESCALER_256			(0b111U<<3)

//@ref SPI_IRQ_Enable
#define SPI_IRQ_Enable_NONE					(uint32_t)(0)
#define SPI_IRQ_Enable_TXEIE				(uint32_t)(1<<7)	//SPI_CR2 bit7 :TXEIE :Tx buffer empty interrupt enable
#define SPI_IRQ_Enable_RXNEIE				(uint32_t)(1<<6)	//SPI_CR2 Bit6 :RXNEIE:RX buffer not empty interrupt enable
#define SPI_IRQ_Enable_ERRIE				(uint32_t)(1<<5)	//SPI_CR2 Bit5:ERRIE: Error interrupt enable



enum PollingMechism{
	Pollingenable,
	Pollingdisable
};
/*
 * ==========================================================
 * 				APIs Supported by "MCAL SPI DRIVER"
 * ==========================================================
 */

void MCAL_SPI_Init(SPI_TypeDef * SPIx,SPI_Config * SPI_config);
void MCAL_SPI_DeInit(SPI_TypeDef *SPIx);
void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef * SPIx);

void MCAL_SPI_SendData (SPI_TypeDef *SPIx,uint16_t *pTxBuffer,enum PollingMechism PollingEn);

void MCAL_SPI_ReceiveData (SPI_TypeDef *SPIx,uint16_t *pRxBuffer,enum PollingMechism PollingEn);

void MCAL_SPI_TX_RX (SPI_TypeDef *SPIx,uint16_t *pTxBuffer,enum PollingMechism PollingEn);








#endif /* INC_STM32_F103C6_SPI_DRIVER_H_ */
