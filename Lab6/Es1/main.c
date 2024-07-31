#include <stdio.h>
#include <malloc.h>


typedef struct arco {
    int ver1;
    int ver2;
} arco;

typedef struct grafo {
    int *nodi;
    arco *archi;
} grafo;

void powerset(int pos, grafo G, int *sol, int k, int E);

int valido(int pos, int *sol, grafo G, int E);


int main() {
    FILE *fp;
    int N, E;
    int *sol;
    grafo G;

    fp = fopen("grafo.txt", "r");
    if (fp == NULL) {
        printf("Impossibile aprire file");
        return 1;
    }

    fscanf(fp, "%d %d", &N, &E);
    G.nodi = malloc(N * sizeof(int));
    G.archi = malloc(N * sizeof(arco));

    /*Per memorizzare i nodi del grafo basterebbe un intero visto che i nodi sono gli interi compresi fra [0,N],
     *si utilizza comunque un vettore per rendere il codice più comprensibile.*/
    for (int i = 0; i < N; i++) {
        G.nodi[i] = i;
    }

    for (int j = 0; j < E; j++) {
        fscanf(fp, "%d %d", &G.archi[j].ver1, &G.archi[j].ver2);
    }

    sol = malloc(N * sizeof(int));
    powerset(0, G, sol, N, E);


}

void powerset(int pos, grafo G, int *sol, int k, int E) {
    int j;

    /*Caso in cui non ci siano più elementi*/
    if (pos >= k) {
        if (valido(pos, sol, G, E)) {
            printf("( ");
            for (j = 0; j < k; j++)
                if (sol[j] != 0)
                    printf("%d ", G.nodi[j]);
            printf(")\n");
        }
        return;

    }
    sol[pos] = 0;
    powerset(pos + 1, G, sol, k, E);
    sol[pos] = 1;
    powerset(pos + 1, G, sol, k, E);
}

int valido(int pos, int *sol, grafo G, int E) {
    int j, i;
    /*Impongo val =1 in modo che, nel caso in cui non vi siano archi nel grafo,
    * l'insieme vuoto viene incluso come soluzione*/
    int val = 1;
    for (j = 0; j < E; j++) {
        val = 0;
        for (i = 0; i < pos && val == 0; i++) {
            //Controllo se dato un arco (u,v) almeno uno dei due appartiene al sottoinsieme sol
            if (sol[i] != 0)
                if (G.archi[j].ver1 == G.nodi[i] || G.archi[j].ver2 == G.nodi[i]) {
                    val = 1;
                }
        }
        //Se trovo un elemento non valido interrompo il controllo sugli altri archi
        if (val == 0) {
            return 0;
        }
    }

    return val;
}