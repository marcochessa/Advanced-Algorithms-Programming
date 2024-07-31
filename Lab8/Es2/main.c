#include <stdio.h>
#include <stdlib.h>

typedef struct tessera_t {
    char colore;
    int valore;
} tessera_t;

typedef struct tassello_t {
    tessera_t oriz;
    tessera_t vert;
    int usato;
    int ind;
} tassello_t;

int rilevaTessere(tassello_t **tasselli);

void allocaScacchiera(tassello_t ***scacchiera, int R, int C);

void riempiScacchiera(tassello_t *tasselli, tassello_t ***scacchiera, int *R, int *C);

void liberaMemoria(tassello_t *tasselli, tassello_t **scacchiera, tassello_t **scacMax, int r);


int scacchieraMax(int posR, int posC, tassello_t **scacchiera, tassello_t **scacMax, tassello_t *tasselli, int R,
                  int C, int N, int valoreMax);

int calcolaValore(tassello_t **scacchiera, int R, int C);

void copiaScacchiera(tassello_t **scacchiera, int R, int C, tassello_t **scacMax);

void stampaScacchiera(tassello_t **scacchiera, int R, int C);

int main() {
    tassello_t *tasselli;
    tassello_t **scacchiera;
    tassello_t **scacMax;
    int R, C;
    int N;
    int valoreMax = 0;

    N = rilevaTessere(&tasselli);
    riempiScacchiera(tasselli, &scacchiera, &R, &C);
    allocaScacchiera(&scacMax, R, C);

    scacMax = malloc(R * sizeof(tassello_t *));
    for (int i = 0; i < R; i++)
        scacMax[i] = malloc((C * sizeof(tassello_t)));

    printf("Scacchiera iniziale:\n");
    stampaScacchiera(scacchiera, R, C);

    valoreMax = scacchieraMax(0, 0, scacchiera, scacMax, tasselli, R, C, N, valoreMax);

    printf("**********************************\n");
    printf("Scacchiera migliore:\n");
    stampaScacchiera(scacMax, R, C);

    printf("Il valore Max e': %d", valoreMax);

    liberaMemoria(tasselli, scacchiera, scacMax, R);

    return 0;
}

int rilevaTessere(tassello_t **tasselli) {
    FILE *fp;
    tassello_t *tasTmp;
    int N;
    fp = fopen("tiles.txt", "r");
    if (fp == NULL) {
        printf("Impossibile aprire file\n");
        exit(1);
    }
    fscanf(fp, "%d", &N);
    tasTmp = malloc(N * sizeof(tassello_t));
    for (int i = 0; i < N; i++) {
        fscanf(fp, " %c %d %c %d", &tasTmp[i].oriz.colore, &tasTmp[i].oriz.valore,
               &tasTmp[i].vert.colore, &tasTmp[i].vert.valore);
        //Imposto la tessere non usate
        tasTmp[i].usato = 0;
        tasTmp[i].ind = i;
    }
    fclose(fp);
    *tasselli = tasTmp;
    return N;
}

void liberaMemoria(tassello_t *tasselli, tassello_t **scacchiera, tassello_t **scacMax, int r) {
    free(tasselli);
    for (int i = 0; i < r; i++) {
        free(scacchiera[i]);
        free(scacMax[i]);
    }
    free(scacchiera);
    free(scacMax);
    free(tasselli);
}

void riempiScacchiera(tassello_t *tasselli, tassello_t ***scacchiera, int *R, int *C) {
    FILE *fp;
    tassello_t **scacTmp;
    tessera_t vuota;
    vuota.colore = '-';
    vuota.valore = -1;
    int ind, rot;
    fp = fopen("board.txt", "r");
    if (fp == NULL) {
        printf("Impossibile aprire file\n");
        exit(1);
    }
    fscanf(fp, "%d %d", R, C);
    allocaScacchiera(&scacTmp, *R, *C);

    for (int i = 0; i < *R; i++) {
        for (int j = 0; j < *C; j++) {
            fscanf(fp, "%d/%d", &ind, &rot);
            if (ind >= 0) {
                if (rot) {
                    scacTmp[i][j].vert = tasselli[ind].oriz;
                    scacTmp[i][j].oriz = tasselli[ind].vert;
                } else
                    scacTmp[i][j] = tasselli[ind];
                tasselli[ind].usato = 1;
                scacTmp[i][j].usato = 1;
            } else {
                scacTmp[i][j].oriz = vuota;
                scacTmp[i][j].vert = vuota;
                scacTmp[i][j].usato = 0;
            }
        }
    }
    *scacchiera = scacTmp;;
}

void allocaScacchiera(tassello_t ***scacchiera, int R, int C) {
    tassello_t **scacTmp;
    scacTmp = malloc(R * sizeof(tassello_t *));
    for (int i = 0; i < R; i++)
        scacTmp[i] = malloc((C * sizeof(tassello_t)));
    *scacchiera = scacTmp;
}

int scacchieraMax(int posR, int posC, tassello_t **scacchiera, tassello_t **scacMax, tassello_t *tasselli, int R,
                  int C, int N, int valoreMax) {
    int i;
    int valore;


    if (posR >= R) {
        valore = calcolaValore(scacchiera, R, C);
        if (valore > valoreMax) {
            /*PER VERIFICA*/
            /*{
                stampaScacchiera(scacchiera, R, C);
                printf("Max temp:%d\n______\n", valore);
            }*/
            copiaScacchiera(scacchiera, R, C, scacMax);
            valoreMax = valore;
        }
        return valoreMax;
    }

    for (i = 0; i < N; i++) {
        if (tasselli[i].usato == 0) {
            if (scacchiera[posR][posC].usato == 0) {
                tasselli[i].usato = 1;

                scacchiera[posR][posC].vert = tasselli[i].vert;
                scacchiera[posR][posC].oriz = tasselli[i].oriz;

                if (posC < C - 1)
                    valoreMax = scacchieraMax(posR, posC + 1, scacchiera, scacMax, tasselli, R, C, N, valoreMax);
                else
                    valoreMax = scacchieraMax(posR + 1, 0, scacchiera, scacMax, tasselli, R, C, N, valoreMax);

                scacchiera[posR][posC].oriz = tasselli[i].vert;
                scacchiera[posR][posC].vert = tasselli[i].oriz;

                if (posC < C - 1)
                    valoreMax = scacchieraMax(posR, posC + 1, scacchiera, scacMax, tasselli, R, C, N, valoreMax);
                else
                    valoreMax = scacchieraMax(posR + 1, 0, scacchiera, scacMax, tasselli, R, C, N, valoreMax);

                tasselli[i].usato = 0;
            } else {
                if (posC < C - 1)
                    valoreMax = scacchieraMax(posR, posC + 1, scacchiera, scacMax, tasselli, R, C, N, valoreMax);
                else
                    valoreMax = scacchieraMax(posR + 1, 0, scacchiera, scacMax, tasselli, R, C, N, valoreMax);
            }
        }
    }
    return valoreMax;
}

int calcolaValore(tassello_t **scacchiera, int R, int C) {
    int i, j;
    int valore = 0;
    int valoreRiga = 0, valoreColonna = 0;

    for (i = 0; i < R; i++) {
        valoreRiga = scacchiera[i][0].oriz.valore;
        for (j = 0; j < C - 1; j++) {
            if (scacchiera[i][j].oriz.colore == scacchiera[i][j + 1].oriz.colore)
                valoreRiga = valoreRiga + scacchiera[i][j + 1].oriz.valore;
            else {
                valoreRiga = 0;
                break;
            }
        }
        valore = valore + valoreRiga;
    }

    for (i = 0; i < C; i++) {
        valoreColonna = scacchiera[0][i].vert.valore;
        for (j = 0; j < R - 1; j++) {
            if (scacchiera[j][i].vert.colore == scacchiera[j + 1][i].vert.colore)
                valoreColonna = valoreColonna + scacchiera[j + 1][i].vert.valore;
            else {
                valoreColonna = 0;
                break;
            }
        }
        valore = valore + valoreColonna;
    }

    return valore;
}

void copiaScacchiera(tassello_t **scacchiera, int R, int C, tassello_t **scacMax) {
    int i, j;
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            scacMax[i][j] = scacchiera[i][j];
        }
    }
}

void stampaScacchiera(tassello_t **scacchiera, int R, int C) {
    int i, j;
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++)
            printf("[V: %c %d O: %c %d] ", scacchiera[i][j].vert.colore, scacchiera[i][j].vert.valore,
                   scacchiera[i][j].oriz.colore, scacchiera[i][j].oriz.valore);
        printf("\n");
    }
    printf("\n");

}
