#ifndef SAVE
#define SAVE

#include <stdio.h>
#include <stdlib.h>

#include "../headers/smartplanner.h"

void saveArr(FILE *fp, array *arr) { // saves to a given file the contents of an entire dynamic array
    if(!fp) {
        printf("Unable to save data!\n");
        return;
    }

    return;
}

#endif