/************************************/
/*	Author	  :	Nour Abd EL-Aziz 	*/
/*	SWC		  : TERMINAL Module  	*/
/*  Layer	  : TERMINAL			*/
/*	Version	  :	1.0		  			*/
/*	Date	  :	December  9, 2022	*/
/*	Last Edit :	N/A					*/
/************************************/
#pragma once
#ifndef TERMINAL_H_
#define TERMINAL_H_
#include "STD_types.h"
#include "card.h"

typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    u8 transactionDate[11];
}ST_terminalData_t;

ST_terminalData_t terminal;

typedef enum EN_terminalError_t
{
    TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

struct date
{
    u8 da_day, da_mon, da_year;
}
dt;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount);
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData); // Optional

void getTransactionDateTest(void);
void isCardExpriedTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmountTest(void);
void setMaxAmountTest(void);
void isValidCardPANTest(void);

#endif
