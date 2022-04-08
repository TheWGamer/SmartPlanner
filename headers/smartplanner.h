#ifndef SMARTPLANNER
#define SMARTPLANNER

typedef struct {
    char name[64];
    float balance;
    float interest;
} account;

typedef struct {
    account *accs;
    int size;
    int used;
} array;

#endif
