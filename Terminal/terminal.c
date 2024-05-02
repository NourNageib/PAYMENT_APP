/************************************/
/*	Author	  :	Nour Abd EL-Aziz 	*/
/*	SWC		  : TERMINAL Module  	*/
/*  Layer	  : TERMINAL			*/
/*	Version	  :	1.0		  			*/
/*	Date	  :	December  9, 2022	*/
/*	Last Edit :	N/A					*/
/************************************/

#include"terminal.h"
#include "app.h"
#include "STD_types.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

extern ST_terminalData_t terminal;
extern ST_cardData_t card;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	if (!termData)
	{
		printf("ACTUAL RESULT : WRONG_TRANSACTION_DATE\n");
		return WRONG_DATE;
	}

	u8 trans_date[10] = { 0 };// DD / MM / YYYY
	//printf("\nPlease enter Transaction Date : ");
	gets(trans_date);         // 01 2 34 5 6789


//int  day, month, year;
//time_t now;
//time(&now);
//struct tm* local = localtime(&now);
//day = local->tm_mday;            // get day of month (1 to 31)
//month = local->tm_mon + 1;      // get month of year (0 to 11)
//year = local->tm_year + 1900;   // get year since 1900
//printf("Date is: %02d/%02d/%d\n", day, month, year);


	if (strlen(trans_date) < 10 || (trans_date[2] != '/') || (trans_date[5] != '/'))
	{
		//printf("ACTUAL RESULT : WRONG_TRANSACTION_DATE\n");
		return WRONG_DATE;
	}
	else
	{

		for (u8 i = 0;i < strlen(trans_date); i++)
		{

			termData->transactionDate[i] = trans_date[i];
		}

		//printf("ACTUAL RESULT : TRANSACTION_DATE _OK\n");
		return TERMINAL_OK;
	}
}




EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	if ((cardData->cardExpirationDate[3] < termData->transactionDate[8]))
	{
		if ((cardData->cardExpirationDate[3] == termData->transactionDate[8]) && (cardData->cardExpirationDate[4] < termData->transactionDate[9]))
	{
	printf("ACTUAL RESULT : EXPIRED_CARD\n");
	return EXPIRED_CARD;
	}
	}
	else if ((cardData->cardExpirationDate[3] == termData->transactionDate[8]) && (cardData->cardExpirationDate[4] == termData->transactionDate[9]))
	{
		if ((cardData->cardExpirationDate[0] < termData->transactionDate[3]) || ((cardData->cardExpirationDate[0] == termData->transactionDate[3]) && (cardData->cardExpirationDate[1] < termData->transactionDate[4])))
		{
			printf("ACTUAL RESULT : EXPIRED_CARD\n");
			return EXPIRED_CARD;
		}
		else
		{
			printf("ACTUAL RESULT: TEMINAL OK\n");
			return TERMINAL_OK;
		}
	}
	else
	{
		printf("ACTUAL RESULT: TEMINAL OK\n");
		return TERMINAL_OK;
	}
}


EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	f32 trans_amount = 0.0;
	printf("\n Please enter Transaction Amount : ");
	scanf_s("%f", &trans_amount);

	if (trans_amount <= 0)
	{
		printf("ACTUAL RESULT : INSUFFECIENT_AMOUNT\n");
		return INVALID_AMOUNT;
	}
	else
	{
		termData->transAmount = trans_amount;
		printf("Actual Result : TERMINAL_OK\n");
		return TERMINAL_OK;
	}
}




EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	
	termData->maxTransAmount = 8000000;
	if ((termData->transAmount) > (termData->maxTransAmount))
	{
		printf("ACTUAL RESULTt : EXCEEDED_MAX_AMOUNT\n");
		return EXCEED_MAX_AMOUNT;
	}
	else if (termData->transAmount == 0)
	{
		printf("error");
	}
	else if ((termData->transAmount) <= (termData->maxTransAmount))
	{
		printf("ACTUAL RESULT : AMOUNT_AVALIABLE\n");
		return TERMINAL_OK;
	}
	
}



EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
	if (maxAmount <= 0)
	{
		printf("ACTUAL RESULT : INVALID_MAX_AMOUNT\n");
		return INVALID_MAX_AMOUNT;

	}
	else
	{
		termData->maxTransAmount = maxAmount;
		printf("ACTUAL RESULT : TERMINAL_OK\n");
		return TERMINAL_OK;
	}
}


void getTransactionDateTest(void)
{
	printf("\nTester Name : Nour abdel-aziz\nFunction Name : getTransactionDate");
	printf("\nTest Case 1 : 365/63/3563\n Exxpected Result : WRONG_TRANS_DATE\nInput Data:");
	getTransactionDate(&terminal);
	printf("\nTest Case 2 : 36|22|2222\n Exxpected Result : WRONG_TRANS_DATE\nInput Data:");
	getTransactionDate(&terminal);
	printf("\nTest Case 3 : 36\n Exxpected Result : WRONG_TRANS_DATE\nInput Data:");
	getTransactionDate(&terminal);
	printf("\nTest Case 4 : 19/12/2022\n Exxpected Result : TRANS_DATE_OK\nInput Data:");
	getTransactionDate(&terminal);
}


void isCardExpriedTest(void)
{
	printf("\nTester Name : Nour abdel-aziz\nFunction Name : isCardExpriedTest");
	printf("\nTest Case 1 : NOT EXPIRED \n Exxpected Result : TERMINAL_OK \nInput Data:");
	getTransactionDate(&terminal);
	getCardExpiryDate(&card);
	isCardExpired(&card, &terminal);
	printf("\nTest Case 2 : EXPIRED\n Exxpected Result : EXPIRED_CARD \nInput Data:");
	getTransactionDate(&terminal);
	getCardExpiryDate(&card);
	isCardExpired(&card, &terminal);
}



void getTransactionAmountTest(void)
{
	printf("\nTester Name : Nour abdel-aziz \nFunction Name :getTransactionAmount");
	printf("\nTest Case 1 : 0 \nExpected Result : INVALID_AMOUNT\nInput Data:");
	getTransactionAmount(&terminal);
	printf("\nTest Case 2 : -367626 \nExpected Result : ERROR \nInput Data:");
	getTransactionAmount(&terminal);
	printf("\nTest Case 3 : 367626 \nExpected Result : TERMINAL_OK \nInput Data:");
	getTransactionAmount(&terminal);
}


void isBelowMaxAmountTest(void)
{
	printf("\nTester Name : Nour abdel-aziz\nFunction Name : isBelowMaxAmount");
	printf("\nTest Case 1 :0 \nExpected Result : INVALID_AMOUNT \nInput Data:");
	getTransactionAmount(&terminal);
	isBelowMaxAmount(&terminal);
	printf("\nTest Case 2 : 888888 \nExpected Result : EXCEEDED_MAX_AMOUNT\nInput Data:");
	getTransactionAmount(&terminal);
	isBelowMaxAmount(&terminal);
	
	printf("\nTest Case 3 :4000 \nExpected Result : AVALIABLE_AMOUNT \nInput Data:");
	getTransactionAmount(&terminal);
	isBelowMaxAmount(&terminal);
}



void setMaxAmountTest(void)
{
	printf("\nTester Name : Nour abdel-aziz\nFunction Name : setMaxAmount");
}

