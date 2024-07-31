//
// Created by marco on 09/01/2019.
//

#ifndef ESERCIZIO1_TITOLI_H
#define ESERCIZIO1_TITOLI_H

#include "quotazioni.h"
#include <stdio.h>

typedef struct title_t *title;
typedef struct titleList_t *titList;

typedef char *KeyTitle;

titList listInit();

title searchTitle(titList tL, KeyTitle k);

void loadTitle(FILE *in, titList tList);

void insertTitle(titList tL, title t);

void quotBalance(title t, int soglia);

quota getDateQuotation(title t, char *date);

void getBetweenDateQuotation(title t, char *date1, char *date2);

void getMaxMinQuotation(title t);

KeyTitle titleGetKey(title t);

void tFree(titList tL);

#endif //ESERCIZIO1_TITOLI_H
