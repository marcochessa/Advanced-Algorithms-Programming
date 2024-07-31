//
// Created by marco on 11/12/2018.
//

#include <stdio.h>

#ifndef ESERCIZIO3_STAT_H
#define ESERCIZIO3_STAT_H
typedef struct stat_t {
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
} stat_t;

void printStat(stat_t stat);

stat_t leggiStat(FILE *fp);

#endif //ESERCIZIO3_STAT_H