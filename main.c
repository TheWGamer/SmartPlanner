#include <stdio.h>
#include "smartplanner.h"

#include "login.c"
#include "init.c"

int main() {
    int input;

    printf("Would you like to login to an existing account or create a new one?\n");
    printf("1. Log in\n2. Create New\n");
        printf("Selection: ");
        scanf("%d", &input); getc(stdin);
        if (input == 1)
            login();
        else
            new();

    printf("Running init system...\n");
    printf("Welcome to SmartPlanner, %s!\n", username);

    return 0;
}
