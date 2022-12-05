#include <stdlib.h>
#include <string.h>

#include "../definitions/card.h"
#include "../definitions/hand.h"

int indexOf(HAND *, CARD *);

void addToHand(HAND *hand, CARD *card)
{
    hand->cards = realloc(hand->cards, (hand->amountCards + 1) * sizeof(CARD));
    hand->cards[hand->amountCards] = card;
    hand->amountCards = hand->amountCards + 1;
}

void removeFromHand(HAND *hand, CARD *card)
{
    int index = indexOf(hand, card);
    if (index == -1)
        return;

    if (index == 0 && hand->amountCards == 1)
    {
        hand->amountCards = 0;
        free(hand->cards[0]);
        hand->cards = calloc(0, sizeof(CARD *));
        return;
    }

    for (int i = index; i < hand->amountCards - 1; i++)
    {
        CARD *aux = hand->cards[i];
        *(hand->cards[i]) = *(hand->cards[i + 1]);
        *(hand->cards[i + 1]) = *aux;
    }

    free(hand->cards[hand->amountCards - 1]);
    hand->cards = realloc(hand->cards, (hand->amountCards - 1) * sizeof(CARD));
    hand->amountCards = hand->amountCards - 1;
}

int indexOf(HAND *hand, CARD *card)
{
    for (int i = 0; i < hand->amountCards; i++)
    {
        if (strcmp(hand->cards[i]->number, card->number) == 0 && strcmp(hand->cards[i]->suit, card->suit) == 0)
        {
            return i;
        }
    }
    return -1;
}