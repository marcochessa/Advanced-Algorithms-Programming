//
// Created by marco on 11/12/2018.
//

#ifndef ESERCIZIO3_EQUIPARRAY_H
#define ESERCIZIO3_EQUIPARRAY_H

#include "inv.h"

typedef struct equip_t *Equip;

void creaEquip(Equip *equip);

void setInUsoEquip(Equip equip, int val);

int getInUsoEquip(Equip equip);

void addItemEquip(Equip equip, rifInv_t inv);

int scalaEquip(Equip equip, char *nomeAccessorio);

int validoEquip(stat_t stat, stat_t statInv);

rifInv_t getEqItem(Equip equip, int ind);

#endif //ESERCIZIO3_EQUIPARRAY_H
