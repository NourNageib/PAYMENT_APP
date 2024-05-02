/************************************/
/*	Author	  :	Nour Abd EL-Aziz 	*/
/*	SWC		  : SERVER Module  		*/
/*  Layer	  : SERVER				*/
/*	Version	  :	1.0		  			*/
/*	Date	  :	December  9, 2022	*/
/*	Last Edit :	N/A					*/
/************************************/
#include"server.h"
#include "card.h"
#include "terminal.h"
#include "STD_types.h"
#include <string.h>


extern ST_terminalData_t terminal;
extern ST_cardData_t card;

ST_accountsDB_t Accounts_Data_Base[255] = { {2000.0, RUNNING, "8989374615436851"} ,{100000.0, BLOCKED, "5807007076043875"} ,{5585.55 ,BLOCKED,25484256345284263},{8542.5 , RUNNING,85674521587964425},{8575.1 ,RUNNING
,1595546245876548},{444465.5,BLOCKED,88559966774455588},{88888.8,BLOCKED,12589574666526698} };

ST_transaction_t Transuction_DB[255] = { 0 };
u8 Transauction_ID = 0;


ST_accountsDB_t REFRENCE;
ST_transaction_t trans_data;



EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	printf("holdername");
	gets(transData->cardHolderData);
	gets(transData->terminalData);

	if (isValidAccount(&transData->cardHolderData, &REFRENCE) == ACCOUNT_NOT_FOUND)
	{
		printf("Actual Result: FRAUD_CARD");
		return FRAUD_CARD;

	}
	if (isAmountAvailable(&transData->terminalData, &REFRENCE) == LOW_BALANCE)
	{
		printf("Actual Result: DECLIEND_INSUFFECIENT_AMOUNT");
		return DECLINED_INSUFFECIENT_FUND;

	}
	if (isBlockedAccount(&REFRENCE))
	{
		printf("Actual REsult: DECLLINED_STOLEN_CARD");
		return DECLINED_STOLEN_CARD;
	}
	if (saveTransaction == INTERNAL_SERVER_ERROR)
	{
		printf("Actual Result: INTERNAL_SERVER_ERROR");
		return INTERNAL_SERVER_ERROR;
	}
	printf("APPROVED");
	return APPROVED;

}
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	if (!cardData)
	{
		printf("Actual Result :ACCOUNT_NOT_FOUND");
		return ACCOUNT_NOT_FOUND;
	}
	for (u32 i = 0; i < 13;i++)
	{
		if (strncmp(cardData->primaryAccountNumber, Accounts_Data_Base[i].primaryAccountNumber,20) == 0)
		{
			accountRefrence->state = Accounts_Data_Base[i].state;
			accountRefrence->balance = Accounts_Data_Base[i].balance;
			strncpy_s(accountRefrence->primaryAccountNumber, 20, Accounts_Data_Base[i].primaryAccountNumber, _TRUNCATE);
			printf("Actual Result : SERVER_OK");
			return SERVER_OK;
		}
		else
		{
			accountRefrence == NULL;
			printf("Actual Result :ACCOUNT_NOT_FOUND");
			return ACCOUNT_NOT_FOUND;
		}
	}
}
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	if (accountRefrence->state == BLOCKED)
	{
		printf("Actual Result: BLOCKED_ACCOUNT");
		return BLOCKED_ACCOUNT;
	}
	else if (accountRefrence->state == RUNNING)
	{
		printf("Actual Result : SERVER_OK");
		return SERVER_OK;
	}
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	if (termData->transAmount <= accountRefrence->balance)
	{
		printf("Actul Result: SERVER_OK");
		return SERVER_OK;
	}
	else
	{
		printf("Actual Result: LOW_BALANCE");
		return LOW_BALANCE;
	}
}
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	transData->transactionSequenceNumber = Transauction_ID;
	strncpy_s(Transuction_DB[Transauction_ID].cardHolderData.cardHolderName, 25, transData->cardHolderData.cardHolderName, _TRUNCATE);
	strncpy_s(Transuction_DB[Transauction_ID].cardHolderData.cardExpirationDate, 5, transData->cardHolderData.cardExpirationDate, _TRUNCATE);
	strncpy_s(Transuction_DB[Transauction_ID].cardHolderData.primaryAccountNumber, 20, transData->cardHolderData.primaryAccountNumber, _TRUNCATE);
	strncpy_s(Transuction_DB[Transauction_ID].terminalData.transactionDate, 11, transData->terminalData.transactionDate, _TRUNCATE);
	Transuction_DB[Transauction_ID].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
	Transuction_DB[Transauction_ID].terminalData.transAmount = transData->terminalData.transAmount;
	Transuction_DB[Transauction_ID].transState = transData->transState;
	Transauction_ID++ ;
	return SERVER_OK;
}
void listSavedTransactions(void)
{
	printf("\nTester Name : Nour abdel-aziz \nFunction Name :listSavedTransactions");
	printf("\nTest Case 1 : 0 \nExpected Result : \nInput Data:");
}

void recieveTransactionDataTest(void)
{
	printf("\nTester Name : Nour abdel-aziz \nFunction Name :recieveTransactionData");
	printf("\nTest Case 1 : FRAUD \nExpected Result : FRAUD_ACCOUNT \nInput Data:");
	getCardPAN(&card);
	recieveTransactionData(&trans_data);
	printf("\nTest Case 2 : INSUFFECIENT_FUND \nExpected Result :DECLINED_INSUFFECIENT_FUND \nInput Data:");
	getTransactionAmount(&trans_data);
	recieveTransactionData(&trans_data);
	printf("\nTest Case 3 : STOLEN \nExpected Result :DECLINED_STOLEN_CARD \nInput Data:");
	getCardPAN(&card);
	recieveTransactionData(&trans_data);
	printf("\nTest Case 3 : INTERNAL_SERVER_ERROR \nExpected Result :INTERNAL_SERVER_ERROR \nInput Data:");
	getCardPAN(&card);
	recieveTransactionData(&trans_data);
	printf("\nTest Case 3 : APPROVED \nExpected Result :APPROVED \nInput Data:");
	getCardPAN(&card);
	recieveTransactionData(&trans_data);

}
void isValidAccountTest(void)
{
	printf("\nTester Name : Nour abdel-aziz \nFunction Name :isValidAccount");
	printf("\nTest Case 1 : 8989374615436851 \nExpected Result : VALID_ACCOUNT \nInput Data:");
	getCardPAN(&terminal);
	isValidAccount(&terminal, &REFRENCE);
	printf("\nTest Case 2 : 8989666666436851 \nExpected Result : ACCOUNT_NOT_FOUND \nInput Data:");
	getCardPAN(&terminal);
	isValidAccount(&terminal, &REFRENCE);
}
void isBlockedAccountTest(void)
{
	printf("\nTester Name : Nour abdel-aziz \nFunction Name :isBlockedAccount");
	printf("\nTest Case 1 :RUNNING \nExpected Result :RUNNING \nInput Data:");
	isBlockedAccount(&Accounts_Data_Base[0]);
	printf("\nTest Case 2 : BLOCKED \nExpected Result : BLOCKED \nInput Data:");
	isBlockedAccount(&Accounts_Data_Base[1]);
	printf("\nTest Case 3 : BLOCKED \nExpected Result : BLOCKED \nInput Data:");
	isBlockedAccount(&Accounts_Data_Base[2]);
}
void isAmountAvailableTest(void) //refrence account database, terminal data-> terminal
{
	REFRENCE.balance = 177777.1;
	printf("\nTester Name : Nour abdel-aziz \nFunction Name :isAmountAvailable");
	printf("\nTest Case 1 : 10000.3 \nExpected Result :SERVER_OK \nInput Data:");
	getTransactionAmount(&terminal);
	isAmountAvailable(&terminal, &REFRENCE);
	printf("\nTest Case 1 : 20000000.3 \nExpected Result : LOW_BALANCE\nInput Data:");
	getTransactionAmount(&terminal);
	isAmountAvailable(&terminal, &REFRENCE);



}
void saveTransactionTest(void)
{
	printf("\nTester Name : Nour abdel-aziz \nFunction Name :saveTransaction");
	printf("\nTest Case 1 : 0 \nExpected Result : \nInput Data:");
}
void listSavedTransactionsTest(void)
{
	printf("\nTester Name : Nour abdel-aziz \nFunction Name :listSavedTransactions");
	printf("\nTest Case 1 : 0 \nExpected Result : \nInput Data:");
}

