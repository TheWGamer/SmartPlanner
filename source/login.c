/*
This file provides login and account creation functionality
login() and createAccount() both return 1 when successful, and 0 when unsuccessful
call getSessionUsername() whenever you need to reference the current user in other parts of the program
*/

#ifndef LOGIN
#define LOGIN

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "..//headers//smartplanner.h"

#include "files.c"

char sessionUsername[LOGINSIZE];

char *getSessionUsername() { // Returns the username for the current session
    return sessionUsername;
}

void setSessionUsername(char *username) { // Sets the username for the current session
    int n = strlen(username) - 1;
    for (int i = 0; i < n; i++)
        sessionUsername[i] = username[i];
    
    // Unneccessary, but it makes things a little nicer
    if (!strcmp(username, "\n")) {
        char temp[8] = "testuser";
        for (int i = 0; i < 8; i++)
            sessionUsername[i] = temp[i];
    }

    return;
}

int login() {
    FILE *fp = fopen("data//logins.txt", "r");
    if (!fp) {
        printf("Unable to locate logins file.  Have you created an account already?\n");
        return 0;
    }

    // Get username and password from user input
    char username[LOGINSIZE], password[LOGINSIZE];
    printf("USERNAME: "); fgets(username, LOGINSIZE, stdin);
    printf("PASSWORD: "); fgets(password, LOGINSIZE, stdin);

    // Test for matching username
    bool usernameMatch = false;
    char compUsername[LOGINSIZE], compPassword[LOGINSIZE];
    while (!feof(fp)) {
        fgets(compUsername, LOGINSIZE, fp);

        if (!strcmp(username, compUsername)) { // If username match is found
            usernameMatch = true;
            break;
        }
    }
    if (!usernameMatch) { // If no username match is found after iterating over login file
        printf("Invalid login!\n");
        fclose(fp);
        return 0;
    }

    setSessionUsername(username);

    // Tests next line of login file for matching password
    fgets(compPassword, LOGINSIZE, fp);
    if (strcmp(password, compPassword)) {
        printf("Invalid login!\n");
        fclose(fp);
        return 0;
    }

    fclose(fp);
    return 1;
}

int usernameAvailable(char *username) {
    bool isAvailable = true;

    FILE *fp = fopen("data//logins.txt", "r");
    if (!fp)
        return 1;
    
    char buffer[LOGINSIZE];
    while (!feof(fp)) {
        fgets(buffer, LOGINSIZE, fp);

        if (!strcmp(buffer, username))
            isAvailable = false;
    }

    if (!isAvailable)
        printf("Invalid Username, please try another one!\n");

    fclose(fp);
    return isAvailable;
}

int createAccount() {
    char username[LOGINSIZE], password[LOGINSIZE], echo[LOGINSIZE];

    do {
        printf("USERNAME: "); fgets(username, LOGINSIZE, stdin);
    }while (!usernameAvailable(username));

    printf("PASSWORD: "); fgets(password, LOGINSIZE, stdin);
    printf("CONFIRM PASSWORD: "); fgets(echo, LOGINSIZE, stdin);

    mkfs();

    if (!strcmp(password, echo)) {
        FILE *fp = fopen("data//logins.txt", "a+");
        if (!fp)
            return 0;

        setSessionUsername(username);

        username[strlen(username) - 1] = '\0';
        password[strlen(password) - 1] = '\0';

        fprintf(fp, "%s\n", username);
        fprintf(fp, "%s\n", password);

        fclose(fp);
        return 1;
    }

    return 0;
}

#endif