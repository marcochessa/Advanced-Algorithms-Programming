//
// Created by marco on 11/12/2018.
//

#ifndef ESERCIZIO3_PG_H
#define ESERCIZIO3_PG_H

#include <mem.h>
#include "equipArray.h"
#include "stat.h"

typedef struct pg_t *rifPg_t;

typedef struct pg_t{
    char codice[7];
    char nome[50 + 1];
    char classe[50 + 1];
    Equip equip;
    stat_t stat;

}pg_t;

typedef char *key;

rifPg_t creaPg(void);

key getKey(rifPg_t pg);

int keyCompare(key k1, key k2);

void printPgDetails(rifPg_t pg);

#endif //ESERCIZIO3_PG_H
