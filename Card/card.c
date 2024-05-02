/************************************/
/*	Author	  :	Nour Abd EL-Aziz 	*/
/*	SWC		  : CARD Module  		*/
/*  Layer	  : CARD				*/
/*	Version	  :	1.0		  			*/
/*	Date	  :	December  9, 2022	*/
/*	Last Edit :	N/A					*/
/************************************/

#include "card.h"
#include "app.h"
#include "STD_types.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
//extern ST_cardData_t card;
//Function 1 checking the card holder name check if it ok with name criteria or not based on what defined in ruberic
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	char namee[30] = { 0 };
	printf("\nCard Holder Name : ");
	gets(namee);
	//if condition check if name within the required size or not
	if (namee == NULL || strlen(namee) < 20 || strlen(namee) > 24) //exceed or less than the limit
	{
		printf("Actual RESULT :WRONG_NAME");
		return WRONG_NAME;
	}
	else //within required size
	{
		char i = 0;
		for ( i = 0;i < strlen(namee);i++)
		{
			if (!isalpha(namee[i]) && (namee[i] != ' ')) // check the char is alphabetic and no null char entered
			{
				printf("Actual Result : WRONG_NAME!");
				return WRONG_NAME;
			}
			else
			{
				cardData->cardHolderName[i] = namee[i];
			}
		}
		cardData->cardHolderName[i] = '\0';
		printf("Actual Result : CARD_OK");
		return CARD_OK;
	}
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	if (!cardData)
	{
		//printf("Actual Reult: WRONG_EXP_DATE");
		return WRONG_EXP_DATE;
	}
	u8 date[6] = { 0 }; // MM/YY
	//printf("\n Enter Card Expirey Date : ");
	gets(date);
	char i = 0;
	for (i = 0; i < 6; i++)
	{
		if ((strlen(date) != 5) || (date[2] != '/') || (date[0] > '1') ) //check not more than 5char check month not morethan12
		{
			//printf("Actual Reult: WRONG_EXP_DATE");
			return WRONG_EXP_DATE;
		}
		else
		{
			//printf("Actual Result : CARD_OK");
			return CARD_OK;
		}
	}
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	if (!cardData)
	{
		printf("Actual Result : WRONG_CARD_PAN");
		return WRONG_PAN;
	}
	u8 pan[19] = { 0 };
	printf("\nEnter Card PAN : ");
	gets(pan);

	if ((strlen(pan) < 16) || (strlen(pan) > 19))
	{
		printf("Actual Result: WRONG_CARD_PAN");
		return WRONG_PAN;
	}
	char i = 0;
	for (i = 0;i < strlen(pan);i++)
	{
		if ( pan[i] == '  ')
		{
			printf("Actual Result :WRONG_PAN!");
			return WRONG_PAN;
		}
		else
		{
			cardData->primaryAccountNumber[i] = pan[i];
		}
	}
	printf("Actual Result : PAN_OK");
	return CARD_OK;
}

void getCardHolderNameTest(void)
{
	ST_cardData_t card;
	printf("\nTester Name : Nour abdel-aziz\nFunction Name : getCardHolderName");
	printf("\nTest Case 1 : NOUUUUUUURRRRRRRR AAAABBBDDDDEELLLAZZIIZZ\nExpected Result : WRONG_NAME\nInput Data: ");
	getCardHolderName(&card);
	printf("\nTest Case 2 : NOUUUUUUURRRRRRRR***\nExpected Result : WRONG_NAME\nInput Data: ");
	getCardHolderName(&card);
	printf("\nTest Case 3 :' '\nExpected Result : WRONG_NAME\nInput Data: ");
	getCardHolderName(&card);
	printf("\nTest Case 4 : NOUR \nExpected Result : WRONG_NAME\nInput Data: ");
	getCardHolderName(&card);
	printf("\nTest Case 5 : Nour Abdelaziz Mohammed \nExpected Result : CARD_NAME_OK\nInput Data: ");
	getCardHolderName(&card);
}

void getCardExpiryDateTest(void)
{
	printf("\nTester Name : Nour abdel-aziz\nFunction Name : getCardExpiryDate");
	printf("\nTest Case 1 : 22/12\nExpected Result : WRONG_EXPIRY_DATE\nInput Data: ");
	getCardExpiryDate(&card);
	printf("\nTest Case 2 : 12654\nExpected Result : WRONG_EXPIRY_DATE\nInput Data: ");
	getCardExpiryDate(&card);
	printf("\nTest Case 3 :' '\nExpected Result : WRONG_EXPIRY_DATE\nInput Data: ");
	getCardExpiryDate(&card);
	printf("\nTest Case 4 : 15*55 \nExpected Result :WRONG_EXPIRY_DATE\nInput Data: ");
	getCardExpiryDate(&card);
	printf("\nTest Case 5 : 12/22 \nExpected Result : CARD_EXPIRY_DATE_OK\nInput Data: ");
	getCardExpiryDate(&card);
}

void getCardPANTest(void)
{
	printf("\nTester Name : Nour abdel-aziz\nFunction Name : getCardPAN");
	printf("\nTest Case 1 : GYUGUU\nExpected Result : WRONG_PAN\nInput Data: ");
	getCardPAN(&card);
	printf("\nTest Case 2 : NJ JBH\nExpected Result : WRONG_PAN\nInput Data: ");
	getCardPAN(&card);
	printf("\nTest Case 3 :' '\nExpected Result : WRONG_PAN\nInput Data: ");
	getCardPAN(&card);
	printf("\nTest Case 4 : 786434678907654357 \nExpected Result : PAN_OK\nInput Data: ");
	getCardPAN(&card);

}