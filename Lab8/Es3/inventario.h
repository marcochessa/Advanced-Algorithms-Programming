//
// Created by marco on 11/12/2018.
//

#ifndef ESERCIZIO3_INVENTARIO_H
#define ESERCIZIO3_INVENTARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <mem.h>

typedef struct stat_t {
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
} stat_t;

typedef struct inv_t {
    char *nome;
    char *tipo;
    stat_t stat;
} inv_t;

typedef struct tabInv_t {
    inv_t *vettInv;
    int nInv;
} tabInv_t;


stat_t leggiStat(FILE *fp);

void caricaInventario(tabInv_t *tabInv);

void liberaInventario(tabInv_t *tabInv);

int cercaAccessiorio(char *nomeAccessorio, tabInv_t tabInv);

void stampaDettagliOggetto(char *nomeAccessorio, tabInv_t tabInv);

void printDetails(inv_t oggetto);

void printStat(stat_t stat);

#endif //ESERCIZIO3_INVENTARIO_H
