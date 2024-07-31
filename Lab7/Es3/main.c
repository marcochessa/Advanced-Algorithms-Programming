#include <stdio.h>
#include <malloc.h>
#include <mem.h>

#define MAX_EQ 8

typedef struct stat_t {
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
} stat_t;

typedef struct inv_t {
    char *nome;
    char *tipo;
    stat_t stat;
} inv_t;

typedef struct equip_t {
    int inUso;
    //Il vettore sottostante potrebbe essere allocato dinamicamente, per comodità si allora in maniera statica
    inv_t *vettEq[MAX_EQ];
} equip_t;

typedef struct pg_t {
    char codice[7];
    char nome[50 + 1];
    char classe[50 + 1];
    equip_t equip;
    stat_t stat;

} pg_t;

typedef struct nodoPg_t *link;

typedef struct tabPg_t {
    link headPg;
    link tailPg;
    int nPg;
} tabPg_t;

typedef struct tabInv_t {
    inv_t *vettInv;
    int nInv;
} tabInv_t;

typedef struct nodoPg_t {
    pg_t val;
    link next;
} nodoPg_t;

link newNode(pg_t val, link next);

//Siccome non sono ammessi personaggi con lo stesso codice viene inserita questa funzione di controllo
int pgPresente(tabPg_t *tabPg, char *codice);

void listInsTailFast(tabPg_t *tabPg, pg_t val);

int listDelKey(tabPg_t *tabPg, char *codice);

stat_t leggiStat(FILE *fp);

void caricaPersonaggi(tabPg_t *tabPg);

void caricaInventario(tabInv_t *tabInv);

void liberaInventario(tabInv_t *tabInv);

int cercaAccessiorio(char *nomeAccessorio, tabInv_t tabInv);

int validoEquip(stat_t stat, stat_t statInv);

/*Si è optato per utilizzare una sola funzione per modificare le statistiche, utilizzando un flag per identificare
* se si tratta di un equipaggiamento o una rimozione*/
stat_t aggiornaStat(stat_t statPG, stat_t statInv, int eqDisEq);

void stampaDettagli(char *codice, tabPg_t tabPg);

void eqPersonaggio(char *codice, tabPg_t *tabPg, tabInv_t *tabInv);

void disEqPersonaggio(char *codice, tabPg_t *tabPg, tabInv_t *tabInv);

int scalaEquip(equip_t *equip, char *nomeAccessorio);

typedef enum {
    r_inserisci_personaggio, r_rimuovi_personaggio, r_equipaggia_oggetto,
    r_sottrai_oggetto, r_stampa_statistiche, r_fine, r_err
} comando_e;

comando_e leggiComando(void);

void istruzione(comando_e codiceComando, tabPg_t *tabPg, tabInv_t *tabInv);

int main() {
    int continua = 1;
    comando_e com;
    tabPg_t tabPg;
    tabPg.headPg = NULL;
    tabPg.tailPg = NULL;
    tabPg.nPg = 0;

    tabInv_t tabInv;
    caricaPersonaggi(&tabPg);
    caricaInventario(&tabInv);

    while (continua) {
        com = leggiComando();
        if (com == r_fine) {
            continua = 0;
        } else if (com == r_err) {
            printf("Comando inserito non valido\n");
        } else {
            istruzione(com, &tabPg, &tabInv);
        }
    }

    liberaInventario(&tabInv);

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

stat_t leggiStat(FILE *fp) {
    stat_t tmp;
    fscanf(fp, "%d %d %d %d %d %d", &tmp.hp, &tmp.mp, &tmp.atk, &tmp.def, &tmp.mag, &tmp.spr);
    return tmp;
}

void stampaDettagli(char *codice, tabPg_t tabPg) {
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
            printf("Statistiche:\n"
                   "\thp: %d\n", x->val.stat.hp);
            printf("\tmp: %d\n", x->val.stat.mp);
            printf("\tatk: %d\n", x->val.stat.atk);
            printf("\tdef: %d\n", x->val.stat.def);
            printf("\tmag: %d\n", x->val.stat.mag);
            printf("\tspr: %d\n", x->val.stat.spr);

            printf("Equipaggiamento:\n");
            if (x->val.equip.inUso == 0)
                printf("Nessun equipaggiamento\n");
            else
                for (int i = 0; i < x->val.equip.inUso; i++) {
                    printf("\t Nome: %s, Tipo: %s\n", x->val.equip.vettEq[i]->nome, x->val.equip.vettEq[i]->tipo);
                }
        }
    }
    if (trovato == 0)
        printf("Personaggio non trovato\n");
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

int cercaAccessiorio(char *nomeAccessorio, tabInv_t tabInv) {
    int i = 0;
    for (i = 0; i < tabInv.nInv; i++) {
        if (strcmp(nomeAccessorio, tabInv.vettInv[i].nome) == 0) {
            return i;
        }
    }
    return -1;
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

comando_e leggiComando(void) {
    comando_e c;
    char cmd[100];
    char tabella[r_err][50] = {"inserisci_personaggio",
                               "rimuovi_personaggio",
                               "equipaggia_oggetto",
                               "sottrai_oggetto",
                               "stampa_stat",
                               "fine"};

    printf("*****************************"
           "\nInserisci comando: "
           "\n-->\"inserisci_personaggio\", "
           "\n-->\"rimuovi_personaggio\", "
           "\n-->\"equipaggia_oggetto\" (assegna un oggetto dell'inventario a un personaggio dato),"
           "\n-->\"sottrai_oggetto\" (sottrae un oggetto a un personaggio dato), "
           "\n-->\"stampa_stat\" (stampa le statistiche di un personaggio dato), "
           "\n-->\"fine\"\n");

    scanf("%s", cmd);

    //Si presume un inserimento del comando con tutti i caratteri minuscoli;
    c = r_inserisci_personaggio;
    while (c < r_err && strcmp(cmd, tabella[c]) != 0)
        c++;
    return c;

}

void istruzione(comando_e codiceComando, tabPg_t *tabPg, tabInv_t *tabInv) {
    pg_t pgTmp;
    switch (codiceComando) {
        case r_inserisci_personaggio:
            printf("Inserire dati personaggio\n"
                   "<codice> <nome> <classe>\n");
            scanf("%s %s %s", pgTmp.codice, pgTmp.nome, pgTmp.classe);
            printf("Inserire statistiche personaggio\n"
                   "<hp> <mp> <atk> <def> <mag> <spr>\n");
            scanf("%d %d %d %d %d %d", &pgTmp.stat.hp, &pgTmp.stat.mp, &pgTmp.stat.atk, &pgTmp.stat.def,
                  &pgTmp.stat.mag, &pgTmp.stat.spr);
            pgTmp.equip.inUso = 0;
            if (pgPresente(tabPg, pgTmp.codice))
                printf("Codice personaggio gia' presente in lista\n");
            else {
                listInsTailFast(tabPg, pgTmp);
                printf("Personaggio %s aggiunto\n", pgTmp.codice);
            }
            break;

        case r_rimuovi_personaggio:
            printf("Inserire il codice del personaggio da rimuovere\n");
            scanf("%s", pgTmp.codice);
            if (listDelKey(tabPg, pgTmp.codice))
                printf("Personaggio %s rimosso\n", pgTmp.codice);
            else
                printf("Non e' possibile rimuovere il personaggio indicato\n");
            break;

        case r_equipaggia_oggetto:
            printf("Inserire il codidce del personaggio a cui equipaggiare\n");
            scanf("%s", pgTmp.codice);
            eqPersonaggio(pgTmp.codice, tabPg, tabInv);

            break;
        case r_sottrai_oggetto:
            printf("Inserire il codidce del personaggio a cui disequipaggiare un oggetto\n");
            scanf("%s", pgTmp.codice);
            disEqPersonaggio(pgTmp.codice, tabPg, tabInv);

            break;
        case r_stampa_statistiche:
            printf("Inserire il codidce del personaggio di cui vuoi conoscere i dati\n");
            scanf("%s", pgTmp.codice);
            stampaDettagli(pgTmp.codice, *tabPg);

            break;

    }
}

