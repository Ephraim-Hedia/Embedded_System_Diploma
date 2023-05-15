/*
 * STM32_F103C6_USART_Driver.c
 *
 *  Created on: Nov 30, 2022
 *      Author: Guirguis
 */

#include "STM32_F103C6_USART_Driver.h"

/*
 * ==========================================================================================
 * 									Generic Variables
 * ==========================================================================================
 */

	UART_Config *Global_UART_Config=NULL;



/*
 * ==========================================================================================
 * 									Generic Macros
 * ==========================================================================================
 */











/*
 * ==========================================================================================
 * 									Generic Functions
 * ==========================================================================================
 */

void (*pFun[3])(void);



/*
 * ==========================================================================================
 * 								APIs Function Definitions
 * ==========================================================================================
 */




/*==========================================================================================
 * @Fn						-MCAL_UART_Init
 * @brief					- Initializes UART (Supported feature Asynchronous Only)
 * @param[in]				- USARTx: where x can be (1..3 depending on device used)
 * @param[in]				- UART_Config :All UART configuration USART_PinConfig_t
 * @retval					-none
 * Note						-Support for Asynchronous Mode & Clock 8 MHz
 *==========================================================================================
 */
void MCAL_UART_Init(USART_TypeDef* USARTx,UART_Config *UART_config)
{
	uint32_t pclk,BRR;

	Global_UART_Config=UART_config;

	//enable the Clock for given USART peripheral
	if(USARTx==USART1)
	{
		RCC_USART1_CLK_EN();
	}
	else if(USARTx==USART2)
	{
		RCC_USART2_CLK_EN();

	}else if(USARTx==USART3)
	{
		RCC_USART3_CLK_EN();
	}

	//Enable USART Module
//	Bit 13 UE: USART enable
	USARTx->CR1 |=1<<13;

	//Enable USART Tx and Rx engines according to The USART_Mode configuration item
	USARTx->CR1 |=UART_config->USART_Mode;

	//PAYLOAD Width
	//USART->CR1 bit 12 M:Word Length
	USARTx->CR1 |=UART_config->Payload_Length;


	//Configuration of Parity control bit fields
	//USARTx->CR1  bit 10 PCE:Parity control enable		Bit 9 PS:Parity Selection
	USARTx->CR1 |=UART_config->Parity;

	//Configure the number of stop bits
	//USART_CR2 bits 13:12 STOP:STOP bits

	USARTx->CR2 |=UART_config->StopBits;


	//USART hardware flow control
	//USART->CR3 bit 9 CTSE: CTS enable 	Bit 8 RTSE :RTS enable
	USARTx->CR3 |=UART_config->HWFlowCtl;

	//Configuration of BRR(Baudrate register)
	//PCLK1 for USART2,3
	//PCLK2 for USART1

	if(USARTx==USART1)
	{
		pclk=MCAL_RCC_Get_PCLK2Freq();
	}else
	{
		pclk = MCAL_RCC_Get_PCLK1Freq();
	}
	BRR = UART_BRR_Register(pclk,UART_config->BaudRate);

	USARTx->BRR=BRR;

	//Enable / Disable Interrupt
	//USART_CR1
	if(UART_config->IRQ_Enable != UART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |= (UART_config->IRQ_Enable);
		//Enable NVIC for USARTx IRQ

		if(USARTx == USART1)
			NVIC_IRQ37_USART1_Enable;
		else if(USARTx == USART2)
			NVIC_IRQ38_USART2_Enable;
		else if(USARTx == USART3)
			NVIC_IRQ39_USART3_Enable;
	}


	if(USARTx == USART1)
		pFun[0]=UART_config->P_IRQ_CallBack;
	else if ( USARTx ==USART2)
		pFun[1]=UART_config->P_IRQ_CallBack;
	else if ( USARTx ==USART3)
		pFun[2]=UART_config->P_IRQ_CallBack;


}

/*==========================================================================================
 * @Fn						-MCAL_UART_DeInit
 * @brief					- DeInitializes UART (Supported feature Asynchronous Only)
 * @param[in]				- USARTx: where x can be (1..3 depending on device used)
 * @retval					-none
 * Note						-Support for Asynchronous Mode & Clock 8 MHz
 *==========================================================================================
 */

void MCAL_UART_DeInit(USART_TypeDef* USARTx)
{

	if (USARTx == USART1)
	{
		RCC_USART1_Reset();
		NVIC_IRQ37_USART1_Disable;
	}else if (USARTx == USART2)
	{
		RCC_USART2_Reset();
		NVIC_IRQ38_USART2_Disable;
	}else if (USARTx == USART3)
	{
		RCC_USART3_Reset();
		NVIC_IRQ39_USART3_Disable;
	}
}


/*==========================================================================================
 * @Fn						-MCAL_UART_SendData
 * @brief					- Send Buffer on UART
 * @param[in]				- USARTx: where x can be (1..3 depending on device used)
 * @param[in]				- pTxBuffer
 * @param[in]				- pollingEn Enable or Disable it
 * @retval					-none
 * Note						-Should initialize UART First
 * 							When transmitting with the parity enable (PCE bit set to 1 in the USART_CR1 register),
 * 							the value written in the MSB (bit 7 ot bit 8 depending on the data length) has no effect
 * 							because it is replaced by the parity
 * 							when receiving with the parity enable ,the value read in the MSB bit is the received Parity bit
 *==========================================================================================
 */

void MCAL_UART_SendData(USART_TypeDef* USARTx,uint16_t *pTxBuffer ,enum Polling_mechism pollingEn)
{
	//wait until TXE flag is set in the SR
	if(pollingEn == enable)
	{
		while(! (USARTx->SR & 1<<7));
	}

	//Check the USART_WordLength item for 9BIT or 8 BIT in frame

//	When transmitting with the parity enable (PCE bit set to 1 in the USART_CR1 register),
//	the value written in the MSB (bit 7 ot bit 8 depending on the data length) has no effect
//	because it is replaced by the parity
//	when receiving with the parity enable ,the value read in the MSB bit is the received Parity bit

	if(Global_UART_Config->Payload_Length == UART_Payload_Length_9B)
	{
		USARTx->DR = (*pTxBuffer & (uint16_t)0x01FF);
	}

	if(Global_UART_Config->Payload_Length == UART_Payload_Length_8B)
	{
		USARTx->DR = (*pTxBuffer & (uint8_t)0x1FF);
	}

}

void MCAL_UART_ReceiveData(USART_TypeDef* USARTx,uint16_t *pRxBuffer ,enum Polling_mechism pollingEn)
{
	//Wait till RXNE flag is set in the SR
	if (pollingEn == enable)
	{
		while (!(USARTx->SR & 1<<5));
	}

	//Check the USART_WordLength item for 9BIT or 8BIT in a frame
	if(Global_UART_Config->Payload_Length == UART_Payload_Length_9B)
	{
		if(Global_UART_Config->Parity == UART_Parity_NONE)
		{
			//no Parity so all 9bit are consider data
			*((uint16_t *)pRxBuffer) =USARTx->DR ;
		}else{

			//Parity is used , so 8Bits will be of user data and 1 bit for parity
			*((uint16_t *)pRxBuffer) =(USARTx->DR & (uint8_t)0xFF);

		}

	}else{
		if(Global_UART_Config->Parity == UART_Parity_NONE)
		{
			//no Parity so all 8bit are consider data
			*((uint16_t *)pRxBuffer) =USARTx->DR ;
		}else{

			//Parity is used , so 7Bits will be of user data and 1 bit for parity
			*((uint16_t *)pRxBuffer) =(USARTx->DR & (uint8_t)0x7F);

		}
	}

}

void MCAL_UART_WAIT_TC(USART_TypeDef* USARTx)
{
	//wait till TC flag is set in the SR
	while (!(USARTx->SR & 1<<6));

}



/*==========================================================================================
 * @Fn						-MCAL_UART_GPIO_set_pins
 * @brief					- Initialize GPIO Pins
 * @param[in]				- USARTx: where x can be (1..3 depending on device used)
 * @retval					-none
 * Note						-Should enable the corresponding ALT & GPIO in RCC clock Also Called after MCAL_UART_init()
 *==========================================================================================
 */
void MCAL_UART_GPIO_set_pins(USART_TypeDef* USARTx)
{
	GPIO_PinConfig_t PinCfg;

	if(USARTx == USART1)
	{
		//PA9 Tx 	--> Alternative output push pull
		//PA10 Rx 	--> Alternative input
		//PA11 CTS	--> input floating
		//PA12 RTS	--> Alternative output push pull

		//PA9 Tx
		PinCfg.GPIO_PinNumber = GPIO_PIN_9;
		PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		//PA10 Rx
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_Mode=GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA,&PinCfg);


		if(Global_UART_Config->HWFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config->HWFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			//PA11 CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_11;
			PinCfg.GPIO_Mode=GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA,&PinCfg);
		}
		if(Global_UART_Config->HWFlowCtl == UART_HwFlowCtl_RTS || Global_UART_Config->HWFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			//PA12 RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_12;
			PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA,&PinCfg);
		}
	}
	else if (USARTx == USART2)
	{

		 //PA2 Tx 	--> Alternative output push pull
		 //PA3 Rx 	--> Alternative input
		 //PA0 CTS	--> input floating
		 //PA1 RTS	--> Alternative output push pull

		//PA2 Tx
		PinCfg.GPIO_PinNumber = GPIO_PIN_2;
		PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		//PA3 Rx
		PinCfg.GPIO_PinNumber = GPIO_PIN_3;
		PinCfg.GPIO_Mode=GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA,&PinCfg);


		if(Global_UART_Config->HWFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config->HWFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			//PA0 CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_0;
			PinCfg.GPIO_Mode=GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA,&PinCfg);
		}
		if(Global_UART_Config->HWFlowCtl == UART_HwFlowCtl_RTS || Global_UART_Config->HWFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			//PA1 RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_1;
			PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA,&PinCfg);
		}
	}
	else if (USARTx == USART2)
	{
		//PB10 Tx 	--> Alternative output push pull
		//PB11 Rx 	--> Alternative input
		//PB13 CTS	--> input floating
		//PB14 RTS	--> Alternative output push pull

		//PB10 Tx
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		//PB11 Rx
		PinCfg.GPIO_PinNumber = GPIO_PIN_11;
		PinCfg.GPIO_Mode=GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOB,&PinCfg);


		if(Global_UART_Config->HWFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config->HWFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			//PB13 CTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_Mode=GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB,&PinCfg);
		}
		if(Global_UART_Config->HWFlowCtl == UART_HwFlowCtl_RTS || Global_UART_Config->HWFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			//PB14 RTS
			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB,&PinCfg);
		}
	}




}





void USART1_IRQHandler(void)
{
//	Global_UART_Config->P_IRQ_CallBack();
	pFun[0]();
}

void USART2_IRQHandler(void)
{
//	Global_UART_Config->P_IRQ_CallBack();
	pFun[1]();
}

void USART3_IRQHandler(void)
{
//	Global_UART_Config->P_IRQ_CallBack();
	pFun[2]();
}


