//
// Created by marco on 16/01/2019.
//

#ifndef ESERCIZIO1_GRAPH_H
#define ESERCIZIO1_GRAPH_Hl

#include "ST.h"
#include <stdio.h>

typedef struct edge {
    int v;
    int w;
    int wt;
} Edge;

typedef struct node *link;

typedef struct G *Graph;

Graph GRAPHinit(int V);

int GRAPHcountVertex(Graph g);

int isDag(Graph G);

Graph GRAPHload(FILE *fin);

void stampaGrafo(Graph g);

int searchDag(Graph g, int *pMax);

void GRAPHfree(Graph g);

int GRAPHremoveE(Graph G, int id1, int id2, int wt);

void GRAPHinsertE(Graph g, int id1, int id2, int wt);

Edge *GRAPHedges(Graph g);

int *topSortWdfs(Graph G);

void DAGmaxPath(Graph G, int id, int *topSort, int start);

#endif //ESERCIZIO1_GRAPH_H
