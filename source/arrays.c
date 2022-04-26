#ifndef ARRAYS
#define ARRAYS

#include <stdlib.h>

#include "..//headers//smartplanner.h"

// Dynamic Arrays
dynArray savings;
dynArray debts;
dynArray investments;

void initArray(dynArray *array, unsigned int size) { // Initializes a dynamic array to a specified size
    array->size = size;
    array->array = (account *) malloc (array->size * sizeof(account));
}

void init() { // Initializes savings, debts, and investments
    initArray(&savings, 5);
    initArray(&debts, 5);
    initArray(&investments, 5);

    return;
}

void doubleArray(dynArray *array) { // Called automatically, doubles the size of an array when there is not enough room for new elements
    array->size *= 2;
    array->array = (account *) realloc (array->array, array->size * sizeof(account));
}

void appendArray(dynArray *array, account acc) { // Adds an account to the end of a dynArray
    if (array->size <= array->used)
        doubleArray(array);
    
    // Writes contents of input account to first empty array element
    array->array[array->used] = acc;
    array->used++;

    return;
}

#endif