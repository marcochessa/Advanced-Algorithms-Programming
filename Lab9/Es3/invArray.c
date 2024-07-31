//
// Created by marco on 11/12/2018.
//

#include <mem.h>
#include <stdlib.h>
#include "invArray.h"

struct tabInv_t{
rifInv_t *vettInv;
int nInv;
} tabInv_t;

TabInv creaTabInv(){
   TabInv tmp;
   tmp=malloc(sizeof(struct tabInv_t));
   return tmp;
}

void caricaInventario(TabInv tabInv) {
    FILE *f_inv;
    int i, N;
    char nome_tmp[50];
    char tipo_tmp[50];

    f_inv = fopen("inventario.txt", "r");
    if (f_inv == NULL) {
        printf("Impossibile aprire file");
        exit(1);
    }

    fscanf(f_inv, "%d", &N);
    tabInv->vettInv = malloc(N * sizeof(rifInv_t));
    tabInv->nInv = N;

    for (i = 0; i < N; i++) {
        tabInv->vettInv[i]=creaInv();
        fscanf(f_inv, "%s %s", nome_tmp, tipo_tmp);
        tabInv->vettInv[i]->nome = strdup(nome_tmp);
        tabInv->vettInv[i]->tipo = strdup(tipo_tmp);
        tabInv->vettInv[i]->stat = leggiStat(f_inv);
    }

    fclose(f_inv);
}

void liberaInventario(TabInv tabInv) {
    int i = 0;
    int N = tabInv->nInv;
    //Libero prima le stringhe interne allocate dinamicamente, gli elementi e successivamente l'intero vettore di struct
    for (i = 0; i < N; i++) {
        free(tabInv->vettInv[i]->nome);
        free(tabInv->vettInv[i]->tipo);
        free(tabInv->vettInv[i]);
    }
    free(tabInv->vettInv);
    free(tabInv);
}

int cercaAccessiorio(char *nomeAccessorio, TabInv tabInv) {
    int i = 0;
    for (i = 0; i < tabInv->nInv; i++) {
        if (EqKeyCompare(getEqKey(tabInv->vettInv[i]),nomeAccessorio)){
            return i;
        }
    }
    return -1;
}

void stampaDettagliOggetto(char *nomeAccessorio, TabInv tabInv) {
    int ind;
    ind = cercaAccessiorio(nomeAccessorio, tabInv);
    if (ind == -1) {
        printf("Accessorio non presente\n");
        return;
    } else {
        printDetails(tabInv->vettInv[ind]);
    }
}

stat_t getStat( TabInv tabInv, int indice){
    return tabInv->vettInv[indice]->stat;
}

rifInv_t getObjectPointer( TabInv tabInv, int indice){
    return (tabInv->vettInv[indice]);
}

