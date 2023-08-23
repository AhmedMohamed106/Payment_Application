
#ifndef CARD_H_
#define CARD_H_


/** Section : Includes **/
#include<string.h>
#include <stdlib.h>


/* Section: Data Type Declarations */

typedef unsigned char uint8_t;
typedef unsigned int  uint16_t;
typedef unsigned long uint32_t;

typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN

}EN_cardError_t;


/* Section: Function Declarations */

/*
* @brief Get the card holder name
* @param cardData pointer to the configurations @ref ST_cardData_t
* @return Status of the function
* (CARD_OK) : The function done successfully
* (WRONG_NAME) : The function has issue to perform this action
*/

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);

/*
* @brief Get the Expire date of the entered card
* @param cardData pointer to the configurations @ref ST_cardData_t
* @return Status of the function
* (CARD_OK) : The function done successfully
* (WRONG_EXP_DATE) : The function has issue to perform this action
*/

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);

/*
* @brief Get the Permanent Account Number of the entered card
* @param cardData pointer to the configurations @ref ST_cardData_t
* @return Status of the function
* (CARD_OK) : The function done successfully
* (WRONG_PAN) : The function has issue to perform this action
*/
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

/* test functions for the Interface functions of card module */
void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);


#endif // !1

