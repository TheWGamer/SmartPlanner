#include <stdio.h>
#include "headers/smartplanner.h"

int quietmode; // edit in config.dat
char username[1024]; // session username

// Dynamic arrays of accounts
array savings;
array debts;
array investments;

#include "source/login.c"
#include "source/dynamic.c"
#include "source/init.c"

// Reads config file for program settings
void config() {
    FILE *config = fopen("config.dat", "r");

    if (config) {
        fscanf(config, "quietmode %d\n", &quietmode);
    }

    if (!quietmode)
        printf("quietmode is off\n");

    return;
}

// main loop
int main() {
    int input;

    config();

    printf("\nWould you like to login to an existing account or create a new one?\n");
    printf("1. Log in\n2. Create New\n");
        printf("Selection: ");
        scanf("%d", &input); getc(stdin);
        if (input == 1) {
            if (!login()) { // Closes program if invalid login
                printf("Closing Program...\n");
                exit(1);
            }
        }
        else // Creates new account if login is not selected
            new();

    if (!quietmode)
        printf("\nrunning init system...\n");
    init(); //Begins the init system
    if (!quietmode)
        printf("init finished\n");


    // Main Menu
    printf("\nWelcome to SmartPlanner, %s!\n", username);

    for (int i = 0; i < accs(fopen("debtsChase.txt", "r")); i++) {
        printf("\nname[%d] = %s\n", i, debts.accs[i].name);
        printf("balance[%d] = $%.2f\n", i, debts.accs[i].balance);
        printf("interest[%d] = %.3f%%\n", i, debts.accs[i].interest * 100);
    }

    printf("\n");
    return 0;
}
