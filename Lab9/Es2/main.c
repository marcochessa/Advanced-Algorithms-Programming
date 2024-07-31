#include <stdio.h>
#include <malloc.h>

int *****malloc5dR(int nZ, int nS, int nR, int nT);

void free5d(int *****soluzione, int nZ, int nS, int nR, int nT);

int fX(int *pietre, int *****soluzione);

int massimo(int n1, int n2);

int fZ(int *pietre, int *****soluzione);

int fS(int *pietre, int *****soluzione);

int fR(int *pietre, int *****soluzione);

int fT(int *pietre, int *****soluzione);

int main() {
    int *****soluzione;
    int pietre[4];
    int nZ = 39, nS = 46, nR = 48, nT = 35; //RISULTATO -> 156
    soluzione = malloc5dR(nZ + 1, nS + 1, nR + 1, nT + 1);

    //Pietre contiene, il numero di pietre disponibili, rispettivamente di Zaffiri, Smeraldi, Rubino, Topazio
    pietre[0] = nZ;
    pietre[1] = nS;
    pietre[2] = nR;
    pietre[3] = nT;

    fX(pietre, soluzione);

    free5d(soluzione, nZ + 1, nS + 1, nR + 1, nT + 1);

    printf("Fine\n");
    return 0;
}

int *****malloc5dR(int nZ, int nS, int nR, int nT) {
    int *****p;
    int i, j, k, t, z;
    p = malloc(nZ * sizeof(int *));
    for (i = 0; i < nZ; i++) {
        p[i] = malloc(nS * sizeof(int *));
        for (j = 0; j < nS; j++) {
            p[i][j] = malloc(nR * sizeof(int *));
            for (k = 0; k < nR; k++) {
                p[i][j][k] = malloc(nT * sizeof(int));
                for (t = 0; t < nT; t++) {
                    p[i][j][k][t] = malloc(4 * sizeof(int));
                    //Mentre alloco la matrice imposto tutti i valori a -1
                    for (z = 0; z < 4; z++)
                        p[i][j][k][t][z] = -1;
                }

            }
        }
    }
    return p;
}

void free5d(int *****soluzione, int nZ, int nS, int nR, int nT) {
    int i, j, k, t;
    for (i = 0; i < nZ; i++) {
        for (j = 0; j < nS; j++) {
            for (k = 0; k < nR; k++) {
                for (t = 0; t < nT; t++)
                    free(soluzione[i][j][k][t]);
            }
            free(soluzione[i][j]);
        }
        free(soluzione[i]);
    }
    free(soluzione);
}


int massimo(int n1, int n2) {
    if (n1 > n2)
        return n1;
    if (n2 > n1)
        return n2;
    return n1;
}

int fZ(int *pietre, int *****soluzione) {
    //Se ho finito le pietre di un determinato tipo ritorno 0
    if (pietre[0] == 0) {
        return 0;
    }
    //Se ho già calcolato il valore della soluzione in una determinata posizione lo ritorno
    if (soluzione[pietre[0]][pietre[1]][pietre[2]][pietre[3]][0] != -1)
        return soluzione[pietre[0]][pietre[1]][pietre[2]][pietre[3]][0];

    /*Calcolo il massimo ricorsivamente, rispettando le regole di composizione della collana, una volta trovata la
     *soluzione migliore incremento il massimo*/
    int max;
    pietre[0]--;
    max = massimo(fZ(pietre, soluzione), fR(pietre, soluzione));
    pietre[0]++;
    soluzione[pietre[0]][pietre[1]][pietre[2]][pietre[3]][0] = max + 1;

    return max + 1;

}

int fS(int *pietre, int *****soluzione) {
    if (pietre[1] == 0) {
        return 0;
    }
    if (soluzione[pietre[0]][pietre[1]][pietre[2]][pietre[3]][1] != -1)
        return soluzione[pietre[0]][pietre[1]][pietre[2]][pietre[3]][1];

    pietre[1]--;
    int max;
    max = massimo(fS(pietre, soluzione), fT(pietre, soluzione));
    pietre[1]++;
    soluzione[pietre[0]][pietre[1]][pietre[2]][pietre[3]][1] = max + 1;

    return max + 1;

}

int fR(int *pietre, int *****soluzione) {
    if (pietre[2] == 0) {
        return 0;
    }
    if (soluzione[pietre[0]][pietre[1]][pietre[2]][pietre[3]][2] != -1)
        return soluzione[pietre[0]][pietre[1]][pietre[2]][pietre[3]][2];

    int max;
    pietre[2]--;
    max = massimo(fS(pietre, soluzione), fT(pietre, soluzione));
    pietre[2]++;
    soluzione[pietre[0]][pietre[1]][pietre[2]][pietre[3]][2] = max + 1;

    return max + 1;

}

int fT(int *pietre, int *****soluzione) {
    if (pietre[3] == 0) {
        return 0;
    }
    if (soluzione[pietre[0]][pietre[1]][pietre[2]][pietre[3]][3] != -1)
        return soluzione[pietre[0]][pietre[1]][pietre[2]][pietre[3]][3];

    int max;
    pietre[3]--;
    max = massimo(fZ(pietre, soluzione), fR(pietre, soluzione));
    pietre[3]++;
    soluzione[pietre[0]][pietre[1]][pietre[2]][pietre[3]][3] = 1 + max;

    return max + 1;

}

int fX(int *pietre, int *****soluzione) {
    int max;
    int zaf = fZ(pietre, soluzione);
    int sme = fS(pietre, soluzione);
    int rub = fR(pietre, soluzione);
    int top = fT(pietre, soluzione);

    max = massimo(massimo(zaf, sme), massimo(rub, top));
    printf("La collana ha lunghezza massima: %d\n", max);

    printf("_________\n**per completezza**\n");
    printf("Iniziante con zaffiro %d\n", zaf);
    printf("Iniziante con smeraldo %d\n", sme);
    printf("Iniziante con rubino %d\n", rub);
    printf("Iniziante con topazio %d\n", top);
}

