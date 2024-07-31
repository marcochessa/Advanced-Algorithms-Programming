//
// Created by marco on 16/01/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAXC 31

struct node {
    int v;
    int wt;
    link next;
};

struct G {
    link *ladj;
    int V;
    int E;
    ST tab;
    link z; //->ARCO SENTINELLA
};

static int genDag(Graph g, Edge *e, int k, Edge **s, Edge **remEd, int n, int pos, int start, int pCorr, int pMax);

static Edge EDGEcreate(int v, int w, int wt);

static void insertE(Graph g, Edge e);

static link NEW(int v, int wt, link next);

static int searchCicle(Graph G, Edge e, int *visited, int *post, int DAG);

static int removeE(Graph G, Edge e);

static void dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *topOrd, int *ind);

Graph GRAPHinit(int V) {
    int v;
    Graph g = malloc(sizeof(*g));
    if (g == NULL)
        return NULL;
    g->V = V;
    g->E = 0;
    g->z = NEW(-1, -1, NULL);
    g->ladj = malloc(g->V * sizeof(link));
    for (v = 0; v < g->V; v++)
        g->ladj[v] = g->z; //Inizializzo i nodi in base all'arco sentinella

    g->tab = STinit(V);
    if (g->tab == NULL)
        return NULL;
    return g;
}

static link NEW(int v, int wt, link next) {
    link x = malloc(sizeof *x);
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}

Graph GRAPHload(FILE *fin) {
    int V, i, id1, id2, wt;
    char label1[MAXC], label2[MAXC];
    Graph G;
    printf("GRAFO INIZIALE:\n");

    fscanf(fin, "%d", &V);
    G = GRAPHinit(V);
    if (G == NULL)
        return NULL;

    printf("VERTICI %d:\n", V);
    for (i = 0; i < V; i++) {
        fscanf(fin, "%s", label1);
        printf("%d: %s\n", i, label1);
        STinsert(G->tab, label1);
    }

    printf("ARCHI:\n", V);
    while (fscanf(fin, "%s %s %d", label1, label2, &wt) == 3) {
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 >= 0 && id2 >= 0) {
            GRAPHinsertE(G, id1, id2, wt);
            printf("%s[%d] - %s[%d]: %d \n", label1, id1, label2, id2, wt);
        }

    }
    return G;
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

static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}

static void insertE(Graph g, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;
    g->ladj[v] = NEW(w, wt, g->ladj[v]);
    g->E++;
}

void GRAPHinsertE(Graph g, int id1, int id2, int wt) {
    insertE(g, EDGEcreate(id1, id2, wt));
}

void stampaGrafo(Graph g) {
    int v;
    link t;
    for (v = 0; v < g->V; v++)
        for (t = g->ladj[v]; t != g->z; t = t->next) {
            printf("%s[%d] - %s[%d]\n", STsearchByIndex(g->tab, v), v, STsearchByIndex(g->tab, t->v), t->v);
        }
}


int GRAPHcountVertex(Graph g) {
    return g->V;
}

int GRAPHremoveE(Graph G, int id1, int id2, int wt) {
    removeE(G, EDGEcreate(id1, id2, wt));
}

static int removeE(Graph G, Edge e) {
    int v = e.v, w = e.w;
    link x;
    if (G->ladj[v]->v == w) {
        G->ladj[v] = G->ladj[v]->next;
        G->E--;
        return 1;
    } else
        for (x = G->ladj[v]; x != G->z; x = x->next)
            if (x->next->v == w) {
                x->next = x->next->next;
                G->E--;
                return 1;
            }
    return 0;
}

int searchDag(Graph g, int *pMax) {
    int n, i, v, w, wt;
    int pCorr = 0;
    Edge *a = GRAPHedges(g);
    Edge **s = malloc(g->E * sizeof(Edge *));
    Edge **remEl = malloc(g->E * sizeof(Edge *));
    if (isDag(g)) {
        return 0;
    }
    for (n = 1; n <= g->V && *pMax == -1; n++) {
        *pMax = genDag(g, a, g->E, s, remEl, n, 0, 0, pCorr, *pMax);
    }
    n--;
    //n viene incrementato alla fine del ciclo quindi per la cardinalità corretta viene sottratto 1

    printf("\nInesieme a peso massimo di archi rimossi\n");
    for (i = 0; i < n; i++) {
        v = s[i]->v;
        w = s[i]->w;
        wt = s[i]->wt;
        printf("%d) %s[%d] - %s[%d] %d\n", i, STsearchByIndex(g->tab, v), v, STsearchByIndex(g->tab, w), w, wt);
        GRAPHremoveE(g, v, w, wt);
    }
    free(s);
    free(remEl);
    free(a);
    return n;
}

static int genDag(Graph g, Edge *e, int k, Edge **s, Edge **remEd, int n,
                  int pos, int start, int pCorr, int pMax) {
    int i, w, v, wt;
    if (pos == n) {
        if (isDag(g)) {
            printf("\nLa rimozione dei seguenti archi permette la costruzione di un DAG\n");
            for (i = 0; i < n; i++) {
                v = remEd[i]->v;
                w = remEd[i]->w;
                wt = remEd[i]->wt;
                printf("%d) %s[%d] - %s[%d] %d\n", i, STsearchByIndex(g->tab, v), v, STsearchByIndex(g->tab, w), w, wt);
            }
            if (pCorr > pMax) {
                for (i = 0; i < n; i++)
                    s[i] = remEd[i];
                pMax = pCorr;
            }
        }
        return pMax;
    }
    for (i = start; i < k; i++) {
        v = e[i].v;
        w = e[i].w;
        wt = e[i].wt;
        if (GRAPHremoveE(g, v, w, wt)) {
            remEd[pos] = &e[i];
            pCorr += wt;
            pMax = genDag(g, e, k, s, remEd, n, pos + 1, i, pCorr, pMax);
            GRAPHinsertE(g, v, w, wt);
            pCorr -= wt;
        }
    }

    return pMax;
}

//Memorizzo tutti gli archi contenuti nella lista di adiacenza in un vettore di Edge
Edge *GRAPHedges(Graph g) {
    int v, E = 0;
    Edge *a;
    a = malloc(g->E * sizeof(Edge));
    if (a == NULL)
        exit(-1);
    link t;
    for (v = 0; v < g->V; v++)
        for (t = g->ladj[v]; t != g->z; t = t->next) {
            a[E] = EDGEcreate(v, t->v, t->wt);
            E++;
        }
    return a;
}

/*Dato un arco di partenza, se seguendo un determinato percorso mi ritrovo su un nodo già visitato
 * non si tratta di un DAG*/
static int searchCicle(Graph G, Edge e, int *visited, int *post, int DAG) {
    link t;
    int w = e.w;
    visited[w] = 1;
    for (t = G->ladj[w]; t != G->z; t = t->next)
        if (visited[t->v] == -1)
            //Se l'arco non è stato visitato ricorro sul successivo
            DAG = searchCicle(G, EDGEcreate(w, t->v, 0), visited, post, DAG);
        else {
            if (post[t->v] == -1)
                //Se l'arco è già stato visitato e il cammino non è stato completato ritorno 0
                return 0;
        }
    post[w] = 1;
    return DAG;
}

/*Inizializza i vettori di visita, e per ogni nodo che non è stato visitato viene chiamata la funzione precedente*/
int isDag(Graph G) {
    int v, *visited, *post;
    int DAG = 1;
    int i;
    visited = malloc(G->V * sizeof(int));
    post = malloc(G->V * sizeof(int));

    for (i = 0; i < G->V && DAG == 1; i++) {
        for (v = 0; v < G->V; v++) {
            visited[v] = -1;
            post[v] = -1;
        }
        DAG = searchCicle(G, EDGEcreate(i, i, 0), visited, post, DAG);
    }
    return DAG;

}

int *topSortWdfs(Graph G) {
    int v, time = 0, *pre, *post, *topOrd, ind = G->V - 1;
    pre = malloc(G->V * sizeof(int));
    post = malloc(G->V * sizeof(int));
    topOrd = malloc(G->V * sizeof(int));
    if ((pre == NULL) || (post == NULL) || (topOrd == NULL))
        return NULL;

    for (v = 0; v < G->V; v++) {
        pre[v] = -1;
        post[v] = -1;
    }

    for (v = 0; v < G->V; v++)
        if (pre[v] == -1)
            dfsR(G, EDGEcreate(v, v, 0), &time, pre, post, topOrd, &ind);

    return topOrd;
}

static void dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *topOrd, int *ind) {
    link t;
    int w = e.w;
    pre[w] = (*time)++;
    for (t = G->ladj[w]; t != G->z; t = t->next)
        if (pre[t->v] == -1)
            dfsR(G, EDGEcreate(w, t->v, t->wt), time, pre, post, topOrd, ind);
    topOrd[*ind] = w;
    *ind = *ind - 1;
    post[w] = (*time)++;
    /*Nonostante non vengano utilizzate nello specifico caso dell'ordinamento, vengono comunque mantenute
    /*le informazioni relative al "tempo" di scoperta*/
}


void DAGmaxPath(Graph G, int id, int *topSort, int start) {
    int v, i;
    link t;
    int *maxdist;
    maxdist = malloc(G->V * sizeof(int));
    if (maxdist == NULL)
        return;

    for (v = 0; v < G->V; v++) {
        maxdist[v] = -1;
    }

    maxdist[id] = 0;
    /*L'indice i parte da start, in questo modo non vengono considerati i vertici che precedono nell'ordine*/
    for (i = start; i < G->V; i++) {
        v = topSort[i];
        if (maxdist[v] != -1) {
            for (t = G->ladj[v]; t != G->z; t = t->next)
                if (maxdist[v] + t->wt > maxdist[t->v]) {
                    maxdist[t->v] = maxdist[v] + t->wt;
                }
        }
    }
    printf("\n---------\n");
    printf("Vertex: %s[%d] Maximium distances:\n", STsearchByIndex(G->tab, id), id);
    for (v = 0; v < G->V; v++)
        if (maxdist[v] != -1)
            printf(" %s[%d] = %d \n", STsearchByIndex(G->tab, v), v, maxdist[v]);

}