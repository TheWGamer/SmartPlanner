/*
This file contains functions for manipulating the contents of the savings, debts, and investments dynamic arrays in memory
*/

#ifndef ACCOUNTS
#define ACCOUNTS

#include <stdio.h>
#include <string.h>

#include "..//headers//smartplanner.h"

#include "arrays.c"

double getTotalBalance(dynArray *array) {
    double total = 0;

    for (int i = 0; i < array->used; i++)
        total += array->array[i].balance;
    
    return total;
}

void addAccount(dynArray *array) { // Adds a new account in memory
    account myAccount;

    printf("New Account:\n");
    printf("    NAME: "); fgets(myAccount.name, 64, stdin);
    printf("    BALANCE: $"); scanf("%lf", &myAccount.balance); getc(stdin);
    printf("    INTEREST RATE: "); scanf("%lf", &myAccount.interest); getc(stdin);
    printf("    COMPOUNDING FREQUENCY: "); scanf("%d", &myAccount.compound); getc(stdin);
    printf("    CONTRIBUTION PER PERIOD (+ or -): "); scanf("%lf", &myAccount.contribution); getc(stdin);

    // Adjustments before committing to array
    myAccount.name[strlen(myAccount.name) - 1] = '\0';
    myAccount.interest /= 100;

    appendArray(array, myAccount);

    return;
}

void listAccounts(dynArray *array) { // Lists all of the accounts in an array
    for (int i = 0; i < array->used; i++) {
        printf("Account #%d - %s:\n", i + 1, array->array[i].name);
        printf("    Balance: $%.2lf\n", array->array[i].balance);
        printf("    Interest Rate: %.2lf%%\n", array->array[i].interest * 100);
        printf("    Compounding Frequency: %d time(s) annually\n", array->array[i].compound);
        printf("    Contribution per Period: $%.2lf\n", array->array[i].contribution);
    }

    return;
}

int selectAccount(dynArray *array) { // Prompts the user to select an account from given array | returns index of the account
    int index;
    
    do {
        printf("\n");
        listAccounts(array);
        printf("Which Account would you like to modify?\n");
        printf("Choice: ");

        scanf("%d", &index); getc(stdin);

        if (index < 0 || index > array->used)
            printf("Invalid Account Number, please try again!\n");
    }while (index <= 0 || index > array->used);
    index--;

    return index;
}

void editAccount(dynArray *array) { // Edits an existing account's information
    int index, choice;

    index = selectAccount(array);
    
    while (1) {
        printf("Which part of the account would you like to modify?\n");
        printf("1. Name\n");
        printf("2. Balance\n");
        printf("3. Interest Rate\n");
        printf("4. Compounding Frequency\n");
        printf("5. Contribution per Period\n");
        printf("6. Cancel\n");
        printf("Choice: ");

        scanf("%d", &choice); getc(stdin);

        if (choice == 1) {
            printf("NEW NAME: ");
            fgets(array->array[index].name, 64, stdin);
            array->array[index].name[strlen(array->array[index].name) - 1] = '\0';
            return;
        }
        else if (choice == 2) {
            printf("NEW BALANCE: $");
            scanf("%lf", &array->array[index].balance); getc(stdin);
            return;
        }
        else if (choice == 3) {
            printf("NEW INTEREST RATE: ");
            scanf("%lf", &array->array[index].interest); getc(stdin);
            array->array[index].interest /= 100;
            return;
        }
        else if (choice == 4) {
            printf("NEW COMPOUNDING FREQUENCY: ");
            scanf("%d", &array->array[index].compound); getc(stdin);
            return;
        }
        else if (choice == 5) {
            printf("NEW CONTRIBUTION PER PERIOD: $");
            scanf("%lf", &array->array[index].contribution); getc(stdin);
            return;
        }
        else if (choice == 6)
            return;
        else
            printf("Invalid Selection, please try again!\n");
    }
}

void removeAccount(dynArray *array) { // Removes an account from memory
    int index; char choice;
    index = selectAccount(array);

    printf("Are you sure? (y/N): ");
    scanf("%c", &choice); getc(stdin);

    if (choice == 'y') {
        // Writes data from next array entry into previous starting at index of account to be removed
        for (int i = index; i < array->used - 1; i++) {
            array->array[i] = array->array[i + 1];
        }

        array->used--;
    }

    return;
}

#endif