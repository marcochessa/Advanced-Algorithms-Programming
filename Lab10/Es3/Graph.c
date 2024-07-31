//
// Created by marco on 04/01/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"


typedef struct node *link;
struct node {
    int index;
    int weight;
    link next;
};

struct G {
    int **madj;
    link *ladj;
    int V;
    int E;
};

static link NEW(int dst, int w, link next);

static Edge EDGEcreate(int v, int w, int wt);

static int **MATRIXint(int r, int c, int val);

static void insertE(Graph g, Edge e);

static int searchInList(link *list, int node1, int node2);

static int GRAPHsottografoMatrix(Graph g, int id, int id2, int id3);

static int GRAPHsottografoList(Graph g, int id, int id2, int id3);

//Alloco dinamicamente la Matrice di adiacenza e inizializzo i suoi elementi a 'val'
static int **MATRIXint(int r, int c, int val) {
    int i, j;
    int **t = malloc(r * sizeof(int *));
    for (i = 0; i < r; i++)
        t[i] = malloc(c * sizeof(int));
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            t[i][j] = val;
    return t;
}

static link NEW(int dst, int w, link next) {
    link x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;
    x->index = dst;
    x->weight = w;
    x->next = next;
    return x;
}


//Inizializzazione con Matrice di adiacenza
Graph GRAPHinit(int V) {
    Graph g = malloc(sizeof *g);
    g->V = V;
    g->E = 0;
    g->ladj = NULL;
    g->madj = MATRIXint(V, V, 0);
    return g;
}

/*Inizializzazione con lista di adiacenza
Graph GRAPHinit(int V) {
    int i;
    Graph g = malloc(sizeof(*g));
    if (g == NULL)
        return NULL;
    g->V = V;
    g->E = 0;
    g->ladj = malloc(V * sizeof(link));
    if (g->ladj == NULL)
        return NULL;
    for (i = 0; i < V; i++)
        g->ladj[i] = NULL;
    g->madj = NULL;
    return g;
}
*/

void GRAPHfree(Graph g, int listGen) {
    int v;
    for (v = 0; v < g->V; v++)
        free(g->madj[v]);
    free(g->madj);
    free(g);

    if (listGen) {
        link tmp, t;
        for (v = 0; v < g->V; v++)
            for (t = g->ladj[v]; t != NULL;) {
                tmp = t;
                t = t->next;
                free(tmp);
            }
        free(g->ladj);
    }

}

static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}

//LETTURA CON MATRICE DI ADIACENZA
static void insertE(Graph g, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;
    if (g->madj[v][w] == 0)
        g->E++;
    //Per grafi non orientati pesati
    g->madj[v][w] = wt;
    g->madj[w][v] = wt;
}

/*LETTURA CON LISTA DI ADIACENZA
static void  insertE(Graph g, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;
    g->ladj[v] = NEW(w, wt, g->ladj[v]);
    g->ladj[w] = NEW(v, wt, g->ladj[w]);
    g->E++;
}
*/

void GRAPHinsertE(Graph g, int id1, int id2, int wt) {
    insertE(g, EDGEcreate(id1, id2, wt));
}

int GRAPHmat2list(Graph g) {
    int i, j;
    link iter;

    if (g->madj == NULL)
        return -1; //Matrice non allocata
    if (g->ladj != NULL)
        return 0; //Lista esistente

    //Alloco il vettore di liste per la lista di adiacenza
    g->ladj = malloc(g->V * sizeof(link));
    if (g->ladj == NULL)
        return -1;//Lista non allocata
    //Assegno null a tutti i puntatori delle liste interne
    for (i = 0; i < g->V; i++)
        g->ladj[i] = NULL;

    for (i = 0; i < g->V; i++) {
        g->ladj[i] = NULL;
        for (j = 0; j < g->V; j++) {
            g->ladj[i] = NEW(j, g->madj[i][j], g->ladj[i]);
            g->ladj[j] = NEW(i, g->madj[i][j], g->ladj[j]);
        }
    }

    return 0;
}

int GRAPHsottografo(Graph g, int id, int id2, int id3) {
    int nMatrix, nList;
    /*ENTRAMBE LE FUNZIONI VENGONO CHIAMATE PER OGNI RICHIESTA, LA FUNZIONE POTREBBE
     * FACILMENTE ESSERE INTEGRATA AGGIUNGENDO UN FLAG COME PARAMETRO*/
    nMatrix = GRAPHsottografoMatrix(g, id, id2, id3);
    nList = GRAPHsottografoList(g, id, id2, id3);
    //printf("MATRICE: %d LISTA: %d \n", nMatrix, nList);
    return nMatrix;
}

static int GRAPHsottografoMatrix(Graph g, int id, int id2, int id3) {
    if (g->madj == NULL)
        return 0;
    //NEL CASO CORRENTE, DI GRAFO NON ORIENTATO
    if (g->madj[id][id2] == 0)
        return 0;
    if (g->madj[id2][id3] == 0)
        return 0;
    if (g->madj[id][id3] == 0)
        return 0;
    return 1;
}

static int GRAPHsottografoList(Graph g, int id, int id2, int id3) {
    if (g->ladj == NULL)
        return 0;
    if (searchInList(g->ladj, id, id2) == 0)
        return 0;
    if (searchInList(g->ladj, id2, id3) == 0)
        return 0;
    if (searchInList(g->ladj, id3, id) == 0)
        return 0;
    return 1;


}

static int searchInList(link *list, int node1, int node2) {
    link iter;
    iter = list[node1];
    while (iter != NULL) {
        if (iter->index == node2)
            return 1;
        iter = iter->next;
    }
    return 0;
}
