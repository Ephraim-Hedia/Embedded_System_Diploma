/*
 * Card.h
 *
 *  Created on: Sep 21, 2022
 *      Author: Lenovo
 */
#ifndef CARD_H_
#define CARD_H_

#include <stdio.h>
#include <stdlib.h>

#define DPRINT(...)		{fflush(stdin);\
		fflush(stdout);\
		printf(__VA_ARGS__);\
		fflush(stdin);\
		fflush(stdout);}

// typedefs
typedef unsigned char  uint8_t ;
typedef unsigned long  uint32_t ;

typedef struct
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
	CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;


//Function prototypes

EN_cardError_t getCardHolderName(ST_cardData_t *cardData);

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);

EN_cardError_t getCardPAN(ST_cardData_t *cardData);

#endif



