#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/smartplanner.h"

// Parser or appendArray is borked

int accs(FILE *fp) {
    int i;
    char c;

    while(!feof(fp)) {
        c = fgetc(fp);

        if (c == '\n')
            i++;
    }

    fseek(fp, 0, SEEK_SET);
    return (i / 3) + 1;
}

void load(char filename[1024], array *arr) {
    FILE *fp = fopen(filename, "r");

    // Creates new file if unable to open
    if (!fp) {
        if (!quietmode)
            printf("unable to locate file, creating new file...\n");

        fp = fopen(filename, "w");
        if (!fp)
            printf("FATAL ERROR: Closing Program\n");

        return;
    }

    //Parser
    account myAcc;
    int n = accs(fp);
    for (int i = 0; i < n; i++) {
        fgets(myAcc.name, 64, fp);
        fscanf(fp, "%f", &myAcc.balance);
        fscanf(fp, "%f", &myAcc.interest);

        myAcc.name[strlen(myAcc.name) - 1] = '\0';

        appendArray(arr, myAcc);
    }

    return;
}

void init() {
    char sfile[1024] = "data/savings";
    char dfile[1024] = "data/debts";
    char ifile[1024] = "data/investments";

    if (!quietmode)
        printf("\ninitializing arrays...\n");

    initArray(&savings, 5);
    initArray(&debts, 5);
    initArray(&investments, 5);

    if (!quietmode)
        printf("finished initializing arrays...\n\nsetting files for loading...\n");

    strcat(sfile, username);
    strcat(dfile, username);
    strcat(ifile, username);

    if (!quietmode) {
        printf("\nsize of savings = %d\n", savings.size);
        printf("size of debts = %d\n", debts.size);
        printf("size of investments = %d\n", investments.size);
    }

    if (!quietmode)
        printf("\nfinished setting files for loading\n\nbeginning to load from files...\n");

    load(strcat(sfile, ".txt"), &savings);
    load(strcat(dfile, ".txt"), &debts);
    load(strcat(ifile, ".txt"), &investments);

    if (!quietmode)
        printf("\nfinished loading from files\n");


    return;
}
