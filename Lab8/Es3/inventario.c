//
// Created by marco on 11/12/2018.
//

#include "inventario.h"


stat_t leggiStat(FILE *fp) {
    stat_t tmp;
    fscanf(fp, "%d %d %d %d %d %d", &tmp.hp, &tmp.mp, &tmp.atk, &tmp.def, &tmp.mag, &tmp.spr);
    return tmp;
}

void caricaInventario(tabInv_t *tabInv) {
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
    tabInv->vettInv = malloc(N * sizeof(inv_t));
    tabInv->nInv = N;

    for (i = 0; i < N; i++) {
        fscanf(f_inv, "%s %s", nome_tmp, tipo_tmp);
        tabInv->vettInv[i].nome = strdup(nome_tmp);
        tabInv->vettInv[i].tipo = strdup(tipo_tmp);
        tabInv->vettInv[i].stat = leggiStat(f_inv);
    }

    fclose(f_inv);
}

void liberaInventario(tabInv_t *tabInv) {
    int i = 0;
    int N = tabInv->nInv;
    //Libero prima le stringhe interne allocate dinamicamente e successivamente l'intero vettore di struct.
    for (i = 0; i < N; i++) {
        free(tabInv->vettInv[i].nome);
        free(tabInv->vettInv[i].tipo);
    }
    free(tabInv->vettInv);
}

int cercaAccessiorio(char *nomeAccessorio, tabInv_t tabInv) {
    int i = 0;
    for (i = 0; i < tabInv.nInv; i++) {
        if (strcmp(nomeAccessorio, tabInv.vettInv[i].nome) == 0) {
            return i;
        }
    }
    return -1;
}

void stampaDettagliOggetto(char *nomeAccessorio, tabInv_t tabInv) {
    int ind;
    ind = cercaAccessiorio(nomeAccessorio, tabInv);
    if (ind == -1) {
        printf("Accessorio non presente\n");
        return;
    } else {
        printDetails(tabInv.vettInv[ind]);
    }
}

//Viene creata questa funzione per poterla utilizzare in più situazioni
void printDetails(inv_t oggetto){
    printf("Nome: %s \n", oggetto.nome);
    printf("Tipo: %s \n", oggetto.tipo);
    printStat(oggetto.stat);
}

void printStat(stat_t stat){
    printf("Statistiche:\n");
    printf("\thp: %d\n", stat.hp);
    printf("\tmp: %d\n", stat.mp);
    printf("\tatk: %d\n", stat.atk);
    printf("\tdef: %d\n", stat.def);
    printf("\tmag: %d\n", stat.mag);
    printf("\tspr: %d\n", stat.spr);
}