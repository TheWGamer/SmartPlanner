#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/smartplanner.h"

void load(char filename[1024], array *arr) {
    FILE *fp = fopen(filename, "r");

    // Creates new file if unable to open
    if (!fp) {
        if (!quietmode)
            printf("unable to locate file, creating new file...\n");

        fp = fopen(filename, "w");
        if (!fp)
            printf("FATAL ERROR: Closing Program\n");
    }

    //Parser
    account myAcc;
    while (!feof(fp)) {
        fgets(myAcc.name, 64, fp);
        fscanf(fp, "%f", &myAcc.balance);
        fscanf(fp, "%f", &myAcc.interest);

        appendArray(arr, myAcc);
    }

    return;
}

void init() {
    char sfile[1024] = "savings";
    char dfile[1024] = "debts";
    char ifile[1024] = "investments";

    if (!quietmode)
        printf("initializing arrays...\n");

    initArray(&savings, 5);
    initArray(&debts, 5);
    initArray(&investments, 5);

    if (!quietmode)
        printf("finished initializing arrays...\nsetting files for loading...\n");

    strcat(sfile, username);
    strcat(dfile, username);
    strcat(ifile, username);

    if (!quietmode)
        printf("finished setting files for loading\nbeginning to load from files...\n");

    load(strcat(sfile, ".txt"), &savings);
    load(strcat(dfile, ".txt"), &debts);
    load(strcat(ifile, ".txt"), &investments);

    if (!quietmode)
        printf("finished loading from files\n");


    return;
}
