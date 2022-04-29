/*
This file provides all of the menu and UI for the program
Call displayElements to show the main menu
Call accountMenu() to modify a type of account
*/

#ifndef MENU
#define MENU

#include <stdio.h>
#include <string.h>

#include "arrays.c"
#include "accounts.c"
#include "project.c"

double income;
double assets;

void displayElements() { // basic display for the main menu
    double s, d, i;
    s = getTotalBalance(&savings);
    d = getTotalBalance(&debts);
    i = getTotalBalance(&investments);

    printf("\nPORTFOLIO:\n");
    printf("    SAVINGS: $%.2f in %d account(s)\n", s, savings.used);
    printf("    DEBTS: $%.2f in %d account(s)\n", d, debts.used);
    printf("    INVESTMENTS: $%.2f in %d account(s)\n", i, investments.used);
    printf("NET WORTH: $%.2f\n", s + i + assets - d); // Still needs assets added
    printf("    VALUE OF ASSETS: $%.2f\n", assets);

    printf("\nMENU:\n");
    printf("1. Set Income and Assets\n");
    printf("2. Savings\n");
    printf("3. Debts\n");
    printf("4. Investments\n");
    printf("5. Project\n");
    printf("6. Save\n"); // Remember to add #@# to EOF
    printf("7. Exit\n");
    printf("Choice: ");

    return;
}

void accountMenu(dynArray *array, char *type) { // Main menu for savings accounts
    int choice;

    while (1) {
        printf("\n%s MENU:\n", type);
        printf("1. List Accounts\n");
        printf("2. Add New Account\n");
        printf("3. Edit Existing Account\n");
        printf("4. Remove Account\n");
        printf("5. Project\n");
        printf("6. Return to Main Menu\n");

        printf("Choice: ");
        scanf("%d", &choice); getc(stdin);

        if (choice == 1) {
            printf("\n%s ACCOUNTS:\n", type);
            listAccounts(array);
        }
        else if (choice == 2)
            addAccount(array);
        else if (choice == 3)
            editAccount(array);
        else if (choice == 4)
            removeAccount(array);
        else if (choice == 5)
            project(array, setYears(), type);
        else if (choice == 6)
            return;
        else
            printf("Invalid selection, please try again!\n");
    }
}

#endif