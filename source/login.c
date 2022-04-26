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

int createAccount() {
    return 1;
}

#endif