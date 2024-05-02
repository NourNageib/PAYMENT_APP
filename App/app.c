
/************************************/
/*	Author	  :	Nour Abd EL-Aziz 	*/
/*	SWC		  : APP Module  		*/
/*  Layer	  : App					*/
/*	Version	  :	1.0		  			*/
/*	Date	  :	December  9, 2022	*/
/*	Last Edit :	N/A					*/
/************************************/
#include"server.h"
#include "card.h"
#include "terminal.h"
#include "app.h"
#include "STD_types.h"
#include <string.h>



void appStart(void)
{
	extern ST_terminalData_t terminal;
	extern ST_cardData_t card;
	extern ST_accountsDB_t REFRENCE;
	extern ST_transaction_t trans_data;

	getCardHolderName(&card);
	getCardPAN(&card);
	getCardExpiryDate(&card);
	getTransactionDate(&terminal);
	setMaxAmount(&terminal, 100000.1);
	getTransactionAmount(&terminal);

	if (isCardExpired(&card, &terminal) == TERMINAL_OK)
	{
		getTransactionAmount(&terminal);
		if (isBelowMaxAmount(&terminal) == TERMINAL_OK)
		{
			if (isValidAccount(&card, &REFRENCE) == SERVER_OK)
			{
				recieveTransactionData(&trans_data);
				if (recieveTransactionData(&trans_data) == APPROVED)
				{
					if (saveTransaction(&trans_data) == SERVER_OK)
					{
						printf("Transaction Saved ");
					}
					else
					{
						printf("Saving Faild");
					}
				}
				else if (recieveTransactionData(&trans_data) == DECLINED_STOLEN_CARD)
				{
					printf("Decliend Stolen Card");
				}
				else if (recieveTransactionData(&trans_data) == DECLINED_INSUFFECIENT_FUND)
				{
					printf("Insuffecient Fund");
				}
			}
		}
	}
}
