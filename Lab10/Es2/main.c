#include <stdio.h>
#include <stdlib.h>

#define K 5
#define malus 50
#define soglia 7
#define secSoglia 10

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
} diag_t;

void ordinaMigliori(elemento_t *arrEl, int N);

int leggiEl(elemento_t **arrEl);

float esibizione(int n, elemento_t *arrEl, float PMaxDiag, float PMaxEsib);

int promettente(int n, elemento_t *arrEl, diag_t *diag, float *DP, float *DD, int *countAv, int *countInd,
                int *countSeq);

void aggiornaAppett(int n, elemento_t *arrEl, int componenti, int countSeq, int countAv, int countInd);

void finale(int n, elemento_t *arrEl, diag_t *diag, float *DP, float *DD);

void stampaEsib(diag_t diag1, diag_t diag2, diag_t diag3, int countAv, int countInd, int countSeq, float DD1,
                float DD2, float DD3, float pMax);

int main() {
    int N;
    int PMaxDiag = 7;
    int PMaxEsib = 30;

    elemento_t *arrEl;
    N = leggiEl(&arrEl);
    ordinaMigliori(arrEl, N);
    printf("(%s)\n\n\n", arrEl[0].nome);

    esibizione(N, arrEl, PMaxDiag, PMaxEsib);

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

float esibizione(int n, elemento_t *arrEl, float PMaxDiag, float PMaxEsib) {
    float PM=PMaxEsib;
    float DD1 = PMaxDiag;
    float DD2 = PMaxDiag;
    float DD3 = PMaxDiag;
    int i = 0;
    int fD1 = 1, fD2 = 1, fD3 = 1;
    int countAv = 0;
    int countInd = 0;
    int countSeq = 0;
    int componenti;
    diag_t diag1, diag2, diag3;
    diag1.len = diag2.len = diag3.len = 0;

    i = 0;
    while (i < 5) {
        if (fD1 == 1) {
            fD1 = promettente(n, arrEl, &diag1, &DD1, &PMaxEsib, &countAv, &countInd, &countSeq);
            componenti = diag1.len + diag2.len + diag3.len;
            aggiornaAppett(n, arrEl, componenti, countSeq, countAv, countInd);
        }
        if (fD2 == 1) {
            fD2 = promettente(n, arrEl, &diag2, &DD2, &PMaxEsib, &countAv, &countInd, &countSeq);
            componenti = diag1.len + diag2.len + diag3.len;
            aggiornaAppett(n, arrEl, componenti, countSeq, countAv, countInd);
        }
        if (fD3 == 1) {
            fD3 = promettente(n, arrEl, &diag3, &DD3, &PMaxEsib, &countAv, &countInd, &countSeq);
            componenti = diag1.len + diag2.len + diag3.len;
            aggiornaAppett(n, arrEl, componenti, countSeq, countAv, countInd);
        }
        i++;
    }
    if (fD1 == 0) {
        finale(n, arrEl, &diag1, &DD1, &PMaxEsib);
        aggiornaAppett(n, arrEl, componenti, countSeq, countAv, countInd);
    }
    if (fD2 == 0) {
        finale(n, arrEl, &diag2, &DD2, &PMaxEsib);
        aggiornaAppett(n, arrEl, componenti, countSeq, countAv, countInd);
    }
    if (fD3 == 0) {
        finale(n, arrEl, &diag3, &DD3, &PMaxEsib);
    }

    stampaEsib(diag1, diag2, diag3, countAv, countInd, countSeq, PMaxDiag-DD1, PMaxDiag-DD2, PMaxDiag-DD3, PM);
}

int promettente(int n, elemento_t *arrEl, diag_t *diag, float *DP, float *DD, int *countAv, int *countInd,
                int *countSeq) {
    int j;
    for (j = 0; j < n; j++) {
        if (arrEl[j].valoreIn <= *DP && arrEl[j].valoreIn <= *DD) {
            if (diag->len == 0) {
                if (arrEl[j].finale == 0) {
                    diag->elementi[diag->len] = &arrEl[j];
                    diag->len = diag->len + 1;
                    *DP = *DP - arrEl[j].valoreIn;
                    *DD = *DD - arrEl[j].valoreIn;
                    if (arrEl->tipo == 1)
                        *countAv = *countAv + 1;
                    else if (arrEl->tipo == 2)
                        *countInd = *countInd + 1;
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
                            *countAv = *countAv + 1;
                            if (diag->elementi[diag->len - 1]->tipo == 1 || diag->elementi[diag->len - 1]->tipo == 2)
                                *countSeq = *countSeq + 1;
                        } else if (arrEl->tipo == 1) {
                            *countInd = *countInd + 1;
                            if (diag->elementi[diag->len - 1]->tipo == 1 || diag->elementi[diag->len - 1]->tipo == 2)
                                *countSeq = *countSeq + 1;
                        }

                        return 1;
                    }
            } else if (diag->len == 4) {
                if (diag->elementi[diag->len - 1]->dirUs == arrEl[j].dirIn) {

                    diag->elementi[diag->len] = &arrEl[j];
                    diag->len = diag->len + 1;
                    *DP = *DP - arrEl[j].valoreIn;
                    *DD = *DD - arrEl[j].valoreIn;
                    if (arrEl->tipo == 2) {
                        *countAv = *countAv + 1;
                        if (diag->elementi[diag->len - 1]->tipo == 1 || diag->elementi[diag->len - 1]->tipo == 2)
                            *countSeq = *countSeq + 1;
                    } else if (arrEl->tipo == 1) {
                        *countInd = *countInd + 1;
                        if (diag->elementi[diag->len - 1]->tipo == 1 || diag->elementi[diag->len - 1]->tipo == 2)
                            *countSeq = *countSeq + 1;
                    }

                    return 1;
                }
            }
        }
    }
    return 0;
}

void finale(int n, elemento_t *arrEl, diag_t *diag, float *DP, float *DD) {
    int j;
    for (j = 0; j < n; j++)
        if (arrEl->valoreIn <= *DP && arrEl->valoreIn <= *DD) {
            if (diag->len == 0)
                if (arrEl[j].finale == 0) {
                    diag->elementi[diag->len] = &arrEl[j];
                    diag->len = diag->len + 1;
                    *DP = *DP - arrEl[j].valoreIn;
                    *DD = *DD - arrEl[j].valoreIn;
                }
        }
}

void aggiornaAppett(int n, elemento_t *arrEl, int componenti, int countSeq, int countAv, int countInd) {
    int i;

    /*Se gli elementi inseriti superano una determinata soglia ma non si hanno elementi avanti/indietro si penalizzano
     * gli elementi indietro/avanti*/
    if (componenti > soglia) {
        if (countAv > 0 && countInd == 0) {
            for (i = 0; i < n; i++) {
                if (arrEl[i].tipo == 2)
                    arrEl[i].valore = arrEl[i].valore - malus;
            }
        }
        if (countAv == 0 && countInd > 0) {
            for (i = 0; i < n; i++) {
                if (arrEl[i].tipo == 1)
                    arrEl[i].valore = arrEl[i].valore - malus;
            }
        }

        /*Se gli elementi inseriti superano una determinata soglia ma non si hanno elementi in sequenza si penalizzano
         * gli elementi di transizione in modo da avere maggiori possibilità di arrivare a completare una seguenza*/
        if (componenti > secSoglia) {
            if (countSeq == 0)
                for (i = 0; i < n; i++) {
                    if (arrEl[i].tipo == 0)
                        arrEl[i].valore = arrEl[i].valore - malus;
                }
        }

        /*Viene effettuato l'ordinamento in base ai nuovi valori degli elementi*/
        ordinaMigliori(arrEl, n);
    }


}

void stampaEsib(diag_t diag1, diag_t diag2, diag_t diag3, int countAv, int countInd, int countSeq, float DD1,
                float DD2, float DD3, float pMax) {
    int i;
    float punt=0;
    float bonus;
    if (countAv == 0 || countInd == 0 || countSeq == 0) {
        printf("Nessuna combinazione valida trovata\n");
        return;
    }
    printf("Diagonale 1: pt. %.2f\n\t", DD1);
    for (i = 0; i < diag1.len; i++) {
        printf("%s, ", diag1.elementi[i]);
    }
    punt=punt+DD1;

    printf("\nDiagonale 2: pt. %.2f\n\t", DD2);
    for (i = 0; i < diag2.len; i++) {
        printf("%s, ", diag2.elementi[i]);
    }

    punt=punt+DD2;


    printf("\nDiagonale 3: pt. %.2f\n\t", DD3);
    for (i = 0; i < diag3.len; i++) {
        printf("%s, ", diag3.elementi[i]);
    }

    punt=punt+DD3;

    if (DD3 > 8) {
        bonus = DD3 / 2;
        if (punt + bonus <= pMax)
            printf("\nPunteggio Totale: %.2f con bonus: %.2f\n", punt, bonus);
    }


    printf("\nPunteggio Totale: %.2f", punt);
}