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
            accountMenu(&savings, "SAVINGS");
        else if (choice == 2)
            accountMenu(&debts, "DEBTS");
        else if (choice == 3)
            accountMenu(&investments, "INVESTMENTS");
        else if (choice < 4 || choice > 6)
            printf("Invalid Selection! Please try again.\n");
    }

    return 0;
}
