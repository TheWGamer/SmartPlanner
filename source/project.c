/*
This file contains functions for projecting both an account type and an entire portfolio into the future
Partial years still need to be taken into account, haven't thought of an elegant solution yet...
*/

#ifndef PROJECT
#define PROJECT

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "..//headers//smartplanner.h"

#include "accounts.c"

double setYears() { // Sets the number of years to be projected into
    double years;
    
    printf("How far into the future would you like to project?\n");
    printf("Year(s): ");

    scanf("%lf", &years); getc(stdin);
    if (years <= 0) {
        printf("Invalid selection!\n");
        return 0;
    }

    return years;
}

double project(dynArray *array, double years, char *type) { // Projects the value of all accounts in a given category after a certain number of years
    printf("\n%s:\n", type);
    
    // Are there accounts of this type?
    if (array->used < 1) {
        printf("No Accounts of this Type!\n");
        return 0;
    }

    double *projection = (double *) malloc (array->used * sizeof(double)); // projected balances
    double delta = 0, totalDelta = 0, totalProjection = 0;

    

    for (int i = 0; i < array->used; i++) { // Iterates over each account
        double accDelta = 0;
        projection[i] = array->array[i].balance;

        for (int n = 1; n < floor(array->array[i].compound * years); n++) { // Calculates data for individual accounts
            projection[i] += array->array[i].contribution;
            if (projection[i] < 0) { // Partial Years with Debts
                projection[i] -= array->array[i].contribution;

                delta = projection[i] * (array->array[i].interest / array->array[i].compound);
                accDelta += delta;

                projection[i] = 0;
            }

            delta = projection[i] * (array->array[i].interest / array->array[i].compound); // Change due to interest each period
            accDelta += delta; // Total change due to interest for account for specified time in years

            projection[i] += delta;
        }

        // Partial Years
        projection[i] += array->array[i].contribution * (years - floor(years));
        if (projection[i] < 0)
            projection[i] = 0;
        delta = projection[i] * (array->array[i].interest / array->array[i].compound);
        accDelta += delta;
        projection[i] += delta;


        printf("Account #%d -- %s\n", i + 1, array->array[i].name);
        printf("    CURRENT BALANCE: $%.2lf\n", array->array[i].balance);
        printf("    PROJECTED BALANCE: $%.2lf\n", projection[i]);
        printf("Change due to interest: $%.2lf\n", accDelta);

        totalDelta += accDelta; // total change due to interest for all accounts for specified time in years
        totalProjection += projection[i]; // total projected balance at specified time in years
    }

    free(projection);

    double currentTotal = getTotalBalance(array);
    printf("\nTOTAL:\n");
    printf("    Current Combined Balance on All '%s' Accounts: $%.2lf\n", type, currentTotal);
    printf("    Combined Balance on All '%s' Accounts after %.1lf years: $%.2lf\n", type, years, totalProjection);
    printf("Net Change due to Interest: $%.2lf\n", totalDelta);
    printf("Net Balance Change: $%.2lf\n", totalProjection - currentTotal);

    return totalProjection;
}

void projectPortfolio() {
    double years = setYears();
    double sTotal = project(&savings, years, "SAVINGS"), dTotal = project(&debts, years, "DEBTS"), iTotal = project(&investments, years, "INVESTMENTS");

    double projectedPortfolio = sTotal + iTotal - dTotal + assets, currentPortfolio = getTotalBalance(&savings) + getTotalBalance(&investments) + assets - getTotalBalance(&debts);
    printf("\n\nProjected Net Worth in %.1lf year(s): $%.2lf\n", years, projectedPortfolio);
    printf("Current Net Worth: $%.2lf\n", currentPortfolio);
    printf("    Estimated Total Change: $%.2lf\n", projectedPortfolio - currentPortfolio);

    return;
}

#endif