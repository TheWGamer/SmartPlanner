#ifndef LOAD
#define LOAD

#include <string.h>

#include "..//headers/smartplanner.h"

#include "login.c"
#include "files.c"
#include "arrays.c"
#include "menu.c"

void parser(char *file, dynArray *array) {    
    FILE *fp = fopen(file, "r");
    if (!fp)
        return;

    int lines = getLines(fp) / 3;
    if (!lines)
        return;
    fseek(fp, 0, SEEK_SET);

    account myAcc;

    // FINALLY F**KING WORKS!
    for (int i = 0; i < lines; i++) {
        fgets(myAcc.name, 64, fp); // Read name from file
        myAcc.name[strlen(myAcc.name) - 1] = '\0'; // Gets rid of newline
        fscanf(fp, "%f\n", &myAcc.balance); // Read balance from file
        fscanf(fp, "%f\n", &myAcc.interest); // Read interest from file

        appendArray(array, myAcc);
    }

    fclose(fp);
    return;
}

void parseMisc(char *file) { // Parses misc file containing info like income and assets
    FILE *fp = fopen(file, "r");
    if (!fp)
        return;
    
    fscanf(fp, "%f\n", &income);
    fscanf(fp, "%f\n", &assets);

    fclose(fp);
    return;
}

void load() { // Loads data from user specific files into memory
    char *sessionUsername = getSessionUsername();

    // Defining file paths
    char path[4][LOGINSIZE + 24] = {"data//savings", "data//debts", "data//investments", "data//misc"};
    for (int i = 0; i < 4; i++) {
        strcat(path[i], sessionUsername);
        strcat(path[i], ".txt");
    }

    // Parsing Files and Writing Contents to Memory
    parser(path[0], &savings);
    parser(path[1], &debts);
    parser(path[2], &investments);
    parseMisc(path[3]);
    
    return;
}

#endif