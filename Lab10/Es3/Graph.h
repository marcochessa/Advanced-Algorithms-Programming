//
// Created by marco on 04/01/2019.
//

#ifndef ESERCIZIO3_GRAPH_H
#define ESERCIZIO3_GRAPH_H

typedef struct edge {
    int v;
    int w;
    int wt;
} Edge;

typedef struct G *Graph;

Graph GRAPHinit(int V);

void GRAPHfree(Graph g, int listGen);

void GRAPHinsertE(Graph g, int id1, int id2, int wt);

int GRAPHmat2list(Graph g);

int GRAPHsottografo(Graph g, int id, int id2, int id3);

#endif //ESERCIZIO3_GRAPH_H
