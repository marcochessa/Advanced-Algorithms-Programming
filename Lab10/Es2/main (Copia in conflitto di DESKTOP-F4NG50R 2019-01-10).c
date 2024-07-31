#include <stdio.h>
#include <stdlib.h>

#define K 5
#define malus 50


typedef struct elemento_t {
    char nome[100];
    int tipo;
    int dirIn;
    int dirUs;
    int prec;
    int finale;
    float valore;
    float valoreIn;
    int diff;
} elemento_t;
typedef struct diag_t {
    elemento_t *elementi[K];
    int len;
    float valore;
} diag_t;

void ordinaMigliori(elemento_t *arrEl, int N);

int leggiEl(elemento_t **arrEl);

float esibizione(int n, elemento_t *arrEl, float DP, float DD);

int promettente(int n, elemento_t *arrEl, diag_t *diag, float *DP, float *DD);

void aggiornaAppett(elemento_t *arrEl, float DP, float DD, int i);

float riempiDiag(elemento_t *arrEl, diag_t diag1, int len, float DP, float DD);

int main() {
    int N;
    int DD = 99;
    int DP = 250;

    elemento_t *arrEl;
    N = leggiEl(&arrEl);
    ordinaMigliori(arrEl, N);
    printf("(%s)", arrEl[0].nome);


    return 0;
}

int leggiEl(elemento_t **arrEl) {
    FILE *fp;
    int N;
    elemento_t *arrayTmp;
    fp = fopen("elementi.txt", "r");
    if (fp == NULL) {
        printf("Errore nella lettura\n");
        exit(1);
    }
    fscanf(fp, "%d", &N);
    arrayTmp = malloc(N * sizeof(elemento_t));
    for (int i = 0; i < N; i++) {
        fscanf(fp, "%s %d %d %d %d %d %f %d", arrayTmp[i].nome, &arrayTmp[i].tipo, &arrayTmp[i].dirIn,
               &arrayTmp[i].dirUs, &arrayTmp[i].prec, &arrayTmp[i].finale, &arrayTmp[i].valoreIn, &arrayTmp[i].diff);
        arrayTmp[i].valore = arrayTmp[i].valoreIn;
    }
    fclose(fp);
    *arrEl = arrayTmp;
    return N;
}


void ordinaMigliori(elemento_t *arrEl, int N) {
    int i, j;
    elemento_t key;
    for (i = 1; i < N; i++) {
        key = arrEl[i];
        j = i - 1;

        /*Ordino gli elementi per valore dell'elemento decrescente*/
        while (j >= 0 && arrEl[j].valore < key.valore) {
            arrEl[j + 1] = arrEl[j];
            j = j - 1;
        }
        arrEl[j + 1] = key;
    }

}

float esibizione(int n, elemento_t *arrEl, float DP, float DD) {
    float punt = DD;
    float DP1 = DP;
    float DP2 = DP;
    float DP3 = DP;
    int i = 0;
    int val = 1;
    int fD1 = 1, fD2 = 1, fD3 = 1;
    diag_t diag1, diag2, diag3;
    int tip = 0;

    elemento_t *elD1[n], *elD2[n], *elD3[n];

    for (i = 0; i < n; i++) {
        elD1[i] = elD2[i] = elD3[i] = &arrEl[i];
    }

    i = 0;
    while (i < 5 && val == 1) {
        if (fD1 == 1) {
            fD1 = promettente(n, arrEl, &diag1, &DP1, &DD);
            aggiornaAppett(elD1, DP1, DD, i);
        }
        if (fD2 == 1) {
            fD2 = promettente(n, arrEl, &diag2, &DP2, &DD);
            aggiornaAppett(elD2, DP2, DD, i);
        }
        if (fD3 == 1) {
            fD3 = promettente(n, arrEl, &diag3, &DP3, &DD);
            aggiornaAppett(elD3, DP3, DD, i);
        }
    }
    if (fD1 == 0) {
        finale(n, arrEl, &diag1, &DP1, &DD);
        aggiornaAppett(elD1, DP1, DD, i);
    }
    if (fD2 == 0) {
        finale(n, arrEl, &diag2, &DP2, &DD);
        aggiornaAppett(elD2, DP2, DD, i);
    }
    if (fD3 == 0) {
        finale(n, arrEl, &diag3, &DP3, &DD);
    }
}

int
promettente(int n, elemento_t *arrEl, diag_t *diag, float *DP, float *DD, int *countAv, int *countInd, int *countSeq) {
    int j;
    for (j = 0; j < n; j++) {
        if (arrEl->valoreIn <= *DP && arrEl->valoreIn <= *DD) {
            if (diag->len == 0) {
                if (arrEl[j].finale == 0) {
                    diag->elementi[diag->len] = &arrEl[j];
                    diag->len = diag->len + 1;
                    *DP = *DP - arrEl[j].valoreIn;
                    *DD = *DD - arrEl[j].valoreIn;
                    if (arrEl->tipo == 1)
                        *countAv++;
                    else if (arrEl->tipo == 2)
                        *countInd++;
                    return 1;

                }
            } else if (diag->len < 4) {
                if (diag->elementi[diag->len - 1]->dirUs == arrEl[j].dirIn)
                    if (arrEl[j].finale == 0) {
                        diag->elementi[diag->len] = &arrEl[j];
                        diag->len = diag->len + 1;
                        *DP = *DP - arrEl[j].valoreIn;
                        *DD = *DD - arrEl[j].valoreIn;
                        if (arrEl->tipo == 2) {
                            *countAv++;
                            if (diag->elementi[diag->len - 1]->tipo == 1 || diag->elementi[diag->len - 1]->tipo == 2)
                                *countSeq++;
                        } else if (arrEl->tipo == 1) {
                            *countInd++;
                            if (diag->elementi[diag->len - 1]->tipo == 1 || diag->elementi[diag->len - 1]->tipo == 2)
                                *countSeq++;
                        }

                        return 1;
                    }
            } else if (diag->len == 4) {
                diag->elementi[diag->len] = &arrEl[j];
                diag->len = diag->len + 1;
                *DP = *DP - arrEl[j].valoreIn;
                *DD = *DD - arrEl[j].valoreIn;
                return 1;
            }
        }
    }
    return 0;
}

void
aggiornaAppett(int n, elemento_t **arrEl, diag_t diag, float DD, float DP, int *countAv, int *countInd, int *countSeq) {
    int i;
    if (countAv > 0 && countInd == 0) {
        for (i = 0; i < n; i++) {
            if (arrEl[i]->tipo == 2)
                arrEl[i]->valore = arrEl[i]->valore - malus;
        }
    }
    if (countAv == 0 && countInd > 0) {
        for (i = 0; i < n; i++) {
            if (arrEl[i]->tipo == 1)
                arrEl[i]->valore = arrEl[i]->valore - malus;
        }
    }

    }