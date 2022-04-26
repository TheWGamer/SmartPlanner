#ifndef SMARTPLANNER
#define SMARTPLANNER

#define LOGINSIZE 1024

typedef struct {
    char name[64];
    float balance;
    float interest;
    int compound;
    float contribution;
} account;

typedef struct {
    account *array;
    int size;
    int used;
} dynArray;

#endif