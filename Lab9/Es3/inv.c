//
// Created by marco on 11/12/2018.
//

#include <mem.h>
#include "inv.h"

rifInv_t creaInv(void) {
    rifInv_t c = malloc(sizeof *c);
    return c;
}

KeyEq getEqKey(rifInv_t inv){
    return inv->nome;
}

int EqKeyCompare(KeyEq k1,KeyEq k2){
    if(strcmp(k1,k2)==0)
        return 1;
    return 0;
}

//Viene creata questa funzione per poterla utilizzare in più situazioni
void printDetails(rifInv_t oggetto){
    printf("Nome: %s \n", oggetto->nome);
    printf("Tipo: %s \n", oggetto->tipo);
    printStat(oggetto->stat);
}