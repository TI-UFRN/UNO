#include <stdio.h>

void debug(char *message)
{
    fprintf(stderr, "%s\n", message);
}