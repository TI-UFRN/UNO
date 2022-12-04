#include <stdio.h>
#include <string.h>

#include "./definitions/constants.h"
#include "./helpers/printHelper.h"
#include "./helpers/creationHelper.h"

int main() {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    char myself[MAX_ID_SIZE];
    char players[MAX_LINE];
    char handString[MAX_LINE];
    char initialTopTableString[MAX_LINE];

    scanf("PLAYERS %[^\n]\n", players);
    scanf("YOU %s\n", myself);

    scanf("HAND %[^\n]\n", handString);
    HAND *hand = createHand(handString);

    scanf("TABLE %s\n", initialTopTableString);
    CARD *topTable = createCard(initialTopTableString);

    char action[MAX_ACTION];
    char complement[MAX_LINE];

    while (1)
    {
        do
        {
            scanf("%s %s", action, complement);
            char init[10] = {"ACAO: "};
            strcat(init, action);
            debug(init);
            debug(complement);
        } while (strcmp(action, "TURN") || strcmp(complement, myself));

        char card[] = "A♥ ♥";
        printf("DISCARD %s\n", card);
    }

    return 0;
}