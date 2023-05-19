/*
 * STM32_F103C6_SPI_Driver.c
 *
 *  Created on: Dec 2, 2022
 *      Author: Guirguis
 */

#include "STM32_F103C6_SPI_Driver.h"

/*
 * =========================================================
 * 						Generic Variables
 * =========================================================
 */
SPI_Config* Global_SPI_Config[2]={NULL,NULL};

SPI_Config Global_SPI_Config1;
SPI_Config Global_SPI_Config2;

/*
 * =========================================================
 * 						Generic Macros
 * =========================================================
 */
#define SPI1_INDEX			0
#define SPI2_INDEX			1


#define SPI_SR_TXE			((uint8_t)0x02)
#define SPI_SR_RXNE			((uint8_t)0x01)

/*
 * =========================================================
 * 								AIPs
 * =========================================================
 */

/*==========================================================================================
 * @Fn						-MCAL_SPI_Init
 * @brief					- Initializes the SPI according to the specified Parameters
 * @param[in]				- SPIx: where x can be (1..2 depending on device used)
 * @param[in]				- SPI_Config :All SPI configuration SPI_PinConfig_t
 * @retval					-none
 * Note						-Support for SPI Full Duplex Master/slave Only & NSS HW /SW
 * 							-in case of master you have to configure pin and drive it
 *==========================================================================================
 */
void MCAL_SPI_Init(SPI_TypeDef * SPIx,SPI_Config * SPI_config)
{
	//Safety for Registers
	uint16_t tmpreg_CR1=0;
	uint16_t tmpreg_CR2=0;

	if(SPIx == SPI1)
	{
		Global_SPI_Config1 = *SPI_config;
		Global_SPI_Config[SPI1_INDEX]=&Global_SPI_Config1;
		RCC_SPI1_CLK_EN();
	}else if (SPIx==SPI2)
	{
		Global_SPI_Config2 = *SPI_config;
		Global_SPI_Config[SPI2_INDEX]=&Global_SPI_Config2;
		RCC_SPI2_CLK_EN();
	}

	//1- Enable SPI CR1:BIT6 -->SPE:SPI Enable
	tmpreg_CR1 = (0x1U<<6);

	//2-Master or Slave
	tmpreg_CR1 |= SPI_config->Device_Mode;

	//3-SPI_Communication_Mode
	tmpreg_CR1 |= SPI_config->Communication_Mode;

	//4-SPI_Frame_FOrmat
	tmpreg_CR1 |= SPI_config->Frame_Format;

	//5-SPI_Data_Size
	tmpreg_CR1 |= SPI_config->DataSize;

//	6-SPI_Clock_Polarity
	tmpreg_CR1 |= SPI_config->CLKPolarity;

	//7-SPI_Clock_Phase
	tmpreg_CR1 |= SPI_config->CLKPhase;

//======================NSS===========================
	if (SPI_config->NSS == SPI_NSS_Hard_Master_SS_ouput_enable)
	{
		tmpreg_CR2 |= SPI_config->NSS;
	}else if (SPI_config->NSS == SPI_NSS_Hard_Master_SS_ouput_disable)
	{
		tmpreg_CR2 &= SPI_config->NSS;
	}else
	{
		tmpreg_CR1 |= SPI_config->NSS;
	}
//=================================================
//SPI_BAUDRATEPRESCALER
	tmpreg_CR1 |= SPI_config->SPI_BAUDRATEPRESCALER;

//=================================================
	if(SPI_config->IRQ_Enable != SPI_IRQ_Enable_NONE)
	{
		//SPI_IRQ_Enable_define
		tmpreg_CR2 |=SPI_config->IRQ_Enable;
		if(SPIx==SPI1)
			NVIC_IRQ35_SPI1_Enable;
		else if (SPIx == SPI2)
			NVIC_IRQ36_SPI2_Enable;
	}

	SPIx->SPI_CR1=(uint32_t)tmpreg_CR1;
	SPIx->SPI_CR2=(uint32_t)tmpreg_CR2;

}





void MCAL_SPI_DeInit(SPI_TypeDef *SPIx)
{
	if(SPIx==SPI1)
	{
		NVIC_IRQ35_SPI1_Disable;
		RCC_SPI1_Reset();
	}else if (SPIx == SPI2)
	{
		NVIC_IRQ36_SPI2_Disable;
		RCC_SPI2_Reset();
	}

}


void MCAL_SPI_SendData (SPI_TypeDef *SPIx,uint16_t *pTxBuffer,enum PollingMechism PollingEn)
{
	if(PollingEn == Pollingenable)
		while(!((SPIx->SPI_SR)&SPI_SR_TXE));

	SPIx->SPI_DR=*pTxBuffer;

}

void MCAL_SPI_ReceiveData (SPI_TypeDef *SPIx,uint16_t *pRxBuffer,enum PollingMechism PollingEn)
{
	if(PollingEn == Pollingenable)
		while(!((SPIx->SPI_SR)&SPI_SR_RXNE));

	*pRxBuffer=SPIx->SPI_DR;
}



void MCAL_SPI_TX_RX (SPI_TypeDef *SPIx,uint16_t *pTxBuffer,enum PollingMechism PollingEn)
{

	if(PollingEn == Pollingenable)
		while(!((SPIx->SPI_SR)&SPI_SR_TXE));
	SPIx->SPI_DR =*pTxBuffer;

	if(PollingEn == Pollingenable)
		while(!((SPIx->SPI_SR)&SPI_SR_RXNE));
	*pTxBuffer=SPIx->SPI_DR;
}

void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef * SPIx)
{
	GPIO_PinConfig_t PinCfg;
	if(SPIx==SPI1)
	{
//		 PA4:SPI1_NSS
//		 PA5:SPI1_SCK
//		 PA6:SPI1_MISO
//		 PA7:SPI1_MOSI
		if(Global_SPI_Config[SPI1_INDEX]->Device_Mode == SPI_Decive_Mode_MASTER)
		{
//			PA4:SPI1_NSS
			switch(Global_SPI_Config[SPI1_INDEX]->NSS)
			{
			case SPI_NSS_Hard_Master_SS_ouput_disable:
				//Hardware master /Slave --> INPUT FLOATING
				PinCfg.GPIO_PinNumber=GPIO_PIN_4;
				PinCfg.GPIO_Mode=GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
				break;

			case SPI_NSS_Hard_Master_SS_ouput_enable:
				PinCfg.GPIO_PinNumber=GPIO_PIN_4;
				PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_AF_PP;
				PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
				break;
			}


			//		PA5:SPI1_SCK
			//		Master Alternate Function Push-pull
			PinCfg.GPIO_PinNumber=GPIO_PIN_5;
			PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);



			//		PA6:SPI1_MISO (Supported Only Full Duplex)
			//		Full Duplex /Master input floating
			PinCfg.GPIO_PinNumber=GPIO_PIN_6;
			PinCfg.GPIO_Mode=GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
			//To do support Half duplex and simplex



			//		 PA7:SPI1_MOSI
			//		Full duplex /master Alternative function Push-pull
			PinCfg.GPIO_PinNumber=GPIO_PIN_7;
			PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);


		}else //Slave
		{
//			PA4:SPI1_NSS
			if(Global_SPI_Config[SPI1_INDEX]->NSS == SPI_NSS_Hard_Slave)
			{
				//Hardware master /slave Input Floating
				PinCfg.GPIO_PinNumber=GPIO_PIN_4;
				PinCfg.GPIO_Mode=GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
			}

			//PA5 :SPI1_SCK
			//Slave INPUT FLOATING
			PinCfg.GPIO_PinNumber = GPIO_PIN_5;
			PinCfg.GPIO_Mode=GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//		 PA6:SPI1_MISO(Supported Only full Duplex)
			//		Full Duplex /Slave (Point to Point) Alternate Function PUSH PULL
			PinCfg.GPIO_PinNumber=GPIO_PIN_6;
			PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//PA7:SPI1_MOSI
			//FULL Duplex/Slave Input Floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_7;
			PinCfg.GPIO_Mode=GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

		}


	}else if(SPIx == SPI2)
	{
//		 PB12:SPI2_NSS
//		 PB13:SPI2_SCK
//		 PB14:SPI2_MISO
//		 PB15:SPI2_MOSI
		if(Global_SPI_Config[SPI2_INDEX]->Device_Mode == SPI_Decive_Mode_MASTER)
		{


//			PB12:SPI2_NSS
			switch(Global_SPI_Config[SPI2_INDEX]->NSS)
			{
			case SPI_NSS_Hard_Master_SS_ouput_disable:
				//Hardware master /Slave --> INPUT FLOATING
				PinCfg.GPIO_PinNumber=GPIO_PIN_12;
				PinCfg.GPIO_Mode=GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
				break;

			case SPI_NSS_Hard_Master_SS_ouput_enable:
				PinCfg.GPIO_PinNumber=GPIO_PIN_12;
				PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_AF_PP;
				PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
				break;
			}


			//		PB13:SPI2_SCK
			//		Master Alternate Function Push-pull
			PinCfg.GPIO_PinNumber=GPIO_PIN_13;
			PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);



			//		PB14:SPI2_MISO (Supported Only Full Duplex)
			//		Full Duplex /Master input floating
			PinCfg.GPIO_PinNumber=GPIO_PIN_14;
			PinCfg.GPIO_Mode=GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
			//To do support Half duplex and simplex



			//		 PB15:SPI2_MOSI
			//		Full duplex /master Alternative function Push-pull
			PinCfg.GPIO_PinNumber=GPIO_PIN_15;
			PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);


		}else //Slave
		{
			//			PB12:SPI2_NSS
			if(Global_SPI_Config[SPI2_INDEX]->NSS == SPI_NSS_Hard_Slave)
			{
				//Hardware master /slave Input Floating
				PinCfg.GPIO_PinNumber=GPIO_PIN_12;
				PinCfg.GPIO_Mode=GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
			}

			//PB13:SPI2_SCK
			//Slave INPUT FLOATING
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_Mode=GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//		 PB14:SPI2_MISO(Supported Only full Duplex)
			//		Full Duplex /Slave (Point to Point) Alternate Function PUSH PULL
			PinCfg.GPIO_PinNumber=GPIO_PIN_14;
			PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//PB15:SPI2_MOSI
			//FULL Duplex/Slave Input Floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_15;
			PinCfg.GPIO_Mode=GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

		}

	}
}





/*
 * =========================================================
 * 								IRQ
 * =========================================================
 */

void SPI1_IRQHandler(void)
{
	struct S_IRQ_SRC irq_src;
	irq_src.TXE =((SPI1->SPI_SR & (1<<1)) >> 1);
	irq_src.RXNE =((SPI1->SPI_SR & (1<<0)) >> 0);
	irq_src.ERRI =((SPI1->SPI_SR & (1<<4)) >> 4);
	Global_SPI_Config[SPI1_INDEX]->P_IRQ_CallBack(irq_src);
}

void SPI2_IRQHandler(void)
{
	struct S_IRQ_SRC irq_src;
	irq_src.TXE =((SPI1->SPI_SR & (1<<1))>>1);
	irq_src.RXNE =((SPI1->SPI_SR & (1<<0))>>0);
	irq_src.ERRI =((SPI1->SPI_SR & (1<<4))>>4);

	Global_SPI_Config[SPI2_INDEX]->P_IRQ_CallBack(irq_src);
}






