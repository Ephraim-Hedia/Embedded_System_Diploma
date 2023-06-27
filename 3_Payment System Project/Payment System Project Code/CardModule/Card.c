/*
 * Card.c
 *
 *  Created on: Sep 21, 2022
 *      Author: Lenovo
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Card.h"


EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
	DPRINT("\nPlease Enter your Card Name:\n");
	DPRINT("The Name Should be in Range 20 ~ 24 Char:\n");
	gets(cardData->cardHolderName);
	if((cardData->cardHolderName)==NULL ||(strlen(cardData->cardHolderName)>24) || (strlen(cardData->cardHolderName)<20) )
	{
		return WRONG_NAME;
	}
	else
		return CARD_OK ;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
	DPRINT("please Enter The Expire Date in the format MM/YY:\n");
	gets(cardData->cardExpirationDate);
	if((cardData->cardExpirationDate)==NULL || (strlen(cardData->cardExpirationDate)<5) || (strlen(cardData->cardExpirationDate)>5))
	{
		return WRONG_EXP_DATE;
	}
	else
		return CARD_OK ;
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
	DPRINT("please Enter The Primary Account Number:\n");
	DPRINT("The Name Should be in Range 16 ~ 19 Char\n");
	gets(cardData->primaryAccountNumber);
	if((cardData->cardExpirationDate)== NULL || (strlen(cardData->primaryAccountNumber)<16) || (strlen(cardData->primaryAccountNumber)>19))
	{
		return WRONG_PAN;
	}
	else
	{
		return CARD_OK ;
	}

}


