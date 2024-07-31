//
// Created by marco on 11/12/2018.
//

#include "pg.h"

rifPg_t creaPg(void) {
    rifPg_t p = malloc(sizeof *p);
    return p;
}

key getKey(rifPg_t pg) {
    return pg->codice;
}

int keyCompare(key k1, key k2) {
    if (strcmp(k1, k2) == 0)
        return 1;
    return 0;
}

void printPgDetails(rifPg_t pg) {
    printf("Codice: %s \n", pg->codice);
    printf("Nome: %s \n", pg->nome);
    printf("Classe: %s \n", pg->classe);
    printStat(pg->stat);

    printf("Equipaggiamento:\n");
    if (getInUsoEquip(pg->equip) == 0)
        printf("Nessun equipaggiamento\n");
    else
        for (int i = 0; i < getInUsoEquip(pg->equip); i++) {
            printf("Elemento %d\n", i);
            printDetails(getEqItem(pg->equip, i));
            printf("\n");
        }
}