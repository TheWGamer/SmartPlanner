#include <string.h>
#include <stdio.h>

char *removeChar(char *iString) {
    char oString[1024];
    strcpy(oString, iString);
    int len = strlen(iString);
    oString[len - 1] = '\0';

    return oString;
}
