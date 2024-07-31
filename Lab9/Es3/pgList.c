//
// Created by marco on 11/12/2018.
//

#include <malloc.h>
#include <mem.h>
#include "pgList.h"

#define MAX_EQ 8

typedef struct nodoPg_t {
    rifPg_t val;
    link next;
} nodoPg_t;

typedef struct tabPg_t {
    link headPg;
    link tailPg;
    int nPg;
} tabPg_t;


TabPg creaTabPg() {
    TabPg tmp;
    tmp = malloc(sizeof(tabPg_t));
    /*Una volta allocata la memoria viene chiamata una funzione statica che imposta i valori iniziali
     *della lista*/
    setVoidTab(tmp);
    return tmp;
}

static void setVoidTab(TabPg tabPg) {
    tabPg->headPg = NULL;
    tabPg->tailPg = NULL;
    tabPg->nPg = 0;
}

void caricaPersonaggi(TabPg tabPg) {
    FILE *f_per;
    rifPg_t pg_temp;

    f_per = fopen("pg.txt", "r");
    if (f_per == NULL) {
        printf("Impossibile aprire file");
        exit(1);
    }

    while (!feof(f_per)) {
        pg_temp = creaPg();
        fscanf(f_per, "%s %s %s", pg_temp->codice, pg_temp->nome, pg_temp->classe);
        pg_temp->stat = leggiStat(f_per);
        creaEquip(&(pg_temp->equip));
        listInsTailFast(tabPg, pg_temp);
    }
    fclose(f_per);
}

void eqPersonaggio(char *codice, TabPg tabPg, TabInv tabInv) {
    link x;
    int ind;
    char nomeAccessorio[50];

    if (tabPg->headPg == NULL)
        return;
    for (x = tabPg->headPg; x != NULL; x = x->next) {
        if (keyCompare(getKey(x->val), codice)) {
            //Si considera un numero massimo di equipaggiamenti fisso (8), si potrebbe facilmente rendere variabile
            if (getInUsoEquip(x->val->equip) < MAX_EQ) {
                printf("Inserire il nome dell'accessorio da equipaggiare\n");
                scanf("%s", nomeAccessorio);
                ind = cercaAccessiorio(nomeAccessorio, tabInv);
                if (ind == -1) {
                    printf("Accessorio non esistente\n");
                } else {
                    if (validoEquip(x->val->stat, getStat(tabInv, ind))) {
                        x->val->stat = aggiornaStat(x->val->stat, getStat(tabInv, ind), 1);
                        addItemEquip(x->val->equip, getObjectPointer(tabInv, ind));
                        setInUsoEquip(x->val->equip, getInUsoEquip(x->val->equip) + 1);
                        printf("%s equipaggiato a %s\n", nomeAccessorio, codice);
                    } else
                        printf("Statistiche non sufficienti per l'equipaggiamento\n");
                }
            } else {
                printf("Numero equipaggiamento massimo raggiunto\n");
            }
            return;
        }
    }
    return;
}

stat_t aggiornaStat(stat_t statPG, stat_t statInv, int eqDisEq) {
    stat_t nuoveStat;
    nuoveStat.hp = statPG.hp + (statInv.hp * eqDisEq);
    nuoveStat.mp = statPG.mp + (statInv.mp * eqDisEq);
    nuoveStat.atk = statPG.atk + (statInv.atk * eqDisEq);
    nuoveStat.def = statPG.def + (statInv.def * eqDisEq);
    nuoveStat.mag = statPG.mag + (statInv.mag * eqDisEq);
    nuoveStat.spr = statPG.spr + (statInv.spr * eqDisEq);
    return nuoveStat;
}

void disEqPersonaggio(char *codice, TabPg tabPg, TabInv tabInv) {
    link x;
    int ind;
    char nomeAccessorio[50];

    if (tabPg->headPg == NULL)
        return;
    for (x = tabPg->headPg; x != NULL; x = x->next) {
        if (keyCompare(getKey(x->val), codice)) {
            printf("Inserire il nome dell'accessorio da rimuovere\n");
            scanf("%s", nomeAccessorio);
            ind = cercaAccessiorio(nomeAccessorio, tabInv);
            if (ind == -1) {
                printf("Accessorio non esistente\n");
            } else {
                x->val->stat = aggiornaStat(x->val->stat, getStat(tabInv, ind), -1);
                if (scalaEquip(x->val->equip, nomeAccessorio))
                    printf("Rimosso %s a personaggio %s\n", nomeAccessorio, codice);
                else
                    printf("Oggetto non equipaggiato al personaggio selezionato\n");
            }
            return;
        }
    }
    return;
}

void listInsTailFast(TabPg tabPg, rifPg_t val) {
    if (tabPg->headPg == NULL)
        tabPg->headPg = tabPg->tailPg = newNode(val, NULL);
    else {
        tabPg->tailPg->next = newNode(val, NULL);
        tabPg->tailPg = tabPg->tailPg->next;
    }
    tabPg->nPg += 1;
}

int pgPresente(TabPg tabPg, char *codice) {
    link x;
    for (x = tabPg->headPg; x != NULL; x = x->next)
        if (keyCompare(getKey(x->val), codice))
            return 1;
    return 0;
}

int listDelKey(TabPg tabPg, char *codice) {
    link x, p;
    if (tabPg->headPg == NULL)
        return 0;
    for (x = tabPg->headPg, p = NULL; x != NULL; p = x, x = x->next) {
        if (keyCompare(getKey(x->val), codice)) {
            if (x == tabPg->headPg)
                tabPg->headPg = x->next;
            else if (x == tabPg->tailPg) {
                tabPg->headPg = p;
                p->next = NULL;
            } else
                p->next = x->next;
            tabPg->nPg -= 1;
            free(x);
            return 1;
        }
    }
    return 0;
}

link newNode(rifPg_t val, link next) {
    link x = malloc(sizeof(*x));
    if (x == NULL)
        return NULL;
    x->val = val;
    x->next = next;
    return x;
}

int getNumPg(TabPg tabPg) {
    return tabPg->nPg;
}

void stampaDettagliPg(char *codice, TabPg tabPg) {
    link x;
    int trovato = 0;

    if (tabPg->headPg == NULL) {
        printf("Lista vuota\n");
        return;
    }
    for (x = tabPg->headPg; x != NULL && trovato == 0; x = x->next) {
        if (keyCompare(getKey(x->val), codice)) {
            trovato = 1;
            printPgDetails(x->val);
        }
    }
    if (trovato == 0)
        printf("Personaggio non trovato\n");
}

void freeTabPg(TabPg tabPg){
    link x;
    if (tabPg->headPg == NULL)
        return;
    for (x = tabPg->headPg; x != NULL; x = x->next) {
        free(x->val->equip);
        free(x->val);
    }
    free(tabPg);
}