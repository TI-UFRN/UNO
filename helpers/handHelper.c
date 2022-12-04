#include <stdlib.h>
#include "../definitions/card.h"
#include "../definitions/hand.h"

void addToHand(HAND *hand, CARD *card) {
    hand->cards = realloc(hand->cards, (hand->amountCards + 1) * sizeof(CARD));
    hand->cards[hand->amountCards] = card;
    hand->amountCards = hand->amountCards + 1;
}