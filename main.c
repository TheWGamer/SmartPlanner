// Standard Headers
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Custom Headers
#include "headers//smartplanner.h"

// Custom Source Files
#include "source//login.c"
#include "source//menu.c"
#include "source//load.c"
#include "source//arrays.c"
#include "source//save.c"

void setMisc() {
    printf("INCOME: $");
    scanf("%lf", &income); getc(stdin);
    printf("ASSETS: $");
    scanf("%lf", &assets); getc(stdin);

    return;
}

int main() {
    int choice;
    bool logged = false;

    // Login
    while (!logged) {
        printf("1. Log In\n2. Create new Account\n");
        printf("Choice: ");
        scanf("%d", &choice); getc(stdin);

        switch (choice) {
            case 1:
                logged = login();
                break;
            case 2:
                logged = createAccount();
                break;
            default:
                printf("Invalid input, please try again.\n");
        }
    }

    // Initialization and Loading
    init();
    load();

    // Main Loop
    printf("\nWelcome to SmartPlanner, %s!\n", getSessionUsername());
    
    while (1) {
        displayElements();

        scanf("%d", &choice); getc(stdin);
        if (choice == 1)
            setMisc();
        else if (choice == 2)
            accountMenu(&savings, "SAVINGS");
        else if (choice == 3)
            accountMenu(&debts, "DEBTS");
        else if (choice == 4)
            accountMenu(&investments, "INVESTMENTS");
        else if (choice == 5)
            projectPortfolio();
        else if (choice == 6) {
            if (!save())
                printf("\nUnable to save data!\n");
            else
                printf("\nData saved successfully!\n");
        }
        else if (choice == 7)
            break;
        else
            printf("Invalid selection! Please try again.\n");
    }

    return 0;
}
