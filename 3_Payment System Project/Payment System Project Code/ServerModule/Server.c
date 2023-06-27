/*
 * Server.c
 *
 *  Created on: Sep 21, 2022
 *      Author: Lenovo
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Server.h"
#include "../TerminalModule/Terminal.h"
#include "../CardModule/Card.h"


//DataBase
ST_accountsDB_t  accountsDB[255] ={
		{1000.0,RUNNING,"1234567899876543123"},
		{1500.0,BLOCKED,"1234567896541236123"},
		{200.5,RUNNING, "5975365485215975123"},
		{200.5,BLOCKED, "4137589661144223123"},
		{200.5,RUNNING, "1111222233334444123"}


};
static int j =0;
int i ;

ST_transaction_t TransDataBase [255]={0};

EN_transStat_t recieveTransactionData(ST_transaction_t *transData)
{

	ST_accountsDB_t AccountSelected;

	if(isValidAccount(&transData->cardHolderData, &AccountSelected)==ACCOUNT_NOT_FOUND)
	{
		transData->transState=FRAUD_CARD;
		if (saveTransaction(transData)==SAVING_FAILED)
			return INTERNAL_SERVER_ERROR;
		else
			return FRAUD_CARD;
	}

	if(isAmountAvailable(&(transData->terminalData),&AccountSelected)==LOW_BALANCE)
	{
		transData->transState=DECLINED_INSUFFECIENT_FUND;
		if (saveTransaction(transData)==SAVING_FAILED)
			return INTERNAL_SERVER_ERROR;
		else
			return DECLINED_INSUFFECIENT_FUND;
	}

	if(isBlockedAccount(&AccountSelected)==BLOCKED_ACCOUNT)
	{
		transData->transState=DECLINED_STOLEN_CARD;
		if (saveTransaction(transData)==SAVING_FAILED)
			return INTERNAL_SERVER_ERROR;
		else
			return DECLINED_STOLEN_CARD;
	}

	transData->transState=APPROVED;
	if(saveTransaction(transData) !=SERVER_OK)
		return INTERNAL_SERVER_ERROR;

	AccountSelected.balance=AccountSelected.balance- transData->terminalData.transAmount;
	accountsDB[i]=AccountSelected;
	DPRINT("\nThe Data Base Amount Balance : %f \n",accountsDB[i].balance);
	return APPROVED;

}

EN_serverError_t isValidAccount(ST_cardData_t *cardData,ST_accountsDB_t *accountRefrence)
{
	for (i=0;i<5;i++)
	{
		if(stricmp(cardData->primaryAccountNumber,accountsDB[i].primaryAccountNumber)==0)
		{
			accountRefrence->balance=accountsDB[i].balance;
			strcpy(accountRefrence->primaryAccountNumber,accountsDB[i].primaryAccountNumber);
			accountRefrence->state=accountsDB[i].state;
			return SERVER_OK;
		}
	}
	accountRefrence =NULL;
	return ACCOUNT_NOT_FOUND;
}


EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
	if(accountRefrence->state == BLOCKED)
		return BLOCKED_ACCOUNT;
	else
		return SERVER_OK;
}


EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{

	if(termData->transAmount > accountRefrence->balance)
		return LOW_BALANCE;
	else
		return SERVER_OK;
}


EN_serverError_t saveTransaction(ST_transaction_t *transData)
{

	if(j==256)
		return SAVING_FAILED;

	//Save Card Data
	strcpy(TransDataBase[j].cardHolderData.cardExpirationDate ,transData->cardHolderData.cardExpirationDate);
	strcpy(TransDataBase[j].cardHolderData.cardHolderName,transData->cardHolderData.cardHolderName);
	strcpy(TransDataBase[j].cardHolderData.primaryAccountNumber,transData->cardHolderData.primaryAccountNumber);

	//Save Terminal Data
	strcpy(TransDataBase[j].terminalData.transactionDate ,transData->terminalData.transactionDate);
	TransDataBase[j].terminalData.maxTransAmount=transData->terminalData.maxTransAmount;
	TransDataBase[j].terminalData.transAmount=transData->terminalData.transAmount;

	//Save State
	TransDataBase[j].transState=transData->transState;

	TransDataBase[j].transactionSequenceNumber=j;

	j++;

	return SERVER_OK;
}



void listSavedTransactions(void)
{
	int z ;
	for(z=0;z<j;z++)
	{
		DPRINT("\nTransaction Number :%s\n",TransDataBase[z].cardHolderData.cardHolderName);
		DPRINT("cardExpirationDate :%s\n",TransDataBase[z].cardHolderData.cardExpirationDate);
		DPRINT("PAN :%s\n",TransDataBase[z].cardHolderData.primaryAccountNumber);

		if(TransDataBase[z].transState==0)
		{
			DPRINT("TransState : :Accepted\n");
		}
		else
		{
			DPRINT("TransState : Rejected\n");
		}


	}
}
