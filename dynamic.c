#include <stdlib.h>
#include <stdio.h>

#include "smartplanner.h"

void doubleArray(array *arr) {
    if (!quietmode)
        printf("doubling array...\n");

    arr->size *= 2;
    arr->accs = (account *) realloc (arr->accs, arr->size * sizeof(account));

    if (!quietmode)
        printf("array doubled\n");

    return;
}

void appendArray(array *arr, account newAcc) {
    if (arr->size > arr->used) {
        arr->accs[arr->used] = newAcc;

        arr->used++;
    }
    else {
        doubleArray(arr);
        appendArray(arr, newAcc);
    }

    return;
}

void initArray(array *arr, int size) {
    arr->size = size;
    arr->accs = (account *) malloc (size * sizeof(account));

    return;
}
