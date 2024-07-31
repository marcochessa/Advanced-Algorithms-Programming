//
// Created by marco on 11/12/2018.
//

#ifndef ESERCIZIO3_PERSONAGGIO_H
#define ESERCIZIO3_PERSONAGGIO_H
#define MAX_EQ 8

#include <malloc.h>
#include "inventario.h"

typedef struct equip_t {
    int inUso;
    //Il vettore sottostante potrebbe essere allocato dinamicamente, per comodità si alloca in maniera statica
    inv_t *vettEq[MAX_EQ];
} equip_t;

typedef struct pg_t {
    char codice[7];
    char nome[50 + 1];
    char classe[50 + 1];
    equip_t equip;
    stat_t stat;

} pg_t;

typedef struct nodoPg_t *link;

typedef struct nodoPg_t {
    pg_t val;
    link next;
} nodoPg_t;

typedef struct tabPg_t {
    link headPg;
    link tailPg;
    int nPg;
} tabPg_t;

void caricaPersonaggi(tabPg_t *tabPg);

void eqPersonaggio(char *codice, tabPg_t *tabPg, tabInv_t *tabInv);

void disEqPersonaggio(char *codice, tabPg_t *tabPg, tabInv_t *tabInv);

int scalaEquip(equip_t *equip, char *nomeAccessorio);

int validoEquip(stat_t stat, stat_t statInv);

link newNode(pg_t val, link next);

void listInsTailFast(tabPg_t *tabPg, pg_t val);

int pgPresente(tabPg_t *tabPg, char *codice);

int listDelKey(tabPg_t *tabPg, char *codice);

stat_t aggiornaStat(stat_t statPG, stat_t statInv, int eqDisEq);

void stampaDettagliPg(char *codice, tabPg_t tabPg);

#endif //ESERCIZIO3_PERSONAGGIO_H
