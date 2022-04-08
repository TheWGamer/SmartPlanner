#include <stdio.h>
#include "headers/smartplanner.h"

int quietmode;
char username[1024];

array savings;
array debts;
array investments;

#include "source/login.c"
#include "source/dynamic.c"
#include "source/init.c"

void config() {
    FILE *config = fopen("config.dat", "r");

    if (config) {
        fscanf(config, "quietmode %d\n", &quietmode);
    }

    if (!quietmode)
        printf("quietmode is off\n");

    return;
}

int main() {
    int input;

    config();

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
        printf("\nrunning init system...\n");
    init();
    if (!quietmode)
        printf("init finished\n");

    printf("\nWelcome to SmartPlanner, %s!\n", username);

    for (int i = 0; i < 5; i++) {
        printf("\nname[%d] = %s\n", i, debts.accs[i].name);
        printf("balance[%d] = $%.2f\n", i, debts.accs[i].balance);
        printf("interest[%d] = %.3f%%\n", i, debts.accs[i].interest * 100);
    }

    printf("\n");
    return 0;
}
