//
// Created by marco on 11/12/2018.
//

#ifndef ESERCIZIO3_INV_H
#define ESERCIZIO3_INV_H

#include <malloc.h>
#include "stat.h"

typedef struct inv_t *rifInv_t;

typedef struct inv_t {
    char *nome;
    char *tipo;
    stat_t stat;
} inv_t;

typedef char *KeyEq;

rifInv_t creaInv(void);

KeyEq getEqKey(rifInv_t inv);

int EqKeyCompare(KeyEq k1, KeyEq k2);

void printDetails(rifInv_t oggetto);

#endif //ESERCIZIO3_INV_H
