/*
 * App.c
 *
 *  Created on: Sep 21, 2022
 *      Author: Lenovo
 */

#include "App.h"





void CardModule (void)
{
	if(getCardHolderName(&CardData)==WRONG_NAME)
	{
		DPRINT("\n===========Error===========  ");
		DPRINT("\n===YOU Enter Wrong Name ===  ");
		DPRINT("\nTry Again =================  ");
	}

	else
	{
		if (getCardExpiryDate(&CardData)==WRONG_EXP_DATE)
		{
			DPRINT("\n===========Error===========  ");
			DPRINT("\n===YOU Enter Wrong Data ===  ");
			DPRINT("\nTry Again =================  ");
		}
		else
		{
			if(getCardPAN(&CardData)==WRONG_PAN)
			{
				DPRINT("\n===========Error===========  ");
				DPRINT("\n===YOU Enter Wrong PAN ===  ");
				DPRINT("\nTry Again =================  ");
			}
			else
			{
				TerminalModule();
			}
		}
	}





}




void TerminalModule (void)
{
	if(getTransactionDate(&TerminalData)==WRONG_DATE)
	{
		DPRINT("\n===========Error===========  ");
		DPRINT("\n===YOU Enter Wrong Date ===  ");
		DPRINT("\nTry Again =================  ");
	}
	else{
		if(isCardExpired(&CardData,&TerminalData)==EXPIRED_CARD)
		{
			DPRINT("\n===========Error===========  ");
			DPRINT("\n===Card is Expired ===  ");
			DPRINT("\nTry Again =================  ");
		}
		else
		{
			if(getTransactionAmount(&TerminalData)==INVALID_AMOUNT)
			{
				DPRINT("\n===========Error===========  ");
				DPRINT("\n===The Amount is Invalid===  ");
				DPRINT("\nTry Again =================  ");
			}
			else
			{

				if(setMaxAmount(&TerminalData,8000)==INVALID_MAX_AMOUNT)
				{
					DPRINT("\n===========Error===========  ");
					DPRINT("\n===INVALID_MAX_AMOUNT======  ");
					DPRINT("\nTry Again =================  ");
				}
				else
				{
					if(isBelowMaxAmount(&TerminalData)==EXCEED_MAX_AMOUNT)
					{
						DPRINT("\n===========Error===========  ");
						DPRINT("\n===EXCEED_MAX_AMOUNT=======  ");
						DPRINT("\nTry Again =================  ");
					}
					else
					{
						ServerModule();
					}
				}
			}
		}
	}
}


void ServerModule (void)
{
	ServerData.cardHolderData=CardData;
	ServerData.terminalData=TerminalData;

	int pressed =0;

	switch (recieveTransactionData(&ServerData))
	{
	case APPROVED:
		DPRINT("\n===========ThankYou===========  ");
		DPRINT("\n===Your Transaction Is Approved=======  ");
		DPRINT("\n =======================================  ");
		break;
	case DECLINED_INSUFFECIENT_FUND:
		DPRINT("\n===========Error===========  ");
		DPRINT("\n===DECLINED_INSUFFECIENT_FUND=======  ");
		DPRINT("\nTry Again =================  ");
		break;
	case DECLINED_STOLEN_CARD:
		DPRINT("\n===========Error===========  ");
		DPRINT("\n===DECLINED_STOLEN_CARD=======  ");
		DPRINT("\nTry Again =================  ");
		break;
	case FRAUD_CARD:
		DPRINT("\n===========Error===========  ");
		DPRINT("\n======= FRAUD_CARD ========  ");
		DPRINT("\n======= Try Again =========  ");
		break;
	case INTERNAL_SERVER_ERROR:
		DPRINT("\n===========Error===========  ");
		DPRINT("\n===INTERNAL_SERVER_ERROR=======  ");
		DPRINT("\nTry Again =================  ");
		break;


	}
	DPRINT("\nIf You Want To Print listSavedTransactions Press 1 else 2 :\n");
	scanf("%d",&pressed);


	DPRINT("Your Option is %d",pressed);
	switch(pressed)
	{
	case 1:
		listSavedTransactions();
		break;
	case 2:
		break;
	default :
		DPRINT("You Entered Wrong Option \n");
	}


	//	EN_serverError_t saveTransaction(ST_transaction_t *transData);
	//
	//	void listSavedTransactions(void);
}

void AppStart(void)
{
	CardModule();

}
