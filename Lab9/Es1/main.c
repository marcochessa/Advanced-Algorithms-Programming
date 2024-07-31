#include <stdio.h>
#include <malloc.h>

typedef struct att {
    int tInizio;
    int tFine;
} att;

void attSel(att val[], int N);

int stampaAtt(att val[], int P[], int i, int durata);

void BubbleSort(att v[], int N);

int main() {
    int N = 7;

    att v[7];

    v[0].tInizio = 0;
    v[0].tFine = 0;

    v[1].tInizio = 1;
    v[1].tFine = 2;

    v[2].tInizio = 2;
    v[2].tFine = 4;

    v[3].tInizio = 2;
    v[3].tFine = 5;

    v[4].tInizio = 3;
    v[4].tFine = 5;

    v[5].tInizio = 5;
    v[5].tFine = 7;

    v[6].tInizio = 6;
    v[6].tFine = 8;

    //Le attività sono ordinate in ordine crescente di tempo di fine, altrimenti si procede all'ordinamento
    //BubbleSort(v,6);

    attSel(v, N);
    return 0;
}

void attSel(att val[], int N) {
    int i, j, lenSeq = 1;
    int *L, *P, last = 1;
    int durata = 0;

    L = malloc(N * sizeof(int));
    P = malloc(N * sizeof(int));

    //Creo una attività fittizia e imposto L[0] a 0 in modo da non considerarla
    L[0] = 0;
    P[0] = -1;
    for (i = 1; i < N; i++) {
        L[i] = 1;
        P[i] = 0;

        for (j = 0; j < i; j++)
            if ((val[j].tFine <= val[i].tInizio) && (L[i] < 1 + L[j])) {
                L[i] = 1 + L[j];
                P[i] = j;
            } else if ((val[j].tFine > val[i].tInizio)) {
                //Visto che le attività sono ordinate, se un'attività non è compatibile posso terminare il ciclo
                break;
            }
        if (lenSeq < L[i]) {
            lenSeq = L[i];
            last = i;
        }
    }
    printf("L'insieme di lunghezza %d e':\n", lenSeq);
    durata = stampaAtt(val, P, last, durata);
    printf("\n---------------------------\n");
    printf("La durata complessiva e': %d", durata);

    free(L);
    free(P);
}

int stampaAtt(att val[], int P[], int i, int durata) {
    if (P[i] == 0) {
        //Individuata la prima attività ne calcolo la durata e la assegno alla durata complessiva
        durata = val[i].tFine - val[i].tInizio;
        printf("[%d , %d] ", val[i].tInizio, val[i].tFine);
        return durata;
    }

    durata = stampaAtt(val, P, P[i], durata);

    //Aggiorno la durata complessiva sommando le durate delle attività rimanenti
    durata = durata + (val[i].tFine - val[i].tInizio);
    printf("[%d , %d] ", val[i].tInizio, val[i].tFine);
    return durata;

}

void BubbleSort(att v[], int N) {
    int i, j, l = 0, r = N - 1;
    att temp;
    for (i = l; i < r; i++) {
        for (j = l; j < r - i + l; j++)
            if (v[j].tFine > v[j + 1].tFine) {
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
    }
    return;
}