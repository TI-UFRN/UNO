#include <string.h>

#include "../definitions/card.h"
#include "../definitions/hand.h"

int cardIsEquals(CARD *c1, CARD *c2) {
    return strcmp(c1->value, c2->value) == 0 ? 1 : 0;
}