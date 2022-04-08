#ifndef LOGIN
#define LOGIN

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../headers/smartplanner.h"

// KNOWN BUG: SEGMENTATION FAULT ON INCORRECT USERNAME ENTERED

void setSessionUsername(char *uname) { // sets the session username
    strcpy(username, uname);
    int len = strlen(uname);
    username[len - 1] = '\0';

    return;
}

int getlines(FILE *fp) { // get the number of lines in a given file
    unsigned int lines;
    char c;

    while (!feof(fp)) {
        c = fgetc(fp);
        if (c == '\n')
            lines++;
    }

    fseek(fp, 0, SEEK_SET);
    return lines - 1;
}

int new() { // Creates a new account to use the program
    char uname[1024], password[1024];
    FILE *login;

    printf("USERNAME: ");
    fgets(uname, 1024, stdin);
    printf("PASSWORD: ");
    fgets(password, 1024, stdin);

    login = fopen("data/login.txt", "a+");
    if (!login) {
        printf("Unable to save login data!\n");
        return 0; // returns 0 for unsuccessful creation of account
    }

    fprintf(login, "%s%s", uname, password);
    fclose(login);
    setSessionUsername(uname);

    return 1; // returns 1 for successful creation of account
}

int login() { // login to an existing account to use the program
    FILE *fp = fopen("data/login.txt", "r");
    char buffer[1024], fbuffer[1024];

    if (!fp) {
        printf("Unable to find login file.\nCreating new account.\n");
        return new();
    }

    printf("USERNAME: ");
    fgets(buffer, 1024, stdin);

    setSessionUsername(buffer);

    unsigned int lines = getlines(fp);
    for (int i = lines; i > 0; i--) {
        if (!strcmp(buffer, fgets(fbuffer, 1024, fp))) {
            break;
        }

        if (i == 1)
            fseek(fp, 0, SEEK_SET);
    }

    printf("PASSWORD: ");
    fgets(buffer, 1024, stdin);

    if (strcmp(buffer, fgets(fbuffer, 1024, fp))) {
        printf("Invalid Login!\n");
        return 0;
    }
    else
        return 1;
}

#endif