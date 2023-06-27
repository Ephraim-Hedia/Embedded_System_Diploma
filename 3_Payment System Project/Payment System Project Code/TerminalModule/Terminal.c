/*
 * Terminal.c
 *
 *  Created on: Sep 21, 2022
 *      Author: Lenovo
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{

	DPRINT("Please Enter The Transaction Date in Formate (DD/MM/YYYY) :\n");
	gets(termData->transactionDate);

	if ((termData->transactionDate)==NULL || (strlen(termData->transactionDate)<10))
	{
		return WRONG_DATE ;
	}
	else
		return TERMINAL_OK;

}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
	uint8_t CardMonthstring[3]={cardData->cardExpirationDate[0],cardData->cardExpirationDate[1],'\0'};
	uint8_t CardYearstring[3]={cardData->cardExpirationDate[3],cardData->cardExpirationDate[4],'\0'};
	uint8_t TerminalMonthstring[3]={termData->transactionDate[3],termData->transactionDate[4],'\0'};
	uint8_t TerminalYearstring[3]={termData->transactionDate[8],termData->transactionDate[9],'\0'};;


	int CardMonth=atoi(CardMonthstring);
	int CardYear=atoi(CardYearstring);
	int TerminalMonth=atoi(TerminalMonthstring);
	int TerminalYear=atoi(TerminalYearstring);

	if(TerminalYear>CardYear)
	{
		return EXPIRED_CARD;
	}
	else if(TerminalYear==CardYear)
	{
		if(TerminalMonth>CardMonth)
		{
			return EXPIRED_CARD;
		}
		else
		{
			return TERMINAL_OK;
		}
	}
	else
	{
		return TERMINAL_OK;
	}


}

//EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
//{
//
//	if ((cardData->primaryAccountNumber) == *(bank data base ))
//	{
//		return INVALID_CARD;
//	}
//	else
//		return OK ;
//
//
//}
//
//
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
	DPRINT("Please Enter The Transaction Amount:\n");
	scanf("%f",&termData->transAmount);

	if ((termData->transAmount)<=0)
	{
		return INVALID_AMOUNT ;
	}
	else
		return TERMINAL_OK ;

}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
	if(termData->transAmount  > termData->maxTransAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	else
		return TERMINAL_OK ;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData,float maxAmount)
{
	termData->maxTransAmount=maxAmount;
	if(termData->maxTransAmount <= 0)
		return INVALID_MAX_AMOUNT;
	else
		return TERMINAL_OK;
}
