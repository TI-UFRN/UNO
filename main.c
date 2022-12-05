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
            debug(myself);
            scanf("%s %s", action, complement);
            if (strcmp(action, "DISCARD") == 0)
            {
                topTable = createCard(complement);
                if (strcmp(topTable->number, "C") == 0 || strcmp(topTable->number, "A") == 0)
                {
                    char complement2[MAX_LINE];
                    scanf(" %s", complement2);
                    topTable->suit = complement2;
                }
            }
        } while (strcmp(action, "TURN") || strcmp(complement, myself));
        debug("---------MINHA VEZ---------");
        debug(topTable->value);
        if(strcmp(topTable->number, "V") == 0 || strcmp(topTable->number, "C") == 0) {

            int quantBuy = strcmp(topTable->number, "V") == 0 ? 2 : 4;

            char cardString1[MAX_LINE];
            char cardString2[MAX_LINE];
            
            printf("BUY %d\n", quantBuy);
            scanf("%s %s\n", cardString1, cardString2);

            CARD *more1 = createCard(cardString1);
            CARD *more2 = createCard(cardString2);

            addToHand(hand, more1);
            addToHand(hand, more2);

            if(quantBuy == 4) {
                char cardString3[MAX_LINE];
                char cardString4[MAX_LINE];
                scanf(" %s %s\n", cardString3, cardString4);
                
                CARD *more3 = createCard(cardString3);
                CARD *more4 = createCard(cardString4);

                addToHand(hand, more3);
                addToHand(hand, more4);
            }
            continue;
        }
        
        //chooseBestCard(topTable, hand);
        CARD *choice = NULL;

        if(choice == NULL) {
            printf("BUY 1\n");    
        } else {
            printf("DISCARD %s\n", choice->value);
        }
    }

    return 0;
}