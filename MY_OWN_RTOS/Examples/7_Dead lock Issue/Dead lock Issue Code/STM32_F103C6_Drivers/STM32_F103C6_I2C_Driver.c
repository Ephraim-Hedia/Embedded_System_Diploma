/*
 * STM32_F103C6_I2C_Driver.c
 *
 *  Created on: Dec 15, 2022
 *      Author: Guirguis
 */

#include "STM32_F103C6_I2C_Driver.h"

//
//
///*
// * =====================================================
// * 						Generic Variables
// * =====================================================
// */
//	I2C_InitTypeDef Global_I2C_Config[2] ={NULL,NULL};
//
//
///*
// * =====================================================
// * 						Generic Macros
// * =====================================================
// */
//
//#define I2C1_INDEX			0
//#define I2C2_INDEX			1
//
///*
// * =====================================================
// * 							APIs
// * =====================================================
// */
//
//void MCAL_I2C_Init(I2C_TypeDef * I2Cx,I2C_InitTypeDef* I2C_InitStruct)
//{
//	uint16_t tmpreg = 0,freqRange =0;
//	uint16_t result;
//	uint32_t pclk1=8000000;
//	//Enable RCC Clock
//	if(I2Cx==I2C1)
//	{
//		Global_I2C_Config[I2C1_INDEX]=*I2C_InitStruct;
//		RCC_I2C1_CLK_EN();
//
//	}else
//	{
//		Global_I2C_Config[I2C2_INDEX]=*I2C_InitStruct;
//		RCC_I2C2_CLK_EN();
//	}
//
//	if(I2C_InitStruct->I2C_Mode == I2C_mode_I2C)
//	{
//		/*-------------------INIT Time-  ----------------*/
//		//-I2C_CR2.FREQ[5:0]: Peripheral clock Frequency
//		/*Get the I2Cx CR2 value */
//		tmpreg =I2Cx->CR2;/*First Take the value of the reg to tempreg*/
//		/*Clear Frequency FREQ[5:0] bits*/
//		tmpreg &=~(I2C_CR2_FREQ);
//		/* Get pclk1 frequency value*/
//		pclk1 =MCAL_RCC_Get_PCLK1Freq();
//		//Set Frequency bits depending on pclk1 value
//		freqRange =(uint16_t)(pclk1/1000000);
//
//		tmpreg |= freqRange;
//
//		/* Write to I2Cx CR2*/
//		I2Cx->CR2=tmpreg;
//
//		//Configure the clock control registers(I2C_CCR)
//		/*Disable the selected I2C peripheral to configure Time*/
//
//		I2Cx->CR1 &=~(I2C_CR1_PE);
//
//		tmpreg = 0 ;
//
//
//		/*Configure Speed in standard Mode */
//		if(I2C_InitStruct->I2C_ClockSpeed == I2C_SCLK_SM_50K || I2C_InitStruct->I2C_ClockSpeed == I2C_SCLK_SM_100K)
//		{
//			/*Standard Mode speed calculate*/
//			//		Tclk/2=CRR * Tpclk1
//			//		CRR = Tclk/(2* Tpclk1)
//			//		CRR = Fpclk1/(2*I2C_ClockFrequency)
//			result =(uint16_t)(pclk1/(I2C_InitStruct->I2C_ClockSpeed <<1));
//			tmpreg |= result;
//
//
//			/*Write to I2Cx CCR*/
//			I2Cx->CCR =tmpreg;
//
//			/*---------I2C_TRISE_Configuration---------------*/
////			For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
////			If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
////			therefore the TRISE[5:0] bits must be programmed with 09h.
////			(1000 ns / 125 ns = 8 + 1)
////			The filter value can also be added to TRISE[5:0].
//			I2Cx->TRISE=freqRange +1;
//
//		}else
//		{
//			//Fast Mode Not Supported
//		}
//
//		/*---------I2Cx CR1 Configuration-------------*/
//		/*Get the I2Cx CR1 value*/
//		tmpreg = I2Cx->CR1;
//
//		tmpreg |= (uint16_t)(I2C_InitStruct->I2C_ACK_Control | I2C_InitStruct->General_Call_Address_Detection |I2C_InitStruct->I2C_Mode |I2C_InitStruct->StretchMode);
//
//		/*Write to I2Cx CR1*/
//		I2Cx->CR1 = tmpreg;
//
//		/*------I2Cx OAR1 & I2Cx OAR2 Configuration------*/
//		tmpreg=0;
//		if(I2C_InitStruct->I2C_Slave_Address.Enable_Dual_ADD == 1)
//		{
//			tmpreg = I2C_OAR2_ENDUAL;/*I2C_OAR2 Bit 0 ENDUAL: Dual addressing mode enable*/
//			tmpreg |= I2C_InitStruct->I2C_Slave_Address.Secondary_slave_address << I2C_OAR2_ADD2_Pos;/*I2C_OAR2 Bits 7:1 ADD2[7:1]: Interface addres*/
//			I2Cx->OAR2=tmpreg;
//
//		}
//		tmpreg=0;
//		tmpreg |= I2C_InitStruct->I2C_Slave_Address.Primary_slave_address << 1;/*I2C_OAR1 Bits 7:1 ADD[7:1]: Interface address*/
//		tmpreg |= I2C_InitStruct->I2C_Slave_Address.I2C_Addressing_Slave_mode; /*I2C_OAR1 Bit 15 ADDMODE Addressing mode (slave mode)*/
//		I2Cx->OAR1 =tmpreg;
//	}else
//	{
//		//SMBUS Not Supported
//	}
//
//	//Interrupt Mode (Slave Mode) //Check callback pointer if != NULL
//	if(I2C_InitStruct->P_Slave_Event_CallBack != NULL)//That Enable SLAVE interrupt state Mode
//	{
//		//Enable IRQ
//		I2Cx->CR2 |= (I2C_CR2_ITERREN);
//		I2Cx->CR2 |= (I2C_CR2_ITEVTEN);
//		I2Cx->CR2 |= (I2C_CR2_ITBUFEN);
//		if(I2Cx == I2C1)
//		{
//			NVIC_IRQ31_I2C1_EV_Enable;
//			NVIC_IRQ32_I2C1_ER_Enable;
//		}else if (I2Cx == I2C2)
//		{
//			NVIC_IRQ33_I2C2_EV_Enable;
//			NVIC_IRQ34_I2C2_ER_Enable;
//		}
//		I2Cx->SR1=0;
//		I2Cx->SR2=0;
//	}
//
//
//	/*Enable the selected I2C peripheral */
//	I2Cx->CR1 |= (I2C_CR1_PE);
//
//
//}
//void MCAL_I2C_DeInit(I2C_TypeDef* I2Cx)
//{
//	if(I2Cx == I2C1)
//	{
//		NVIC_IRQ31_I2C1_EV_Disable;
//		NVIC_IRQ32_I2C1_ER_Disable;
//		RCC_I2C1_Reset();
//	}else if (I2Cx == I2C2)
//	{
//		NVIC_IRQ33_I2C2_EV_Disable;
//		NVIC_IRQ34_I2C2_ER_Disable;
//		RCC_I2C2_Reset();
//	}
//}
//void MCAL_I2C_GPIO_set_Pins(I2C_TypeDef* I2Cx)
//{
//	GPIO_PinConfig_t PinCfg;
//	if(I2Cx == I2C1)
//	{
//		//PB6:I2C1_SCL
//		//PB7:I2C1_SDA
//		PinCfg.GPIO_PinNumber=GPIO_PIN_6;
//		PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_AF_OD;
//		PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
//		MCAL_GPIO_Init(GPIOB, &PinCfg);
//
//
//		PinCfg.GPIO_PinNumber=GPIO_PIN_7;
//		PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_AF_OD;
//		PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
//		MCAL_GPIO_Init(GPIOB, &PinCfg);
//
//	}else if(I2Cx == I2C2)
//	{
//		//PB10:I2C2_SCL
//		//PB11:I2C2_SDA
//
//		PinCfg.GPIO_PinNumber=GPIO_PIN_10;
//		PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_AF_OD;
//		PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
//		MCAL_GPIO_Init(GPIOB, &PinCfg);
//
//
//		PinCfg.GPIO_PinNumber=GPIO_PIN_11;
//		PinCfg.GPIO_Mode=GPIO_MODE_OUTPUT_AF_OD;
//		PinCfg.GPIO_Output_Speed=GPIO_SPEED_10M;
//		MCAL_GPIO_Init(GPIOB, &PinCfg);
//	}
//
//
//
//}
//
//void MCAL_I2C_Master_TX(I2C_TypeDef* I2Cx,uint16_t devAddr , uint8_t* dataOut , uint32_t dataLen , Stop_Condition Stop , Repeated_Start start)
//{
//	uint16_t i =0;
//	//todo
//	//Support timeout (configure timer working for specific duration rise interrupt)
//	//timer_interrupt (){flag=1}
//	//so any code exist in while (){check flag || any polling conditions}
//
//	//	1.Set the Start Bit in the I2C_CR1 register to generate a start condition
//	I2C_GenerateSTART(I2Cx,ENABLE,start);
//
//
//	//2. wait for EV5
////	EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
//	while (!I2C_GetFlagStatus(I2Cx ,EV5 ));
//
//	//3-Send Address
//	I2C_SendAddress(I2Cx, devAddr, I2C_Direction_Transmitter);
//
//	//3.1 wait for EV6
////	EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
//	while (!I2C_GetFlagStatus(I2Cx ,EV6 ));
//
//	//4./*TRA , BUSY , MSL , TXE flags*/
//	while (!I2C_GetFlagStatus(I2Cx ,MASTER_BYTE_TRANSMITTING ));
//
//	for (i = 0 ; i <dataLen ; i++)
//	{
//		/*Write in the DR register the data to be sent */
//		I2Cx->DR = dataOut[i];
//		//5.Wait for EV8
////		EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
//		while (!I2C_GetFlagStatus(I2Cx ,EV8 ));
//	}
//
//	//6.wait EV8_2
////	EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
//	while (!I2C_GetFlagStatus(I2Cx ,EV8_2 ));
//
//
//	if(stop ==With_Stop)
//	{
//		// 7. Send Stop Condition
//		I2C_GenerateSTOP(I2Cx,ENABLE);
//	}
//
//}
//
//void MCAL_I2C_Master_RX(I2C_TypeDef* I2Cx,uint16_t devAddr , uint8_t* dataOut , uint32_t dataLen , Stop_Condition Stop , Repeated_Start start)
//{
//	int i = 0 ;
//	//	1.Set the Start Bit in the I2C_CR1 register to generate a start condition
//	I2C_GenerateSTART(I2Cx,ENABLE,start);
//
//
//	//2. wait for EV5
//	//	EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
//	while (!I2C_GetFlagStatus(I2Cx ,EV5 ));
//
//
//	//3-Send Address
//	I2C_SendAddress(I2C_TypeDef, devAddr, I2C_Direction_Recieve);
//
//	//3.1 wait for EV6
//	//	EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
//	while (!I2C_GetFlagStatus(I2Cx ,EV6 ));
//
//	I2C_AcknowledgeConfig(I2Cx,ENABLE);
//
//	if(dataLen)
//	{
//		for (i = dataLen ; i > 1;i--)
//		{
//			//wait until RXNE becomes 1
//			while (!I2C_GetFlagStatus(I2Cx ,EV7 ));
//			//read the data from data register in to buffer
//			*dataOut = I2Cx->DR;
//			//Increment the buffer address
//			dataOut++;
//		}
//		I2C_AcknowledgeConfig(I2Cx,DISABLE);
//	}
//
//
//	if (Stop == With_Stop)
//	{
//		// 7. Send Stop condition
//		I2C_GenerateSTOP(I2Cx, ENABLE);
//	}
//
//	//re-enable ACKing
//	if(Global_I2C_Config[index].I2C_ACK_Control == I2C_Ack_Enable)
//	{
//		I2C_AcknowledgeConfig(I2Cx,ENABLE);
//	}
//}
//
//
//
//
//
//
//
//
//
//
//
//void I2C_GenerateSTART(I2C_TypeDef* I2Cx,FuntionalState NewState ,Repeated_Start start)
//{
//	if(start != repeated_start)
//	{
//		//Check if the BUS is Idle
//		while(I2C_GetFlagStatus(I2Cx,I2C_FLAG_BUSY));
//	}
////	Bit 8 START: Start generation
////	This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
////	In Master Mode:
////	0: No Start generation
////	1: Repeated start generation
////	In Slave mode:
////	0: No Start generation
////	1: Start generation when the bus is free
//	if(NewState != DISABLE)
//	{
//		/*Generate a Start condition */
//		I2Cx->CR1 |= I2C_CR1_START;
//	}
//	else
//	{
//		/*Disable the START condition generation*/
//		I2Cx->CR1 &=~( I2C_CR1_START);
//	}
//}
//
//
//
//
//
//
//
//
//
//FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx ,Status flag)
//{
//	volatile uint32_t dummyRead;
//	FlagStatus bitstatus = RESET;
//	uint32_t flag1=0 , flag2=0;
//	uint32_t lastevent = 0;
//	switch (flag)
//	{
//
//	case I2C_FLAG_BUSY:
//	{
////		Bit 1 BUSY: Bus busy
////		0: No communication on the bus
////		1: Communication ongoing on the bus
////		– Set by hardware on detection of SDA or SCL low
////		– cleared by hardware on detection of a Stop condition.
////		It indicates a communication in progress on the bus. This information is still updated when
////		the interface is disabled (PE=0)
//		if((I2Cx->SR2) & (I2C_SR2_BUSY))
//			bitstatus=SET;
//		else
//			bitstatus=RESET;
//		break;
//	}
//
//	case EV5:
//	{
////		Bit 0 SB: Start bit (Master mode)
////		0: No Start condition
////		1: Start condition generated.
////		– Set when a Start condition generated.
////		– Cleared by software by reading the SR1 register followed by writing the DR register, or by
////		hardware when PE=0
//		if((I2Cx->SR2) & (I2C_SR1_SB))
//			bitstatus=SET;
//		else
//			bitstatus=RESET;
//
//		break;
//
//
//
//	}
//
//	case EV6:
//	{
//		//			Address sent (Master)
//		//			0: No end of address transmission
//		//			1: End of address transmission
//		//			– For 10-bit addressing, the bit is set after the ACK of the 2nd byte.
//		//			– For 7-bit addressing, the bit is set after the ACK of the byte.
//		//			Note: ADDR is not set after a NACK receptio
//		//	EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
//
//
//		if((I2Cx->SR1) & (I2C_SR1_ADDR))
//			bitstatus=SET;
//		else
//			bitstatus=RESET;
//		break;
//		//			cleared by reading SR1 register followed by reading SR2.
//		dummyRead=I2Cx->SR2;
//	}
//
//	case MASTER_BYTE_TRANSMITTING:
//	{
//		/*Read the I2Cx status register*/
//		flag1 =I2Cx->SR1;
//		flag2 =I2Cx->SR2;
//		flag2 = flag2<<16;
//
//		/*Get the last value from I2C status register */
//		lastevent= (flag1 | flag2) & ((uint32_t)0x00FFFFFF);
//
//		/*Check whether the last event contains the I2x_EVENT*/
//		if((lastevent & MASTER_BYTE_TRANSMITTING) ==MASTER_BYTE_TRANSMITTING)
//		{
//			/*SUCCESS: last event is equal to I2C_EVENT*/
//			bitstatus=SET;
//		}
//		else
//		{
//			/*ERROR: last event is different from I2C_EVENT*/
//			bitstatus=RESET;
//		}
//		break;
//	}
//
//	case EV8_1:
//	case EV8:
//	{
//		//				EV8: TxE=1, shift register not empty, d. ata register empty, cleared by writing DR register
//		//				Bit 7 TxE: Data register empty (transmitters)
//		//				0: Data register not empty
//		//				1: Data register empty
//		//				– Set when DR is empty in transmission. TxE is not set during address phase.
//		//				– Cleared by software writing to the DR register or by hardware after a start or a stop condition
//		//				or when PE=0.
//		//				TxE is not set if either a NACK is received, or if next byte to be transmitted is PEC (PEC=1)
//		//				Note: TxE is not cleared by writing the first data being transmitted, or by writing data when
//		//				BTF is set, as in both cases the data register is still empty
//		if((I2Cx->SR1) & (I2C_SR1_TXE))
//			bitstatus=SET;
//		else
//			bitstatus=RESET;
//		break;
//
//	}
//	case EV8_2:
//	{
//
//		if(((I2Cx->SR1) & (I2C_SR1_TXE)) && ((I2Cx->SR1) & (I2C_SR1_BTF)))
//		{
//			bitstatus =SET;
//		}
//		else
//		{
//			bitstatus=RESET;
//		}
//		break;
//	}
//
//	case EV7:
//	{
////		Bit 6 RxNE: Data register not empty (receivers)
////		0: Data register empty
////		1: Data register not empty
////		– Set when data register is not empty in receiver mode. RxNE is not set during address phase.
////		– Cleared by software reading or writing the DR register or by hardware when PE=0.
////		RxNE is not set in case of ARLO event
//		if((I2Cx->SR1) & (I2C_SR1_RXNE))
//			bitstatus=SET;
//		else
//			bitstatus=RESET;
//		break;
//	}
//
//	return bitstatus;
//	}
//}
//
//
//void I2C_SendAddress(I2C_TypeDef* I2Cx ,uint16_t Address , I2C_Direction Direction)
//{
//	//Supported Only 7 bit Mode
//
//
//
//
//	uint8_t index = I2Cx == I2C1 ? I2C1_INDEX:I2C2_INDEX;
//	if(Global_I2C_Config[index].I2C_Slave_Address.I2C_Addressing_Slave_mode==I2C_Addressing_Slave_mode_7Bit)
//	{
//		Address = (Address<<1);
//		if (Direction == I2C_Direction_Transmitter)
//		{
//			/* Set the address Bit0 for read */
//			Address |= 1<<0;
//		}
//		else
//		{
//			/* Reset the address Bit0 for Write */
//			Address &=~(1<<0);
//		}
//	}
//	else
//	{
//		//Not Supported
//	}
//
//	/* Send the address */
//	I2Cx->DR=Address;
//
//}
//
//
//
//
//void I2C_GenerateSTOP (I2C_TypeDef* I2Cx ,FuntionalState NewState)
//{
//	if (NewState != DISABLE)
//	{
//		/*Generate a STOP Condition*/
//		I2Cx->CR1 |= I2C_CR1_STOP;
//	}
//	else
//	{
//		/*Disable the STOP condition generation */
//		I2Cx->CR1 &=~(I2C_CR1_STOP);
//	}
//}
//
//
//void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx , FuntionalState state )
//{
//	if (state != ENABLE)
//	{
//		/*ENABLE ACK*/
//		I2Cx->CR1 |= I2C_CR1_ACK;
//	}
//	else
//	{
//		/*Disable ACK*/
//		I2Cx->CR1 &=~(I2C_CR1_ACK);
//	}
//}
//
//
//void MCAL_I2C_SlaveSendData(I2C_TypeDef* I2Cx , uint8_t data)
//{
//	I2Cx->DR=data;
//}
//uint8_t MCAL_I2C_SlaveReceiveData(I2C_TypeDef* I2C_TypeDef)
//{
//	return (uint8_t)I2Cx->DR;
//}
//
//
//
//
//void I2C1_ER_IRQHandler(void)
//{
//
//}
//
//
//void I2C1_EV_IRQHandler(void)
//{
//	volatile uint32_t dummy_read = 0 ;
//	I2C_TypeDef* I2Cx = I2C1;
//	//Interrupt handling for both master and slave mode of a device
//
//	uint32_t temp1 , temp2 , temp3 ;
//	temp1 = I2Cx->CR2& ( I2C_CR2_ITEVTEN);
//	temp2 = I2Cx->CR2& ( I2C_CR2_ITBUFEN);
//	temp3 = I2Cx->SR1& ( I2C_SR1_STOPF);
//
//	//Handle for Interrupt generated by STOPF event
//		//Note : Stop detection flag is applicable only slave mode
//	if(temp1 && temp3)
//	{
//		//STOP flag is set
//		//Clear the STOPF ( i.e 1 read SR1 2 write to CR1 )
//		I2Cx->CR1 |= 0x0000;
//		I2C_Slave_States(I2Cx,I2C_EV_STOP);
//	}
//
//	//------------------------------------------------------------
//	temp3 = I2Cx->SR1 & (I2C_SR1_ADDR);
//	//Handle for interrupt generated by ADDR event
//	//Note : when master mode : Address is sent
//	//		When Slave mode : Address matched with own address
//
//	if(temp1 && temp3)
//	{
//		//interrupt is generated because of ADDR event
//		//check for device mode
//		if(I2Cx->SR2 &(I2C_SR2_MSL))
//		{
//			//master
//		}
//		else
//		{
//			//slave mode
//			//clear the ADDR flag (read SR1 , read SR2)
//			dummy_read = I2Cx->SR1;
//			dummy_read = I2Cx->SR2;
//			I2C_Slave_States(I2Cx,I2C_EV_ADDR_Matched);
//		}
//	}
//	temp3 =I2Cx->SR1 & (I2C_SR1_TXE);
//	//Handle for interrupt generated by TXE event
//	if (temp1 && temp2 && temp3)
//	{
//		//Check for device mode
//		if(I2Cx->SR2 &(I2C_SR1_MSL))
//		{
//
//		}else
//		{
//			//slave
//			Slave_State(I2Cx,I2C_EV_DATA_REQ);
//		}
//	}
//
//
//
//
//
//
//}
//
//
//void I2C2_ER_IRQHandler(void)
//{
//
//}
//
//
//void I2C2_EV_IRQHandler(void)
//{
//
//}
//
//
//
//
//void I2C_Slave_States (I2C_TypeDef*I2Cx , Slave_State state)
//{
//	uint8_t index = I2Cx ==I2C1 ? I2C1_INDEX : I2C2_INDEX;
//	switch (state)
//	{
//	case I2C_ERROR_AF:
//	{
//		//make sure that the slave is really in transmitter mode
//		if(I2Cx->SR2 & (I2C_SR2_TRA))
//		{
//			//Slave shouldn't Send anything else
//		}
//		break;
//	}
//	case I2C_EV_STOP:
//	{
//		//make sure that the slave is really in transmitter mode
//		if(I2Cx->SR2 & (I2C_SR2_TRA))
//		{
//			//Notify APP that the Stop condition is sent by the master
//			Global_I2C_Config[index].P_Slave_Event_CallBack(I2C_EV_STOP);
//		}
//		break;
//	}
//	case I2C_EV_ADDR_Matched :
//	{
//		//Notify APP that the Stop condition is sent by the master
//		Global_I2C_Config[index].P_Slave_Event_CallBack(I2C_EV_ADDR_Matched);
//		break;
//	}
//	case I2C_EV_DATA_REQ:
//	{
//		//make sure that the salve is really in transmitter mode
//		if(I2Cx->SR2 & (I2C_SR2_TRA))
//		{
//			//The APP Layer should send the data (MCAL_I2C_SlaveSendData) in this state
//			Global_I2C_Config[index ].P_Slave_Event_CallBack(I2C_EV_DATA_REQ);
//		}
//		break;
//	}
//	case I2C_EV_DATA_RCV :
//	{
//		//make sure that the slave is really in receiver mode
//		if(!(I2Cx->SR2 & (I2C_SR2_TRA)))
//		{
//			//the APP Layer should read the data (MCAL_I2C_SlaveReceiveData) in this state
//			Global_I2C_Config[index].P_Slave_Event_CallBack(I2C_EV_DATA_RCV);
//		}
//
//		break;
//	}
//
//
//	}
//}





