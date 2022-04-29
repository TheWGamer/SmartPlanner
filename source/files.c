/*
This file contains backend functions for file manipulations
I cannot for the life of me figure out a bug on linux machines that causes counting newlines in a "while(!feof(fp))" loop to cause getLines to return
excessively high numbers
*/

#ifndef FILES
#define FILES

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int getLines(FILE *fp) { // Returns the number of lines in a file that ends with #@#
    char c;
    int lines = 0;
    
    while (!feof(fp)) {
        c = fgetc(fp);

        if (c == '\n')
            lines++;

        // Exit Sequence
        if (c == '#') {
            c = fgetc(fp);

            if (c == '@') {
                c = fgetc(fp);

                if (c == '#')
                    break;
                
                else
                    fseek(fp, -2, SEEK_CUR);
            }

            else {
                fseek(fp, -1, SEEK_CUR);
            }
        }
    }

    return lines;
}

void addEnd(FILE *fp) { // Adds a custom signature to end of file for future reading
    fseek(fp, 0, SEEK_END);
    fprintf(fp, "#@#");
    return;
}

void mkfs() {
    FILE *temp = fopen("data//temp", "w");
    if (!temp)
        mkdir("data", 0777);
    else
        fclose(temp);

    return;
}

#endif