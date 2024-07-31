#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define len 21

int main() {
    /*Per comodità i file non vengono letti da riga di comando, i file di input vengono fissati nel main e
     * passati come parametri alle funzioni che li utilizzano, mentre quello di output viene creato durante la stampa.
     * La lettura da linea di comando viene ritenuta poco rilevante ai fini della procedura risolutiva attuata*/
    FILE *F1, *F2;
    Graph g;
    int *bestSol;
    int *ker, N;

    printf("-------------------\n");
    printf("2.Acquisizione dei dati e stampa della struttura dati creata\n");
    F1 = fopen("file1.txt", "r");
    if (F1 == NULL) {
        printf("Impossibile aprire file1\n");
        return (-1);
    }
    GRAPHload(&g, F1);
    fclose(F1);

    printf("-------------------\n");
    printf("3.Verifica del kernel dato\n");
    F2 = fopen("file2.txt", "r");
    if (F2 == NULL) {
        printf("Impossibile aprire file1\n");
        return (-1);
    }
    printf("Inseme dato come potenziale kernel:\n");
    N = readKernel(F2, &ker, g);
    if (isKernel(g, ker, N)) {
        printf("L'inseme dato e' un Kernel\n");
    } else {
        printf("L'inseme dato non e' un Kernel\n");
    }
    fclose(F2);


    printf("-------------------\n");
    printf("4.Ricerca del kernel massimo del grafo\n");
    N = findKernel(g, &bestSol);


    printf("-------------------\n");
    printf("5.Calcolo della lunghezza del cammino semplice\n");
    printf("Il cammino migliore contentiene %d nodi del Kernel\n", camMaxVert(g, bestSol, N));

    free(bestSol);
    GRAPHfree(g);
    return 0;
}
