# Payment Application 
## Getting help
Feel Free to contact me, just message me at <br/>
Linkedin at https://www.linkedin.com/in/guirguis-hedia-501446207/ <br/>
Facebook at https://www.facebook.com/afraem.hedia <br/>
with your question. <br/>

## Application Flowchart
![payment system](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/9043147f-dbe1-4772-92c5-500436114f8f)

## Folder Structure 
![image](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/75c9387b-3578-41da-b991-b06ea9419f5d)

## Card Module
This Module Care About The Way That the user Enter His Data "The Syntax Only"<br/>
1. The Card Name Length Must be 20 ~ 24 Char
2. The Expire Date in the format MM/YY
3. The PAN Should be in Range 16 ~ 19 Char
<br/>


if Any Error Occur We must return an Error to the user 
so we will use this enum 
```
typedef enum EN_cardError_t
{
	CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;
```
if No error occur we will return CARD_OK <br/>
and if the user Enter The Name of Card **More than 24 Char or Less Than 20** , We will return **WRONG_NAME** <br/>
and if the user Enter The Expire Data of Card not **in format MM/YY** , We will return **WRONG_EXP_DATE** <br/>
and if the user Enter The PAN of Card **More than 19 or less than 16** , We will return **WRONG_PAN** <br/>

### Three Function in Card Module to Check the Syntax :
1. getCardHolderName 
```
DPRINT("\nPlease Enter your Card Name:\n");
DPRINT("The Name Should be in Range 20 ~ 24 Char:\n");
gets(cardData->cardHolderName);
if((cardData->cardHolderName)==NULL ||(strlen(cardData->cardHolderName)>24) || (strlen(cardData->cardHolderName)<20) )
{
  return WRONG_NAME;
}
else
  return CARD_OK ;
```

2. getCardExpiryDate

```
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
```
  
3. getCardPAN

```
DPRINT("please Enter The Primary Account Number:\n");
DPRINT("The PAN Should be in Range 16 ~ 19 Char\n");
gets(cardData->primaryAccountNumber);
if((cardData->cardExpirationDate)== NULL || (strlen(cardData->primaryAccountNumber)<16) || (strlen(cardData->primaryAccountNumber)>19))
{
  return WRONG_PAN;
}
else
{
  return CARD_OK ;
}

```

## Terminal Module

The Aim of this Module :
- We Have The Expired Data From the information we take from the customer , And we know the date , So we can calculate if the card is Expired or No
  so we will Print To the User **EXPIRED_CARD** Error if Expired
- Check if the User Enter Invalid Amount ex : -500 LE
  so we will Print To the User **INVALID_AMOUNT** Error
- Check if the User Enter More than the Max of ATM ex : The Max of the ATM 8000 LE and the Customer Enter 12000LE 
so we will Print To the User **EXCEED_MAX_AMOUNT** Error

if Any Error Occur We must return an Error to the user 
so we will use this enum 
```
typedef enum EN_terminalError_t
{
TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;
```

### This Module Consist from 4 Main Important Function :
1. getTransactionDate
<br/> 
Ask the User to Enter the Date of the day

```
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
	DPRINT("Please Enter The Transaction Amount:\n");
	scanf("%f",&termData->transAmount);

	if ((termData->transAmount)<=0)
	{
		return INVALID_AMOUNT ;
	}
	else
		return TERMINAL_OK ;}
```
<br/>

2. isCardExpired

```
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
	uint8_t CardMonthstring[3]={cardData->cardExpirationDate[0],cardData->cardExpirationDate[1],'\0'};
	uint8_t CardYearstring[3]={cardData->cardExpirationDate[3],cardData->cardExpirationDate[4],'\0'};
	uint8_t TerminalMonthstring[3]={termData->transactionDate[3],termData->transactionDate[4],'\0'};
	uint8_t TerminalYearstring[3]={termData->transactionDate[8],termData->transactionDate[9],'\0'};



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
```
3. getTransactionAmount
<br/> 
This Function To Check if the User Enter invalid Amount of not

```
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
	DPRINT("Please Enter The Transaction Amount:\n");
	scanf("%f",&termData->transAmount);

	if ((termData->transAmount)<=0)
	{
		return INVALID_AMOUNT ;
	}
	else
	{	return TERMINAL_OK ;}
```

4. isBelowMaxAmount


We Use This Function to Check if the User Enter Amount More than the Max Amount or Not

```
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
	if(termData->transAmount  > termData->maxTransAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	else
		return TERMINAL_OK ;
}
```

## Server Module
The Server Module Has The database of the BANK 

```
ST_accountsDB_t  accountsDB[255] ={
		{1000.0,RUNNING,"1234567899876543123"},
		{1500.0,BLOCKED,"1234567896541236123"},
		{200.5,RUNNING, "5975365485215975123"},
		{200.5,BLOCKED, "4137589661144223123"},
		{200.5,RUNNING, "1111222233334444123"}


};
```

### The Server Module Has 4 Main Functions  :
1. isValidAccount
   
```

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

```
   
2. isAmountAvailable

```
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{

	if(termData->transAmount > accountRefrence->balance)
		return LOW_BALANCE;
	else
		return SERVER_OK;
}
```

   
3. isBlockedAccount

```
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
	if(accountRefrence->state == BLOCKED)
		return BLOCKED_ACCOUNT;
	else
		return SERVER_OK;
}
```


4. saveTransaction
   
```
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
```

# Checking The System 
## 1.Your Transaction Is Approved
![OUTPUT1](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/eb08f739-668c-479c-9e84-4454dc0c388b)

## 2.DECLINED_INSUFFECIENT_FUND
![OUTPUT2](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/55efdb26-c6c2-46a5-9bf3-3f3a2a7e6c18)

## 3.FRAUD_CARD
![OUTPUT3](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/801df823-a955-4327-975f-eb0c59d0f3b6)

## 4.DECLINED_STOLEN_CARD
![OUTPUT4](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/b4d20822-b63f-4306-a218-1118b18d76f9)

## 5.Card is Expired
![OUTPUT5](https://github.com/Ephraim-Hedia/Embedded_System_Diploma/assets/74508494/61247285-d259-4dc1-9c6f-07d7b2a73923)







