//
// Created by marco on 11/12/2018.
//


#include "stat.h"

stat_t leggiStat(FILE *fp) {
    stat_t tmp;
    fscanf(fp, "%d %d %d %d %d %d", &tmp.hp, &tmp.mp, &tmp.atk, &tmp.def, &tmp.mag, &tmp.spr);
    return tmp;
}

void printStat(stat_t stat){
    printf("Statistiche:\n");
    printf("\thp: %d\n", stat.hp);
    printf("\tmp: %d\n", stat.mp);
    printf("\tatk: %d\n", stat.atk);
    printf("\tdef: %d\n", stat.def);
    printf("\tmag: %d\n", stat.mag);
    printf("\tspr: %d\n", stat.spr);
}