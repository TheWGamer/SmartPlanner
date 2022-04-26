#ifndef MENU
#define MENU

#include <stdio.h>

#include "arrays.c"

float income;
float assets;

float getTotalBalance(dynArray *array) {
    float total = 0;

    for (int i = 0; i < array->used; i++)
        total += array->array[i].balance;
    
    return total;
}

void displayElements() { // basic display for the main menu
    float s, d, i;
    s = getTotalBalance(&savings);
    d = getTotalBalance(&debts);
    i = getTotalBalance(&investments);

    printf("\nPORTFOLIO:\n");
    printf("    SAVINGS: $%.2f in %d account(s)\n", s, savings.used);
    printf("    DEBTS: $%.2f in %d account(s)\n", d, debts.used);
    printf("    INVESTMENTS: $%.2f in %d account(s)\n", i, investments.used);
    printf("NET WORTH: $%.2f\n", s + i + assets - d); // Still needs assets added

    printf("\nMENU:\n");
    printf("1. Savings\n");
    printf("2. Debts\n");
    printf("3. Investments\n");
    printf("4. Project\n");
    printf("5. Save\n"); // Remember to add #@# to EOF
    printf("6. Exit\n");
    printf("Choice: ");

    return;
}

#endif