#ifndef FILES
#define FILES

#include <stdio.h>

int getLines(FILE *fp) {
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

#endif