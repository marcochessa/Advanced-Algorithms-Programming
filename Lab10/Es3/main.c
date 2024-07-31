#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>

#include "ST.h"
#include "Graph.h"

#define MAXL 31

Graph read_file(FILE *fin, ST *st, int *V);

int main() {
    char label1[MAXL], label2[MAXL], label3[MAXL], select[MAXL], *sel;
    int i, V, stop = 0, listgen = 0;
    int id, id2, id3;
    Graph g = NULL;
    ST st = NULL;
    FILE *fin;
    elab_t tmp;

    fin = fopen("grafo.txt", "r");
    if (fin == NULL)
        exit(-1);

    g = read_file(fin, &st, &V);
    if (g == NULL || st == NULL)
        exit(-1);

    do {
        printf("\nQuale operazione vuoi eseguire?\n");
        printf("\tA: Visualizza numero e nome dei nodi\n");
        printf("\tB: Visualizza se 3 nodi formano un sottografo completo\n");
        printf("\tC: Genera lista di adiacenza\n");
        printf("\tZ: Esci\n");
        scanf("%s", select);
        for (sel = select; !isalpha(*sel); sel++);
        *sel = toupper(*sel);
        switch (*sel) {
            case 'A': {
                printf("Numero di vertici: %d\n", V);
                /*Per tabella di simboli viene utilizzato un vettore ordinato, in questo modo vengono poi stampate
                 * in ordine alfabetico crescente gli elementi della tabella di simboli, utilizzando una funzione
                 * ad accesso diretto*/
                for (i = 0; i < V; i++) {
                    tmp = STsearchByIndex(st, i);
                    printf("\t%s, rete: %s\n", tmp.name, tmp.subnet);
                }
            }
                break;
            case 'B': {
                printf("Quale nodi vuoi esaminare? [nome1][nome2][nome3]\n");
                scanf("%s %s %s", label1, label2, label3);
                id = STsearch(st, label1);
                id2 = STsearch(st, label2);
                id3 = STsearch(st, label3);

                if (id < 0 || id2 < 0 || id3 < 0) {
                    printf("Uno o piu' nodi non esistenti\n");
                    break;
                }
                if (GRAPHsottografo(g, id, id2, id3))
                    printf("I nodi %s, %s, %s formano un sottografo completo\n", label1, label2, label3);
                else
                    printf("I nodi NON formano un sottografo completo\n");
            }
                break;
            case 'C':
                if (!GRAPHmat2list(g))
                    printf("Generazione avvenuta con successo!\n");
                listgen = 1;
                break;
            case 'Z': {
                stop = 1;
            }
                break;
            default:
                printf("Scelta non valida!\n");
        }
    } while (!stop);

    fclose(fin);
    STfree(st);
    GRAPHfree(g, listgen);
    return 0;
}


int countEdges(FILE *in) {
    int i = 0;
    char *tmp;
    while (!feof) {
        fgets(tmp, 1, in);
        i++;
    }
}

Graph read_file(FILE *fin, ST *st, int *V) {
    int id1, id2, wt;
    char label1[MAXL], label2[MAXL], net1[MAXL], net2[MAXL];
    Graph G;

    elab_t elab1, elab2;
    *st = STinit(1);
    if (*st == NULL) return NULL;

    int i = 0;
    while (!feof(fin)) {
        fscanf(fin, "%s %s %s %s %*d", label1, net1, label2, net2);
        id1 = STsearch(*st, label1);
        if (id1 < 0) {
            elab1.name = strdup(label1);
            elab1.subnet = strdup(net1);
            id1 = STinsert(*st, elab1);
            if (id1 < 0) exit(-1);
        }
        id2 = STsearch(*st, label2);
        if (id2 < 0) {
            elab2.name = strdup(label2);
            elab2.subnet = strdup(net2);
            id2 = STinsert(*st, elab2);
            if (id2 < 0) exit(-1);
        }
        i++;
    }

    rewind(fin);

    *V = STcount(*st);
    G = GRAPHinit(*V);
    if (G == NULL) return NULL;

    while (!feof(fin)) {
        fscanf(fin, "%s %*s %s %*s %d", label1, label2, &wt);
        id1 = STsearch(*st, label1);
        id2 = STsearch(*st, label2);
        if (id1 >= 0 && id2 >= 0)
            GRAPHinsertE(G, id1, id2, wt);
    }

    return G;
}
