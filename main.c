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


// UNRESOLVED ISSUE WITH THE PARSER.  I think it has something to do with memory being allocated incorrectly in dynamic.c


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

// Unidentified behavior with investmentsTotal
void portfolio() { // Lists portfolio information
    float savingsTotal, debtsTotal, investmentsTotal;

    for (int i = 0; i < savings.used; i++)
        printf("Savings[%d] = %.2f\n", i, savings.accs[i].balance);
    for (int i = 0; i < debts.used; i++)
        printf("Debts[%d] = %.2f\n", i, debtsTotal += debts.accs[i].balance);
    for (int i = 0; i < investments.used; i++)
        printf("Investments[%d] = %.2f\n", i, investmentsTotal += investments.accs[i].balance);

    printf("PORTFOLIO:\n");
    printf("    ASSETS: $%.2f\n", 0.00); // add assets later
    printf("    SAVINGS: $%.2f\n", savingsTotal);
    printf("    DEBTS: $%.2f\n", debtsTotal);
    printf("    INVESTMENTS: $%.2f\n", investmentsTotal);
    printf("NET WORTH: $%.2f\n", savingsTotal + investmentsTotal - debtsTotal);

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


    printf("\nWelcome to SmartPlanner, %s!\n\n", username);

    // Main Menu
    while (1) {
        portfolio();
        return 0;
    }

    printf("\n");
    return 0;
}
