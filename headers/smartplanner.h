#ifndef SMARTPLANNER
#define SMARTPLANNER

#define LOGINSIZE 1024

typedef struct {
    char name[64];
    double balance;
    double interest;
    int compound;
    double contribution;
} account;

typedef struct {
    account *array;
    int size;
    int used;
} dynArray;

#endif