
#ifndef TERMINAL_H_

#define TERMINAL_H_

/*    Section : Includes    */
#include<string.h>
#include <stdlib.h>

#include "../Card/Card.h"

/* Section : Type decarations*/

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;


typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;


typedef enum EN_terminalError_t
{
    TERMINAL_OK, WRONG_DATE, 
    EXPIRED_CARD, INVALID_CARD,
    INVALID_AMOUNT, EXCEED_MAX_AMOUNT,
    INVALID_MAX_AMOUNT

}EN_terminalError_t;

/* Section : Function decalrations  */

/*
* @brief Get the Transaction date of the entered card
* @param termData pointer to the configurations @ref ST_terminalData_t
* @return Status of the function
* (CARD_OK) : The function done successfully
* (WRONG_PAN) : The function has issue to perform this action
*/

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);

/*
* @brief Check if the card is expired or not 
* @param cardData pointer to the configurations @ref ST_cardData_t
* @param termData pointer to the configurations @ref ST_terminalData_t
* @return Status of the function
* (TERMINAL_OK) : The function done successfully
* (EXPIRED_CARD) : The function has issue to perform this action
*/

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData);

/*
* @brief get Transaction Amount of the card
* @param termData pointer to the configurations @ref ST_terminalData_t
* @return Status of the function
* (TERMINAL_OK) : The function done successfully
* (INVALID_AMOUNT) : The function has issue to perform this action
*/

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);

/*
* @brief check if the transaction amount is beow max amout or not
* @param termData pointer to the configurations @ref ST_terminalData_t
* @return Status of the function
* (TERMINAL_OK) : The function done successfully
* (EXCEED_MAX_AMOUNT) : The function has issue to perform this action
*/

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);

/*
* @brief pass the terminal the max amout it can recognise
* @param termData pointer to the configurations @ref ST_terminalData_t
* @param maxAmout Variable has the max amout to pass
* @return Status of the function
* (TERMINAL_OK) : The function done successfully
* (INVALID_MAX_AMOUNT) : The function has issue to perform this action
*/

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount);

/*
* @brief check of the card number is vaid or not
* @param termData pointer to the configurations @ref ST_terminalData_t
* @param maxAmout Variable has the max amout to pass
* @return Status of the function
* (TERMINAL_OK) : The function done successfully
* (INVALID_CARD) : The function has issue to perform this action
*/

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData); // Optional

// test fnctions

void getTransactionDateTest(void);
void isCardExpriedTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmountTest(void);
void setMaxAmountTest(void);
#endif // !1

//extern ST_terminalData_t* terminalptr;



