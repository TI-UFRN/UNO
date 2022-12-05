#include <string.h>

#include "../definitions/card.h"
#include "../definitions/hand.h"

int cardIsEquals(CARD *c1, CARD *c2)
{
    return (strcmp(c1->number, c2->number) == 0 && strcmp(c1->suit, c2->suit) == 0) ? 1 : 0;
}

int cardIsEqualsNumber(CARD *c1, CARD *c2)
{
    return (strcmp(c1->number, c2->number) == 0) ? 1 : 0;
}

int cardIsEqualsSuit(CARD *c1, CARD *c2)
{
    return (strcmp(c1->suit, c2->suit) == 0) ? 1 : 0;
}