
#include <ctype.h>
#include <stdio.h>
#include<time.h>
#include <string.h>
#include "card.h"

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS


/*
* @brief Get the card holder name
* @param cardData pointer to the configurations @ref ST_cardData_t
* @return Status of the function
* (CARD_OK) : The function done successfully
* (WRONG_NAME) : The function has issue to perform this action
*/

EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {

	EN_cardError_t name_error_type = 0;
	uint8_t name[25] = { 0 };

	gets(name);

	if (name == NULL || strlen(name) < 20 || strlen(name) > 24)
	{
		name_error_type = WRONG_NAME;
		return name_error_type;
	}
	else
	{
		uint16_t i = 0;
		for (i = 0; i < strlen(name); i++) {

			if (!isalpha(name[i]) && (name[i] != ' '))
			{
				name_error_type = WRONG_NAME;
				return name_error_type;
			}
			else
			{
				cardData->cardHolderName[i] = name[i];
			}
		}

		cardData->cardHolderName[i] = '\0';
		name_error_type = CARD_OK;
		return name_error_type;



	}


}

/*
* @brief Get the Expire date of the entered card
* @param cardData pointer to the configurations @ref ST_cardData_t
* @return Status of the function
* (CARD_OK) : The function done successfully
* (WRONG_EXP_DATE) : The function has issue to perform this action
*/

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {

	EN_cardError_t error_expire_date = 0;
	uint8_t Expired_date[15] = { 0 };

	if (!cardData) {

		error_expire_date = WRONG_EXP_DATE;
		return error_expire_date;

	}

	gets(Expired_date);

	uint16_t i = 0;
	for (i;i < 6;i++)
	{

		if ((strlen(Expired_date) != 5) || (Expired_date[0] > '1') || ((Expired_date[0] == '1') && (Expired_date[1] > '2')) || (Expired_date[2] != '/'))
		{
			error_expire_date = WRONG_EXP_DATE;
			
		}

		else

		{
			error_expire_date = CARD_OK;
			
		}

	}

	return error_expire_date;
}

/*
* @brief Get the Permanent Account Number of the entered card
* @param cardData pointer to the configurations @ref ST_cardData_t
* @return Status of the function
* (CARD_OK) : The function done successfully
* (WRONG_PAN) : The function has issue to perform this action
*/

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {


	EN_cardError_t error_pan = 0;
	uint8_t prim_acc_number[50] = { 0 };
	uint16_t x = 0;

	if (!cardData) {
		error_pan = WRONG_PAN;
		return error_pan;
	}



	gets(prim_acc_number);

	if ((strlen(prim_acc_number) < 16) || (strlen(prim_acc_number) > 19)) {

		error_pan = WRONG_PAN;
		return error_pan;

	}

	else
	{
		error_pan = CARD_OK;
		return error_pan;
	}


}



// test functions

// function  1 : getCardHolderName

void getCardHolderNameTest(void) {


	ST_cardData_t cardptr;
	EN_cardError_t error;

	printf("\nTester Name: Ahmed Mohamed \n");
	printf("Function Name: getCardHolderName \n");

	//printf("\nTest Case 1 : NULL \nExpected Result : WRONG_NAME\nInput Data : ");

	uint16_t counter = 0;

	for (counter; counter < 3; counter++)
	{
		printf("Enter your card holder name : \t");

		error = getCardHolderName(&cardptr);
		if (error != CARD_OK)
		{
			printf("Function has wrong issue\n");
			printf("\nActual Result : WRONG_NAME\n");
		}

		else
		{
			printf("Actual Result : CARD_OK\n");
			break;
		}

	}
	

}

void getCardExpiryDateTest(void) {


	ST_cardData_t cardptr;
	EN_cardError_t error;

	printf("Tester Name:   Ahmed Mohamed     \n\n");
	printf("Function Name: getCardExpiryDate \n");

	for (uint16_t i = 0; i < 3; i++)
	{
		printf("\n Enter card expiration date in format MM/YY  : ");

		error = getCardExpiryDate(&cardptr);

		if (error != CARD_OK)
		{
			printf("your Function has wrong issue \n");
			printf("Actual Result : WRONG_EXP_DATE\n");
		}
		else
		{
			printf("Actual Result : CARD_OK\n");
			break;
		}
	}


}

void getCardPANTest(void) {


	ST_cardData_t cardptr;
	EN_cardError_t error;

	printf("Tester Name:   Ahmed Mohamed \n");
	printf("Function Name: getCardPAN    \n");

	


	for (uint16_t i = 0; i < 3; i++)
	{
		printf("Enter your card PAN: ");
		error = getCardPAN(&cardptr);

		if (error != CARD_OK)
		{
			printf("your Function has wrong issue \n");
			printf("Actual Result : WRONG_PAN\n");
		}
		else
		{
			printf("actual Result : CARD_OK\n");
			break;
		}
	}
	
}




