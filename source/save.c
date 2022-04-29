/*
This file handles all saving data from memory onto files on the user's PC
calling save() should do all saving
*/

#ifndef SAVE
#define SAVE

#include "login.c"
#include "arrays.c"

int writeToFile(char *file, dynArray *array) { // Writes the array information for the user in corresponding files
    FILE *fp = fopen(file, "w");
    if (!fp)
        return 0;

    // Writes to file for each account in an array
    for (int i = 0; i < array->used; i++) {
        fprintf(fp, "%s\n", array->array[i].name);
        fprintf(fp, "%lf\n", array->array[i].balance);
        fprintf(fp, "%lf\n", array->array[i].interest);
        fprintf(fp, "%d\n", array->array[i].compound);
        fprintf(fp, "%lf\n", array->array[i].contribution);
    }

    addEnd(fp);
    
    fclose(fp);
    return 1;
}

int writeMisc(char *file) { // Writes to the misc file for the user, contains income and assets data
    FILE *fp = fopen(file, "w");
    if (!fp)
        return 0;
    
    fprintf(fp, "%lf\n", income);
    fprintf(fp, "%lf\n", assets);

    addEnd(fp);

    fclose(fp);
    return 1;
}

int save() { // Call to save program info
    char *sessionUsername = getSessionUsername();

    // Defining file paths
    char path[4][LOGINSIZE + 24] = {"data//savings", "data//debts", "data//investments", "data//misc"};
    for (int i = 0; i < 4; i++) {
        strcat(path[i], sessionUsername);
        strcat(path[i], ".txt");
    }

    // Check to make sure that file system exists
    mkfs();

    // Write to files
    int success = 0;
    success += writeToFile(path[0], &savings);
    success += writeToFile(path[1], &debts);
    success += writeToFile(path[2], &investments);
    success += writeMisc(path[3]);

    if (success == 4)
        return 1;
    else
        return 0;
}

#endif