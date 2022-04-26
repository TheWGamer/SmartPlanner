/*
This file contains functions for projecting both an account type and an entire portfolio into the future
*/

#ifndef PROJECT
#define PROJECT

#include <stdio.h>
#include <stdlib.h>

#include "..//headers//smartplanner.h"

#include "accounts.c"

float setYears() { // Sets the number of years to be projected into
    float years;
    
    printf("How far into the future would you like to project?\n");
    printf("Year(s): ");

    scanf("%f", &years); getc(stdin);
    if (years <= 0) {
        printf("Invalid selection!\n");
        return 0;
    }

    return years;
}

float futureBalance(account acc, float years) { // Returns the projected balance on an account in the specified number of years
    float total = acc.balance;

    // Iterates over each period for an account in the specified time applying the compounding interest formula
    for (int i = 0; i < (int) years * acc.compound; i++) {
        total += acc.contribution;
        total *=  (1 + (acc.interest / acc.compound));
    }

    return total;
}

float project(dynArray *array, float years, char *type) { // Projects the value of all accounts in a given category after a certain number of years
    printf("\n%s:\n", type);
    
    if (array->used < 1) {
        printf("No Accounts of this Type!\n");
        return 0;
    }

    float *projections = (float *) malloc (array->used * sizeof(float)), total = 0, totalPayment = 0;

    printf("Projected value of account(s) in %.1f years:\n", years);
    for (int i = 0; i < array->used; i++) {
        projections[i] = futureBalance(array->array[i], years);
        total += projections[i];
        
        printf("Account #%d - %s:\n", i + 1, array->array[i].name);
        printf("    Balance: $%.2f\n", projections[i]);
        printf("    Interest Rate: %.2f%%\n", array->array[i].interest * 100);
        printf("    Compounding Frequency: %d time(s) annually\n", array->array[i].compound);
        printf("    Monthly Contribution $%.2f\n", array->array[i].contribution);

        totalPayment += (float) (array->array[i].contribution * ((int) array->array[i].compound * years));
    }
    free(projections);

    float temp = getTotalBalance(array);    
    printf("\nCombined Balance on All Accounts after %.1f year(s): $%.2f\n", years, total);
    printf("Current Combined Balance on All Accounts: $%.2f\n", temp);
    printf("    Change due to Interest: $%.2f\n", total - totalPayment - temp);

    return total;
}

void projectPortfolio() {
    float years = setYears();
    float sTotal = project(&savings, years, "SAVINGS"), dTotal = project(&debts, years, "DEBTS"), iTotal = project(&investments, years, "INVESTMENTS");

    float projectedPortfolio = sTotal + iTotal - dTotal + assets, temp = getTotalBalance(&savings) + getTotalBalance(&investments) + assets - getTotalBalance(&debts);
    printf("\nProjected Net Worth in %.1f year(s): $%.2f\n", years, projectedPortfolio);
    printf("Current Net Worth: $%.2f\n", temp);
    printf("    Estimated Total Change: $%.2f\n", projectedPortfolio - temp);

    return;
}

#endif