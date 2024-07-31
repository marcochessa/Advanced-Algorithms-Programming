#include <stdio.h>
#include <stdlib.h>

#define K 5

typedef struct elemento_t {
    char nome[100];
    int tipo;
    int dirIn;
    int dirUs;
    int prec;
    int finale;
    float valore;
    int diff;
} elemento_t;


typedef struct diag_t {
    elemento_t *elementi[K];
    int len;
    float valore;
} diag_t;


int leggiEl(elemento_t **arrEl);

float calcolaPuntEsib(diag_t *esib);

float esibizione(int pos, diag_t *elencoDiag, diag_t *comboSol, diag_t *comboMigliore, int n, int k, float DP,
                 float pMax);

int diagonale(int pos, elemento_t *val, diag_t sol, diag_t *elencoSol, int n, int k, int count,
              float DD);

float calcolaPunt(diag_t sol, int n);

int esibValida(diag_t *esib);

int acAvInd(diag_t *esib);

int acrob(diag_t *esib);

void stampaEsib(diag_t *esib, int punt);

int main() {
    int N;
    float DD = 99;
    float DP = 250;
    int k, pos = 0;
    int count = 0;
    elemento_t *arrEl;
    diag_t sol;
    diag_t *elencoSol;

    //elencoSol = malloc(380 * sizeof(diag_t));

    N = leggiEl(&arrEl);

    for (k = 1; k < K; k++)
        count = diagonale(pos, arrEl, sol, elencoSol, N, 5, count, DD);

    int pMax = 0;
    diag_t comboSol[3];
    diag_t comboMigliore[3];
    comboMigliore[0].len=0;
    pMax = esibizione(pos, elencoSol, comboSol, comboMigliore, count, 3, DP, pMax);

    stampaEsib(comboMigliore, pMax);

    free(arrEl);
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
               &arrayTmp[i].dirUs, &arrayTmp[i].prec, &arrayTmp[i].finale, &arrayTmp[i].valore, &arrayTmp[i].diff);
    }
    fclose(fp);
    *arrEl = arrayTmp;
    return N;
}

int diagonale(int pos, elemento_t *val, diag_t sol, diag_t *elencoSol, int n, int k, int count, float DD) {
    int i;
    float puntCorr;
    if (pos >= k) {
        puntCorr = calcolaPunt(sol, k);
        if (puntCorr <= DD) {
            count++;
            elencoSol = realloc(elencoSol, count * sizeof(diag_t));
            for (i = 0; i < k; i++)
                elencoSol[count - 1].elementi[i] = sol.elementi[i];
            elencoSol[count - 1].len = k;
            elencoSol[count - 1].valore = puntCorr;
        }
        return count;
    }
    for (i = 0; i < n; i++) {
        if (pos == 0) {
            if (val[i].prec == 0) {
                sol.elementi[pos] = &val[i];
                count = diagonale(pos + 1, val, sol, elencoSol, n, k, count, DD);
            }
        } else if (val[i].finale == 1) {
            if (pos == k - 1)
                if (val[i].dirIn == sol.elementi[pos - 1]->dirUs) {
                    sol.elementi[pos] = &val[i];
                    count = diagonale(pos + 1, val, sol, elencoSol, n, k, count, DD);
                }
        } else if (val[i].dirIn == sol.elementi[pos - 1]->dirUs) {
            sol.elementi[pos] = &val[i];
            count = diagonale(pos + 1, val, sol, elencoSol, n, k, count, DD);
        }
    }
    return count;
}


float esibizione(int pos, diag_t *elencoDiag, diag_t *comboSol, diag_t *comboMigliore, int n, int k, float DP,
                 float pMax) {
    int i;
    if (pos >= k) {
        if (esibValida(comboSol)) {
            int pCor = calcolaPuntEsib(comboSol);
            if (pCor > pMax && pCor <= DP) {
                for (i = 0; i < k; i++) {
                    comboMigliore[i] = comboSol[i];
                }
                pMax = pCor;
            }
        }
        return pMax;
    }
    for (i = 0; i < n; i++) {
        comboSol[pos] = elencoDiag[i];
        pMax = esibizione(pos + 1, elencoDiag, comboSol, comboMigliore, n, k, DP, pMax);
    }
    return pMax;

}

float calcolaPunt(diag_t sol, int n) {
    float punt = 0;
    for (int i = 0; i < n; i++) {
        punt = punt + sol.elementi[i]->valore;
    }
    return punt;
}

int esibValida(diag_t *esib) {
    if (!acAvInd(esib))
        return 0;
    if (!acrob(esib))
        return 0;
    return 1;
}

int acAvInd(diag_t *esib) {
    int i;
    int av = 0, ind = 0;
    for (i = 0; i < esib[0].len; i++) {
        if (esib[0].elementi[i]->tipo == 2)
            av = 1;
        else if (esib[0].elementi[i]->tipo == 1)
            ind = 1;
        if (av == 1 && ind == 1)
            return 1;
    }
    for (i = 0; i < esib[1].len; i++) {
        if (esib[1].elementi[i]->tipo == 2)
            av = 1;
        else if (esib[1].elementi[i]->tipo == 1)
            ind = 1;
        if (av == 1 && ind == 1)
            return 1;
    }
    for (i = 0; i < esib[2].len; i++) {
        if (esib[2].elementi[i]->tipo == 2)
            av = 1;
        else if (esib[2].elementi[i]->tipo == 1)
            ind = 1;
        if (av == 1 && ind == 1)
            return 1;
    }
    return 0;

}

int acrob(diag_t *esib) {
    int i;

    for (i = 1; i < esib[0].len; i++) {
        if (esib[0].elementi[i]->tipo != 0 && esib[0].elementi[i - 1]->tipo != 0)
            return 1;
    }

    for (i = 1; i < esib[1].len; i++) {
        if (esib[1].elementi[i]->tipo != 0 && esib[1].elementi[i - 1]->tipo != 0)
            return 1;
    }


    for (i = 1; i < esib[2].len; i++) {
        if (esib[2].elementi[i]->tipo != 0 && esib[2].elementi[i - 1]->tipo != 0)
            return 1;
    }

    return 0;
}

float calcolaPuntEsib(diag_t *esib) {
    float punt = 0;
    punt = esib[0].valore + esib[1].valore;
    if (esib[2].elementi[esib[2].len - 1]->valore >= 8)
        punt = punt + (esib[2].valore * 1.5);
    else
        punt = punt + esib[2].valore;
    return punt;
}

void stampaEsib(diag_t *esib, int punt) {
    int i;

    if(esib[0].len==0){
        printf("Nessun insieme di diagonali rispetta le regole\n");
        return;
    }

    printf("Diagonale 1:\n");
    for (i = 0; i < esib[0].len; i++) {
        printf("\t%s", esib[0].elementi[i]->nome);
    }

    printf("\nDiagonale 2:\n");
    for (i = 0; i < esib[1].len; i++) {
        printf("\t%s", esib[1].elementi[i]->nome);
    }


    printf("\nDiagonale 3:\n");
    for (i = 0; i < esib[2].len; i++) {
        printf("\t%s", esib[2].elementi[i]->nome);
    }

    printf("\n***********\nPunteggio Totale: %d", punt);

}