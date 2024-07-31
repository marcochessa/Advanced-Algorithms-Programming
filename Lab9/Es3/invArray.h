//
// Created by marco on 11/12/2018.
//

#ifndef ESERCIZIO3_INVARRAY_H
#define ESERCIZIO3_INVARRAY_H

#include "inv.h"

typedef struct tabInv_t *TabInv;

TabInv creaTabInv();

void caricaInventario(TabInv tabInv);

void liberaInventario(TabInv tabInv);

int cercaAccessiorio(char *nomeAccessorio, TabInv tabInv);

void stampaDettagliOggetto(char *nomeAccessorio, TabInv tabInv);

stat_t getStat( TabInv tabInv, int indice);

rifInv_t getObjectPointer( TabInv tabInv, int indice);

#endif //ESERCIZIO3_INVARRAY_H
