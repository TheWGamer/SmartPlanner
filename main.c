#include <stdio.h>
#include "headers/smartplanner.h"

char username[1024];

array savings;
array debts;
array investments;

#include "source/login.c"
#include "source/dynamic.c"
#include "source/init.c"

int main() {
    int input;

    printf("\nWould you like to login to an existing account or create a new one?\n");
    printf("1. Log in\n2. Create New\n");
        printf("Selection: ");
        scanf("%d", &input); getc(stdin);
        if (input == 1) {
            if (!login()) {
                printf("Closing Program...\n");
                exit(1);
            }
        }
        else
            new();

    if (!quietmode)
        printf("running init system...\n");
    init();

    printf("Welcome to SmartPlanner, %s!\n", username);

    return 0;
}
