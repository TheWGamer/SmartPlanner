#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init() {
    FILE *savings, *debts, *investments;

    char sfile[1024] = "savings";
    char dfile[1024] = "debts";
    char ifile[1024] = "investments";

    strcat(sfile, username);
    strcat(dfile, username);
    strcat(ifile, username);

     printf("%s\n", sfile);

    return;
}
