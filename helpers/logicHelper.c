#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../definitions/card.h"
#include "../definitions/hand.h"
#include "../definitions/constants.h"
#include "../definitions/suits.h"
#include "../definitions/phrases.h"
#include "../definitions/field.h"

#include "../helpers/creationHelper.h"
#include "../helpers/handHelper.h"
#include "../helpers/printHelper.h"
#include "../helpers/cardHelper.h"

int getIndexCardBy(FIELD, char *, char *, HAND *);

int quantSuitInHand(HAND *hand, char *suit)
{
    int cont = 0;
    for (int i = 0; i < hand->amountCards; i++)
    {
        if (strcmp(suit, hand->cards[i]->suit) == 0 && strcmp("C", hand->cards[i]->number) != 0 && strcmp("A", hand->cards[i]->number) != 0)
        {
            cont++;
        }
    }
    return cont;
}

char *chooseBestSuit(HAND *hand)
{
    char *suit = calloc(10, sizeof(char));
    strcpy(suit, hand->cards[0]->suit);

    int amountHearts = quantSuitInHand(hand, HEARTS_U);
    int amountDiamonds = quantSuitInHand(hand, DIAMONDS_U);
    int amountClubs = quantSuitInHand(hand, CLUBS_U);
    int amountSpades = quantSuitInHand(hand, SPADES_U);

    int amounts[] = {amountHearts, amountDiamonds, amountClubs, amountSpades};

    int index = 0;

    for (int i = 0; i < 4; i++)
        if (amounts[i] > amounts[index])
            index = i;

    switch (index)
    {
    case 0:
        return HEARTS_U;
    case 1:
        return DIAMONDS_U;
    case 2:
        return CLUBS_U;
    case 3:
        return SPADES_U;
    default:
        return HEARTS_U;
    }
}

CARD *chooseBestCard(CARD *topCard, HAND *hand)
{
    // Find any valete
    int i = getIndexCardBy(VALUE_AND, topCard->suit, "V", hand);
    if (i != -1)
    {
        CARD *choice = createCard(hand->cards[i]->value);
        removeFromHand(hand, hand->cards[i]);
        return choice;
    }
    // Find any Coringa
    i = getIndexCardBy(NUMBER, "", "C", hand);
    if (i != -1)
    {
        CARD *choice = createCard(hand->cards[i]->value);
        removeFromHand(hand, hand->cards[i]);
        return choice;
    }
    // Find any Rei

    i = getIndexCardBy(VALUE_AND, topCard->suit, "R", hand);
    if (i != -1)
    {
        CARD *choice = createCard(hand->cards[i]->value);
        removeFromHand(hand, hand->cards[i]);
        return choice;
    }
    // Find any
    i = getIndexCardBy(VALUE_OR, topCard->suit, topCard->number, hand);
    if (i != -1)
    {
        CARD *choice = createCard(hand->cards[i]->value);
        removeFromHand(hand, hand->cards[i]);
        return choice;
    }
    // Find any ÁS
    i = getIndexCardBy(NUMBER, "", "A", hand);
    if (i != -1)
    {
        CARD *choice = createCard(hand->cards[i]->value);
        removeFromHand(hand, hand->cards[i]);
        return choice;
    }
    return NULL;
}

int getIndexCardBy(FIELD f, char *stringSuit, char *stringNumber, HAND *hand)
{
    for (int i = 0; i < hand->amountCards; i++)
    {
        switch (f)
        {
        case VALUE_OR:
            if (strcmp(hand->cards[i]->number, stringNumber) == 0 || strcmp(hand->cards[i]->suit, stringSuit) == 0)
            {
                return i;
            }
            break;
        case VALUE_AND:
            if (strcmp(hand->cards[i]->number, stringNumber) == 0 && strcmp(hand->cards[i]->suit, stringSuit) == 0)
            {
                return i;
            }
            break;
        case NUMBER:
            if (strcmp(hand->cards[i]->number, stringNumber) == 0)
            {
                return i;
            }
            break;
        case SUIT:
            if (strcmp(hand->cards[i]->suit, stringSuit) == 0)
            {
                return i;
            }
            break;
        default:
            break;
        }
    }

    return -1;
}

void actionAnotherPlayer(char *action, CARD *topTable, char *complement)
{
    if (strcmp(action, "BUY") == 0 && (strcmp(topTable->number, "V") == 0 || strcmp(topTable->number, "C") == 0))
    {
        strcpy(topTable->number, "X");
        return;
    }

    if (strcmp(action, "DISCARD") == 0)
    {
        CARD *new = createCard(complement);
        if (!cardIsEqualsSuit(new, topTable) && !cardIsEqualsNumber(new, topTable) && !strcmp(new->number, "C") && !strcmp(new->number, "A"))
        {
            return;
        }

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
    if ((rand() % 100) < 50)
    {
        printf("SAY %s\n", PHRASES[rand() % 9]);
    }

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

    CARD *choice = chooseBestCard(topTable, hand);

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
        if (hand->amountCards == 0)
        {
            printf("SAY UNOOO!!!\n");
        }
        if (strcmp(choice->number, "C") == 0 || strcmp(choice->number, "A") == 0)
        {
            char *bestSuit = chooseBestSuit(hand);
            strcpy(topTable->suit, bestSuit);
            printf("DISCARD %s%s %s\n", choice->number, choice->suit, bestSuit);
        }
        else
        {
            printf("DISCARD %s%s\n", choice->number, choice->suit);
        }
    }
}