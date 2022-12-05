#include <stdio.h>
#include <string.h>

#include "../helpers/creationHelper.h"
#include "../helpers/handHelper.h"
#include "../helpers/printHelper.h"
#include "../definitions/card.h"
#include "../definitions/hand.h"
#include "../definitions/constants.h"

CARD *chooseBestCard(CARD *topCard, HAND *hand)
{
    // return NULL;
}

void actionAnotherPlayer(char *action, CARD *topTable, char *complement)
{
    if (strcmp(action, "DISCARD") == 0)
    {

        CARD *new = createCard(complement);
        *topTable = *new;

        if (strcmp(topTable->number, "C") == 0 || strcmp(topTable->number, "A") == 0)
        {
            char complement2[MAX_LINE];
            scanf(" %s", complement2);
            topTable->suit = complement2;
        }
    }
}

void myAction(CARD *topTable, HAND *hand)
{
    debug(topTable->number);
    if (strcmp(topTable->number, "V") == 0)
    {
        char cardString1[MAX_LINE];
        char cardString2[MAX_LINE];
        printf("BUY 2\n");
        scanf("%s %s\n", cardString1, cardString2);

        CARD *more1 = createCard(cardString1);
        CARD *more2 = createCard(cardString2);

        addToHand(hand, more1);
        addToHand(hand, more2);
        return;
    }
    else if (strcmp(topTable->number, "C") == 0)
    {
        char cardString1[MAX_LINE];
        char cardString2[MAX_LINE];
        char cardString3[MAX_LINE];
        char cardString4[MAX_LINE];
        printf("BUY 4\n");
        scanf("%s %s %s %s\n", cardString1, cardString2, cardString3, cardString4);

        CARD *more1 = createCard(cardString1);
        CARD *more2 = createCard(cardString2);
        CARD *more3 = createCard(cardString3);
        CARD *more4 = createCard(cardString4);

        addToHand(hand, more1);
        addToHand(hand, more2);
        addToHand(hand, more3);
        addToHand(hand, more4);
        return;
    }

    chooseBestCard(topTable, hand);
    CARD *choice = NULL;

    if (choice == NULL)
    {
        printf("BUY 1\n");
        char cardString[MAX_LINE];
        scanf("%s\n", cardString);
        CARD *more = createCard(cardString);
        addToHand(hand, more);
    }
    else
    {
        printf("DISCARD %s\n", choice->value);
    }
}