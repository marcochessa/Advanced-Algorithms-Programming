//
// Created by marco on 11/12/2018.
//

#include <mem.h>
#include <malloc.h>
#include "equipArray.h"

#define MAX_EQ 8

typedef struct equip_t {
    int inUso;
    //Il vettore sottostante potrebbe essere allocato dinamicamente, per comodità si allora in maniera statica
    rifInv_t vettEq[MAX_EQ];
} equip_t;

void creaEquip(Equip *equip) {
    *equip = malloc(sizeof(equip_t));
    setInUsoEquip(*equip, 0);
}

void setInUsoEquip(Equip equip, int val) {
    equip->inUso = val;
}

int getInUsoEquip(Equip equip) {
    return equip->inUso;
}

void addItemEquip(Equip equip, rifInv_t inv) {
    equip->vettEq[equip->inUso] = inv;
}

rifInv_t getEqItem(Equip equip, int ind){
    return equip->vettEq[ind];
}

int scalaEquip(Equip equip, char *nomeAccessorio) {
    int i = 0, ind = -1;

    for (i = 0; i < equip->inUso; i++) {
        if (strcmp(nomeAccessorio, equip->vettEq[i]->nome) == 0)
            ind = i;
        /*break;
         *Utilizzando il comando break l'indice sarà uguale alla prima corrispondenza, nel caso in cui ci fossero
         *corrispondenze succesive esse andranno poi scalate successivamente.
         *Per esempio, nel caso in cui abbia la prima corrispondenza con indice = 0 e un ulteriore corrispondenza
         *con indice = MAX_EQ, non utilizzando il comando break, quindi scorrendo interamente il vettore, ho la
         *possibilità di evitare il for successivo.
         *In conclusione con il break si hanno meno confronti ma potenzialemnte più scambi.
         *Nel caso in cui un oggetto possa essere euipaggiato una sola volta è invece vantaggiosa l'interruzione
         *forzata.
         */
    }

    if (ind == -1)
        return 0;

    //Scalo gli eventuali elementi successivi a quello rimosso.
    for (i = ind; i < equip->inUso - 1; i++) {
        equip->vettEq[i] = equip->vettEq[i + 1];
    }
    equip->inUso = equip->inUso - 1;
    return 1;
}

int validoEquip(stat_t stat, stat_t statInv) {
    if (stat.hp + statInv.hp >= 1 &&
        stat.mp + statInv.mp >= 1 &&
        stat.atk + statInv.atk >= 1 &&
        stat.def + statInv.def >= 1 &&
        stat.mag + statInv.mag >= 1 &&
        stat.spr + statInv.spr >= 1)
        return 1;
    return 0;
}