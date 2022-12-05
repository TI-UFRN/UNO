#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./definitions/constants.h"

#include "./helpers/handHelper.h"
#include "./helpers/printHelper.h"
#include "./helpers/creationHelper.h"
#include "./helpers/logicHelper.h"

int main()
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    char *myself = calloc(MAX_ID_SIZE, sizeof(char));
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
            actionAnotherPlayer(action, topTable, complement);
            char string[50] = {"Top table: "};
            strcat(string, topTable->number);
            strcat(string, topTable->suit);
            debug(string);
        } while (strcmp(action, "TURN") || strcmp(complement, myself));
        myAction(topTable, hand);
    }

    return 0;
}