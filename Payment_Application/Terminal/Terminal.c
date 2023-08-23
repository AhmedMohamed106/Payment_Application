#include "terminal.h"
#include <ctype.h>
#include <stdio.h>
#include<time.h>
#include <string.h>
#include "Terminal.h"

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE


/*
* @brief Get the Transaction date of the entered card
* @param termData pointer to the configurations @ref ST_terminalData_t
* @return Status of the function
* (CARD_OK) : The function done successfully
* (WRONG_PAN) : The function has issue to perform this action
*/

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {


	EN_terminalError_t error_transaction = 0;
	uint8_t transaction_date[15] = { 0 };
	uint16_t k = 0;

	gets(transaction_date);

	if ((strlen(transaction_date) != 10) || (transaction_date[2] != '/')
		|| (transaction_date[5] != '/') || (transaction_date == NULL) ||
		((transaction_date[0] >= '3' ) && (transaction_date[1]> '1')) || (transaction_date[3] > '1') 
		|| ((transaction_date[3] == '1') && (transaction_date[4] > '2')))

	{
		error_transaction = WRONG_DATE;
		
	}

	else 
	{

		for (k; k < strlen(transaction_date); k++)
		{
			termData->transactionDate[k] = transaction_date[k];
		}

		error_transaction = TERMINAL_OK;
		//termData->transactionDate[10] = '\0';
		
	}
	return error_transaction;
}


/*
* @brief Check if the card is expired or not
* @param cardData pointer to the configurations @ref ST_cardData_t
* @param termData pointer to the configurations @ref ST_terminalData_t
* @return Status of the function
* (TERMINAL_OK) : The function done successfully
* (EXPIRED_CARD) : The function has issue to perform this action
*/


EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
	EN_terminalError_t ThisFunction_ErrorState = 0;

	uint8_t CardExpirationMonth =
		((cardData->cardExpirationDate[0] - '0') * 10) + (cardData->cardExpirationDate[1] - '0');
	uint8_t CardExpirationYear =
		((cardData->cardExpirationDate[3] - '0') * 10) + (cardData->cardExpirationDate[4] - '0');

	uint8_t TransactionMonth =
		((termData->transactionDate[3] - '0') * 10) + (termData->transactionDate[4] - '0');
	uint8_t TransactionYear =
		((termData->transactionDate[8] - '0') * 10) + (termData->transactionDate[9] - '0');

	if ((CardExpirationYear < TransactionYear))
	{
		ThisFunction_ErrorState = EXPIRED_CARD;
	}
	else if ((CardExpirationYear == TransactionYear))
	{
		if ((CardExpirationMonth <= TransactionMonth))

			//||(CardExpirationMonth == TransactionMonth))
		{
			ThisFunction_ErrorState = EXPIRED_CARD;
		}

		else { ThisFunction_ErrorState = TERMINAL_OK; }
	}

	else { ThisFunction_ErrorState = TERMINAL_OK; }

	return ThisFunction_ErrorState;
}

#pragma region expiredate another method

/*
	EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
	{


		EN_terminalError_t expired_card_error = 0;
		uint8_t m_transaction[3] = { 0 };
		uint8_t y_transaction[3] = { 0 };
		uint8_t m_expired[3] = { 0 };
		uint8_t y_expired[3] = { 0 };
		uint16_t m_transaction_number = 0;
		uint16_t y_transaction_number = 0;
		uint16_t m_expire_number = 0;
		uint16_t y_expire_number = 0;

		m_transaction[0] = termData->transactionDate[3];
		m_transaction[1] = termData->transactionDate[4];
		m_transaction[2] = '\0';
		m_transaction_number = atoi(m_transaction);

		y_transaction[0] = termData->transactionDate[8];
		y_transaction[1] = termData->transactionDate[9];
		y_transaction[2] = '\0';
		y_transaction_number = atoi(y_transaction);

		m_expired[0] = cardData->cardExpirationDate[0];
		m_expired[1] = cardData->cardExpirationDate[1];
		m_expired[2] = '\0';
		m_expire_number = atoi(m_expired);

		y_expired[0] = cardData->cardExpirationDate[3];
		y_expired[1] = cardData->cardExpirationDate[4];
		y_expired[2] = '\0';
		y_expire_number = atoi(y_expired);

		if (y_transaction_number > y_expire_number)
		{
			expired_card_error = EXPIRED_CARD;
		}
		else if (y_transaction_number < y_expire_number)
		{
			expired_card_error = TERMINAL_OK;
		}
		else if (y_transaction_number == y_expire_number)
		{
			if (m_transaction_number <= m_expire_number)
			{
				expired_card_error = TERMINAL_OK;
			}
			else if (m_transaction_number > m_expire_number)
			{
				expired_card_error = EXPIRED_CARD;
			}
		}

		return expired_card_error;

	}

	*/
#pragma endregion

	/*
	* @brief get Transaction Amount of the card
	* @param termData pointer to the configurations @ref ST_terminalData_t
	* @return Status of the function
	* (TERMINAL_OK) : The function done successfully
	* (INVALID_AMOUNT) : The function has issue to perform this action
	*/

	EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) 
	{

		EN_cardError_t Trans_amount_error = 0;

		float TransAmount = 0;

		scanf_s("%f", &TransAmount);

		if (TransAmount <= 0.0)
		{
			Trans_amount_error = INVALID_AMOUNT;
		}
		else
		{
			Trans_amount_error = TERMINAL_OK;
			termData->transAmount = TransAmount;
		}
		return Trans_amount_error;
	}
	
	/*
	* @brief check if the transaction amount is beow max amout or not
	* @param termData pointer to the configurations @ref ST_terminalData_t
	* @return Status of the function
	* (TERMINAL_OK) : The function done successfully
	* (EXCEED_MAX_AMOUNT) : The function has issue to perform this action
	*/

	EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
	{
		
		termData->maxTransAmount = 5000;
		EN_cardError_t Max_amount_error = 0;
		if (termData->transAmount > termData->maxTransAmount)
		{
			Max_amount_error = EXCEED_MAX_AMOUNT;
		}
		else {
			Max_amount_error = TERMINAL_OK;
		}
		return Max_amount_error;
	}



/*
* @brief pass the terminal the max amout it can recognise
* @param termData pointer to the configurations @ref ST_terminalData_t
* @param maxAmout Variable has the max amout to pass
* @return Status of the function
* (TERMINAL_OK) : The function done successfully
* (INVALID_MAX_AMOUNT) : The function has issue to perform this action
*/

	EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
	{
		EN_terminalError_t max_amount_error = 0;
		if (maxAmount <= 0.0)
		{
			max_amount_error = INVALID_MAX_AMOUNT;
		}
		else
		{
			max_amount_error = TERMINAL_OK;
			termData->maxTransAmount = maxAmount;
		}
		return max_amount_error;
	}


	//optional

	EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
	{
		EN_terminalError_t isVaidPAN = 0;
		uint16_t sum = 0 , i;
		_Bool isSecond = 0;
		for( i = strlen(cardData->primaryAccountNumber)-1;i>=0;i--)
		{
			uint16_t d = cardData->primaryAccountNumber[i] - '0';
			if (isSecond != 0)
				d = d * 2;
			sum += d / 10;
			sum += d % 10;
			isSecond = !isSecond;
		}
		if (sum % 10 == 0)
			isVaidPAN = TERMINAL_OK;
		else
			isVaidPAN = INVALID_CARD;
		return isVaidPAN;



	}


	void getTransactionDateTest(void)
	{

		ST_terminalData_t terminalptr;
		EN_terminalError_t error;

		printf("Tester Name  : Ahmed Mohamed \n");
		printf("Function Name: getTransactionDate \n");
		
		for (uint16_t i = 0; i < 3; i++)
		{
			printf("Please enter transaction date in this form DD/MM/YYYY :\t");
			error = getTransactionDate(&terminalptr);
			if (error != TERMINAL_OK)
			{
				printf("\n your Function has issue: \n");
				printf("Actual Result : WRONG_DATE\n");
			}
			else
			{
				printf("Actual Result : TERMINAL_OK\n");
				break;
			}
		}

	}


    void isCardExpriedTest(void)
	{
		ST_terminalData_t terminalptr;
		ST_cardData_t cardptr;
		EN_terminalError_t error;


		printf("Tester Name  : Ahmed Mohamed \n");
		printf("Function Name: isCardExpried \n");
		
		for (uint16_t i = 0; i < 10; i++)
		{
			printf("Expire date in format MM/YY : \t");
			getCardExpiryDate(&cardptr);
			printf("Transaction date in format DD/MM/YYYY : \t");
			getTransactionDate(&terminalptr);
			error = isCardExpired(&cardptr, &terminalptr);
			if (error != TERMINAL_OK)
			{
				printf("\n your Function has issue: \n");
				printf("Actual Result : EXPIRED_CARD\n");
			}
			else
			{
				printf("Actual Result : TERMINAL_OK\n");
				break;
			}
		}
		

	}
	void getTransactionAmountTest(void)
	{
		ST_terminalData_t terminalptr;
		EN_terminalError_t error;

		printf("Tester Name: Ahmed Mohamed \n");
		printf("Function Name: getTransactionAmount \n");
		
		for (uint16_t i = 0; i < 3; i++)
		{
			printf("Enter transaction amount you need in USD: \t");

			error = getTransactionAmount(&terminalptr);
			if (error != TERMINAL_OK)
			{
				printf("\n your Function has issue: \n");
				printf("Actual Result : INVALID_AMOUNT\n");
			}
			else
			{
				printf("Actual Result : TERMINAL_OK\n");
				break;
			}
		}

	}


	void isBelowMaxAmountTest(void)
	{
		ST_terminalData_t terminalptr;
		EN_terminalError_t error;

		printf("Tester Name  : Ahmed Mohamed \n");
		printf("Function Name: isBelowMaxAmount \n");


		for (uint16_t i = 0; i < 3; i++)
		{
			printf("Enter transaction amount you need in USD: \t");
			getTransactionAmount(&terminalptr);
			error = isBelowMaxAmount(&terminalptr);
			if (error != TERMINAL_OK)
			{
				printf("your function has an issue\n");
				printf("Actual Result : EXCEED_MAX_AMOUNT\n");
			}
			else
			{
				printf("Actual Result : TERMINAL_OK\n");
				break;
			}
		}
	}


	void setMaxAmountTest(void)
	{
		ST_terminalData_t terminalptr;
		EN_terminalError_t error;

		printf("Tester Name: Ahmed Mohamed \n");
		printf("Function Name: setMaxAmount \n");
		error = setMaxAmount(&terminalptr , 0);
		if (error != TERMINAL_OK)
			printf("Actual Result : INVALID_MAX_AMOUNT\n");
		else
			printf("Actual Result : TERMINAL_OK\n");
		printf("\nTest Case 2 :Negative \n Expected Result : INVALID_MAX_AMOUNT \nInput Data : ");
		error = setMaxAmount(&terminalptr , -5214250);
		if (error != TERMINAL_OK)
			printf("Actual Result : INVALID_MAX_AMOUNT\n");
		else
			printf("Actual Result : TERMINAL_OK\n");

		printf("\nTest Case 3 :Positive \nExpected Result : TERMINAL_OK\nInput Data : ");
		error = setMaxAmount(&terminalptr , 1201120);
		if (error != TERMINAL_OK)
			printf("Actual Result : INVALID_MAX_AMOUNT\n\n");
		else
			printf("Actual Result : TERMINAL_OK\n\n");
	

	}



	








	


