//
// Created by marco on 31/01/2019.
//
#include <mem.h>
#include <malloc.h>
#include "Graph.h"

#define len 21

struct node {
    int v;
    link next;
};

struct G {
    link *ladj;
    int V;
    int E;
    ST tab;
    link z; //->SENTINELLA
};

static int cammino(Graph g, int ind, int *Ker, int N, int max, int *vCons, int *finalMax);

static Edge EDGEcreate(int v, int w);

static void insertE(Graph g, Edge e);

static link NEW(int v, link next);

static void genKernel(Graph g, int *sol, int *bestSol, int pos, int start, int car);

static void saveKernel(FILE *F3, int *ker, int N, Graph g);

static int BelongKer(int i, int *LVert, int N);

void GRAPHload(Graph *G, FILE *F1) {
    int id1, id2;
    int V;
    char nome1[len], nome2[len];
    Graph g;
    ST table;

    table = STinit(1);
    if (table == NULL)
        return;

    int i = 0;
    char *val;
    while (!feof(F1)) {
        fscanf(F1, "%s %s", nome1, nome2);
        id1 = STsearch(table, nome1);
        if (id1 < 0) {
            val = strdup(nome1);
            STinsert(table, val);
        }
        id2 = STsearch(table, nome2);
        if (id2 < 0) {
            val = strdup(nome2);
            STinsert(table, val);
        }
        i++;
    }
    rewind(F1);

    V = STcount(table);
    g = GRAPHinit(V);
    g->tab = table;

    while (!feof(F1)) {
        fscanf(F1, "%s %s ", nome1, nome2);
        id1 = STsearch(g->tab, nome1);
        id2 = STsearch(g->tab, nome2);
        if (id1 >= 0 && id2 >= 0)
            GRAPHinsertE(g, id1, id2);
    }

    printf("GRAfO: <id>[index]\n");
    GRAPHprint(g);
    *G = g;
}

Graph GRAPHinit(int V) {
    int v;
    Graph g = malloc(sizeof(*g));
    if (g == NULL)
        return NULL;
    g->V = V;
    g->E = 0;
    g->z = NEW(-1, NULL);
    g->ladj = malloc(g->V * sizeof(link));
    for (v = 0; v < g->V; v++)
        g->ladj[v] = g->z; //Inizializzo i nodi in base all'arco sentinella
    return g;
}


static link NEW(int v, link next) {
    link x = malloc(sizeof *x);
    x->v = v;
    x->next = next;
    return x;
}

static Edge EDGEcreate(int v, int w) {
    Edge e;
    e.v = v;
    e.w = w;
    return e;
}

static void insertE(Graph g, Edge e) {
    int v = e.v, w = e.w;
    g->ladj[v] = NEW(w, g->ladj[v]);
    g->E++;
}

void GRAPHinsertE(Graph g, int id1, int id2) {
    insertE(g, EDGEcreate(id1, id2));
}

int isKernel(Graph g, int *LVert, int N) {
    int i, j, id;
    int nConnesso;
    link x;

    for (i = 0; i < N; i++) {
        id = LVert[i];
        for (x = g->ladj[id]; x != g->z; x = x->next)
            for (j = 0; j < N; j++) {
                if (LVert[j] == x->v)
                    return 0; //Nodi del probabile kernel adiacenti, interruzione
            }
    }

    for (i = 0; i < g->V; i++) {
        //CONTROLLA SE i NON APPARTIENE A LVert
        if (BelongKer(i, LVert, N) == 0) {
            nConnesso = 0;
            for (j = 0; j < N; j++) {
                id = LVert[j];
                for (x = g->ladj[id]; x != g->z; x = x->next) {
                    if (x->v == i) {
                        nConnesso = 1;
                        break;
                    }
                }
            }
            if (nConnesso == 0)
                return 0; //Il nodo di V-K non è connesso a nessun nodo dell'insieme K, interruzione
        }
    }
    return 1; //L'insieme dato è un Kernel
}

static void genKernel(Graph g, int *sol, int *bestSol, int pos, int start, int car) {
    int i, id;
    if (pos >= car) {
        if (isKernel(g, sol, car)) {
            for (i = 0; i < car; i++)
                bestSol[i] = sol[i];
            return;
        }
    }

    for (id = start; id < g->V; id++) {
        sol[pos] = id;
        genKernel(g, sol, bestSol, pos + 1, id + 1, car);
    }
    return;
}

static void saveKernel(FILE *F3, int *ker, int N, Graph g) {
    F3 = fopen("file3.txt", "w");
    if (F3 == NULL) {
        printf("Impossibile aprire file di output\n");
        return;
    }
    for (int i = 0; i < N; i++) {
        //Viene stampato a video per comodità
        printf("%s\n", STsearchByIndex(g->tab, ker[i]));
        fprintf(F3, "%s\n", STsearchByIndex(g->tab, ker[i]));
    }
    fclose(F3);
    printf("Salvato in file3.txt\n");
}

int findKernel(Graph G, int **bSol) {
    /* Partendo dalla cardinalità massima vengono generati attraverso il
     * modello delle combinazioni dei potenziali kernel, se viene ottenuta
     * una soluzione valida viene salvato e interrotto il ciclo che decrementa la
     * cardinalità */
    int i;
    int *sol = malloc(G->V * sizeof(int));
    int *bestSol = malloc(G->V * sizeof(int));
    bestSol[0] = -1;

    //Si parte dalla cardinalità massima del kernel, fissata a V-1
    for (i = (G->V) -1; i > 0; i--) {
        genKernel(G, sol, bestSol, 0, 0, i);
        if (bestSol[0] != -1) {
            break;
        }
    }

    if (i != 0) {
        printf("Kernel trovato con cardinalita' %d\n", i);
        FILE *F3;
        saveKernel(F3, bestSol, i, G);
    } else {
        printf("Kernel non trovato\n");
    }
    //Punto il kernel trovato per utilizzarlo in altre funzioni
    *bSol = bestSol;
    free(sol);
    return i;

}

int camMaxVert(Graph g, int *ker, int N) {
    //Verifico i cammini partendo dai nodi del Kernel in modo da risparmiare verifiche
    int finalMax = 0;
    int m = 0, i, j;
    int *vCons = malloc(g->V * sizeof(int));

    for (i = 0; i < N; i++) {
        for (j = 0; j < g->V; j++)
            vCons[j] = 0;
        m = 1;//Considero il nodo di partenza
        /*Viene passato by reference finalMax in modo da avere un aggiornamento del massimo, all' interno alla
         * funzione cammino, senza avere il bisogno di controlli esterni sul valore ritornato da essa*/
        cammino(g, ker[i], ker, N, m, vCons, &finalMax);
    }

    free(vCons);
    return finalMax;
}


static int cammino(Graph g, int ind, int *Ker, int N, int max, int *vCons, int *finalMax) {
    link x;

    if (max > *finalMax) {
        *finalMax = max;
    }

    for (x = g->ladj[ind]; x != g->z; x = x->next) {
        if (vCons[x->v] == 0) { //VCons verifica che i nodi non siano stati già considerati
            if (BelongKer(x->v, Ker, N)) //Se il nodo appartiene al Nucleo incremento max
                max++;
            vCons[x->v] = 1;
            max = cammino(g, x->v, Ker, N, max, vCons, finalMax);

            //In fase di backtrack viene decrementato il massimo negli stessi nodi in cui è stato incrementato
            if (BelongKer(x->v, Ker, N))
                max--;
        }
    }
    return max;
}

void GRAPHprint(Graph g) {
    int v;
    link t;
    for (v = 0; v < g->V; v++)
        for (t = g->ladj[v]; t != g->z; t = t->next) {
            printf("%s[%d] - %s[%d]\n", STsearchByIndex(g->tab, v), v, STsearchByIndex(g->tab, t->v), t->v);
        }
}

static int BelongKer(int i, int *LVert, int N) {
    /*Viene effettuato un controllo lineare seguendo la scelta risolutiva attuata
     * durante l'esame, analogamente poteva essere gestito un vettore che contenesse i
     nodi del kernel in corrispondenza degli indici del grafo in modo da avere un accesso diretto*/
    int j;
    for (j = 0; j < N; j++) {
        if (i == LVert[j])
            return 1;
    }
    return 0;
}

int readKernel(FILE *F2, int **kernel, Graph g) {
    int pos = 0;
    int *ker;
    char ident[len];
    //Si suppone un numero corretto di elementi nel file
    ker = malloc(g->V * sizeof(int));
    while (!feof(F2)) {
        fscanf(F2, "%s", ident);
        printf("%s\n", ident);
        ker[pos] = STsearch(g->tab, ident);
        pos++;
    }

    *kernel = ker;
    return pos;
}

void GRAPHfree(Graph g) {
    int v;
    link t, next;
    for (v = 0; v < g->V; v++)
        for (t = g->ladj[v]; t != g->z; t = next) {
            next = t->next;
            free(t);
        }
    free(g->ladj);
    free(g->z);
    STfree(g->tab);
    free(g);
}