/********************************************************************************/
/* Author 			: Guirguis Hedia 											*/
/* Date 			: 5 MARCH 2023												*/
/* Version 			: V01														*/
/********************************************************************************/


#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H


 
typedef struct
{
	u32 CTRL;
	u32	LOAD;
	u32 VAL;
	u32 CALIB;
}STK_REG;

volatile STK_REG* STK =(volatile STK_REG*)(0xE000E010);


/*Options :		STK_CLK_SOURCE*/
#define STK_AHB				1
#define STK_AHB_OVER_8		0




#endif
