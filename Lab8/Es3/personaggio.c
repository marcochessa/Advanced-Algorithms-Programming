//
// Created by marco on 11/12/2018.
//

#include "personaggio.h"

#include "inventario.h"


void caricaPersonaggi(tabPg_t *tabPg) {
    FILE *f_per;
    pg_t pg_temp;

    f_per = fopen("pg.txt", "r");
    if (f_per == NULL) {
        printf("Impossibile aprire file");
        exit(1);
    }

    while (!feof(f_per)) {
        fscanf(f_per, "%s %s %s", pg_temp.codice, pg_temp.nome, pg_temp.classe);
        pg_temp.stat = leggiStat(f_per);
        pg_temp.equip.inUso = 0;
        listInsTailFast(tabPg, pg_temp);
    }
    fclose(f_per);
}

void eqPersonaggio(char *codice, tabPg_t *tabPg, tabInv_t *tabInv) {
    link x;
    int ind;
    char nomeAccessorio[50];

    if (tabPg->headPg == NULL)
        return;
    for (x = tabPg->headPg; x != NULL; x = x->next) {
        if (strcmp(x->val.codice, codice) == 0) {
            //Si considera un numero massimo di equipaggiamenti fisso (8), si potrebbe facilmente rendere variabile
            if (x->val.equip.inUso < MAX_EQ) {
                printf("Inserire il nome dell'accessorio da equipaggiare\n");
                scanf("%s", nomeAccessorio);
                ind = cercaAccessiorio(nomeAccessorio, *tabInv);
                if (ind == -1) {
                    printf("Accessorio non esistente\n");
                } else {
                    if (validoEquip(x->val.stat, tabInv->vettInv[ind].stat)) {
                        x->val.stat = aggiornaStat(x->val.stat, tabInv->vettInv[ind].stat, 1);
                        x->val.equip.vettEq[x->val.equip.inUso] = &(tabInv->vettInv[ind]);
                        x->val.equip.inUso = x->val.equip.inUso + 1;
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

void disEqPersonaggio(char *codice, tabPg_t *tabPg, tabInv_t *tabInv) {
    link x;
    int ind;
    char nomeAccessorio[50];

    if (tabPg->headPg == NULL)
        return;
    for (x = tabPg->headPg; x != NULL; x = x->next) {
        if (strcmp(x->val.codice, codice) == 0) {
            printf("Inserire il nome dell'accessorio da rimuovere\n");
            scanf("%s", nomeAccessorio);
            ind = cercaAccessiorio(nomeAccessorio, *tabInv);
            if (ind == -1) {
                printf("Accessorio non esistente\n");
            } else {
                x->val.stat = aggiornaStat(x->val.stat, tabInv->vettInv[ind].stat, -1);
                if (scalaEquip(&x->val.equip, nomeAccessorio))
                    printf("Rimosso %s a personaggio %s\n", nomeAccessorio, codice);
                else
                    printf("Oggetto non equipaggiato al personaggio selezionato\n");
            }
            return;
        }
    }
    return;
}

void listInsTailFast(tabPg_t *tabPg, pg_t val) {
    if (tabPg->headPg == NULL)
        tabPg->headPg = tabPg->tailPg = newNode(val, NULL);
    else {
        tabPg->tailPg->next = newNode(val, NULL);
        tabPg->tailPg = tabPg->tailPg->next;
    }
    tabPg->nPg += 1;
}

int pgPresente(tabPg_t *tabPg, char *codice) {
    link x;
    for (x = tabPg->headPg; x != NULL; x = x->next)
        if (strcmp(codice, x->val.codice) == 0)
            return 1;
    return 0;
}

int listDelKey(tabPg_t *tabPg, char *codice) {
    link x, p;
    if (tabPg->headPg == NULL)
        return 0;
    for (x = tabPg->headPg, p = NULL; x != NULL; p = x, x = x->next) {
        if (strcmp(x->val.codice, codice) == 0) {
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

link newNode(pg_t val, link next) {
    link x = malloc(sizeof(*x));
    if (x == NULL)
        return NULL;
    x->val = val;
    x->next = next;
    return x;
}

int scalaEquip(equip_t *equip, char *nomeAccessorio) {
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

void stampaDettagliPg(char *codice, tabPg_t tabPg) {
    link x;
    int trovato = 0;

    if (tabPg.headPg == NULL) {
        printf("Lista vuota\n");
        return;
    }
    for (x = tabPg.headPg; x != NULL && trovato == 0; x = x->next) {
        if (strcmp(x->val.codice, codice) == 0) {
            trovato = 1;
            printf("Codice: %s \n", x->val.codice);
            printf("Nome: %s \n", x->val.nome);
            printf("Classe: %s \n", x->val.classe);
            printStat(x->val.stat);

            printf("Equipaggiamento:\n");
            if (x->val.equip.inUso == 0)
                printf("Nessun equipaggiamento\n");
            else
                for (int i = 0; i < x->val.equip.inUso; i++) {
                    printf("Elemento %d\n", i);
                    printDetails(*(x->val.equip.vettEq[i]));
                    printf("\n");
                }
        }
    }
    if (trovato == 0)
        printf("Personaggio non trovato\n");
}