//
// Created by marco on 11/12/2018.
//

#ifndef ESERCIZIO3_PGLIST_H
#define ESERCIZIO3_PGLIST_H

#include "pg.h"
#include "invArray.h"

typedef struct nodoPg_t *link;

typedef struct tabPg_t *TabPg;

TabPg creaTabPg();

static void setVoidTab(TabPg tabPg);

void caricaPersonaggi(TabPg tabPg);

link newNode(rifPg_t val, link next);

void listInsTailFast(TabPg tabPg, rifPg_t val);

int pgPresente(TabPg tabPg, char *codice);

int listDelKey(TabPg tabPg, char *codice);

void stampaDettagliPg(char *codice, TabPg tabPg);

stat_t aggiornaStat(stat_t statPG, stat_t statInv, int eqDisEq);

void eqPersonaggio(char *codice, TabPg tabPg, TabInv tabInv);

void disEqPersonaggio(char *codice, TabPg tabPg, TabInv tabInv);

int getNumPg(TabPg tabPg);

void freeTabPg(TabPg tabPg);

#endif //ESERCIZIO3_PGLIST_H
