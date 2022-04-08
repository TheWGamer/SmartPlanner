#ifndef DYNAMIC
#define DYNAMIC

#include <stdlib.h>
#include <stdio.h>

#include "../headers/smartplanner.h"

void cleanup(array *arr) { // Cleans up a dynamic array by unallocated unused space
    if (!quietmode)
	printf("\ncleaning up an array...\n");

    arr->size = arr->used;
    arr->accs = (account *) realloc (arr->accs, arr->size * sizeof(account));

    if (!quietmode)
	printf("\ncleaned up the array.\n");

    return;
}

// Doubles the size of the given dynamic array, called automatically
void doubleArray(array *arr) {
    if (!quietmode)
        printf("\ndoubling array...\n");

    arr->size *= 2;
    arr->accs = (account *) realloc (arr->accs, arr->size * sizeof(account));

    if (!quietmode)
        printf("array doubled\n");

    return;
}

void appendArray(array *arr, account newAcc) { // Call to add a new account to a given dynamic array
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

void initArray(array *arr, int size) { // Call to initialize a dynamic array after defining one
    if (size < 2)
        size = 2;

    arr->size = size;
    arr->accs = (account *) malloc (size * sizeof(account));

    return;
}

#endif