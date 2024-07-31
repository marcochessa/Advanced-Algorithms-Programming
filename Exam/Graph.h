//
// Created by marco on 31/01/2019.
//

#ifndef ESAME_GRAPH_H
#define ESAME_GRAPH_H
#include <stdio.h>
#include "ST.h"

typedef struct edge {
    int v;
    int w;
} Edge;

typedef struct node *link;

typedef struct G *Graph;

Graph GRAPHinit(int V);

void GRAPHinsertE(Graph g, int id1, int id2);
/*Analogo a
 * void GRAPHinsertE(Graph g, Edge e);
 * Utilizzato in sede d'esame*/

int GRAPHremoveE(Graph G, int id1, int id2);

void GRAPHload(Graph *G, FILE *F1);

int isKernel(Graph g, int *LVert, int N);

int findKernel(Graph G, int **bestSol);

int camMaxVert(Graph g, int *ker, int N);

void GRAPHprint(Graph g);

int readKernel(FILE *F2, int **kernel, Graph g);

void GRAPHfree(Graph g);

#endif //ESAME_GRAPH_H
