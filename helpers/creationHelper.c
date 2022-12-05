#include <stdlib.h>
#include <string.h>

#include "../definitions/card.h"
#include "../definitions/hand.h"

#include "./handHelper.h"
#include "./printHelper.h"

CARD *createCard(char *cardString)
{
    CARD *c = calloc(1, sizeof(CARD));
    c->value = calloc(10, sizeof(char));
    strcpy(c->value, cardString);

    int initSub = 0;
    if (c->value[0] == '1')
    {
        c->number = calloc(strlen(c->value), sizeof(char));
        strncpy(c->number, c->value, 2);
        initSub = 2;
    }
    else
    {
        c->number = calloc(strlen(c->value), sizeof(char));
        strncpy(c->number, c->value, 1);
        initSub = 1;
    }

    c->suit = calloc(strlen(c->value), sizeof(char));
    strncpy(c->suit, c->value + initSub, strlen(c->value));

    return c;
}

HAND *createHand(char *handString)
{
    HAND *h = calloc(1, sizeof(HAND));
    h->cards = calloc(0, sizeof(CARD *));
    h->amountCards = 0;

    char delim[] = " ";
    char *split = strtok(handString, delim);

    while (split != NULL)
    {
        if (split[0] != '[' && split[0] != ']')
        {
            CARD *c = createCard(split);
            addToHand(h, c);
        }
        split = strtok(NULL, delim);
    }

    return h;
}