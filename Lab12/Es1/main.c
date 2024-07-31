#include <stdio.h>
#include <mem.h>
#include "Graph.h"

void searchMaxPath(Graph g);

int main() {
    FILE *fp;
    int pMax = -1;
    int card;

    fp = fopen("grafo.txt", "r");
    if (fp == NULL)
        return -1;

    Graph g = GRAPHload(fp);

    fclose(fp);

    card = searchDag(g, &pMax);
    if (card == 0)
        printf("\nIl grafo iniziale e' un dag, cardinalita 0, nessun arco rimosso\n");
    else {
        printf("Il DAG ottenuto con cardinalita' %d, peso totale archi rimossi: %d\n", card, pMax);

        printf("\nGRAFO SOLUZIONE:\n");
        stampaGrafo(g);
    }

    searchMaxPath(g);
    GRAPHfree(g);

    return 0;
}

void searchMaxPath(Graph g) {
    int *arr;
    int i;
    int V = GRAPHcountVertex(g);

    //Viene effettuato l'ordinamento topologico dei vertici salvando gli indici in un vettore d'appoggip
    arr = topSortWdfs(g);

    printf("\nOrdine topologico; \n");
    for (i = 0; i < V; i++)
        printf(" %d  ", arr[i]);

    for (int i = 0; i < V; i++)
        /*Per ogni Vertice viene calcolata la distanza massima da tutti gli altri vertici raggiungibili.
         *Nel caso  in cui un vertice non sia raggiungibile non viene stampato*/
        DAGmaxPath(g, arr[i], arr, i);
}