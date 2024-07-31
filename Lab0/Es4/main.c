#include <stdio.h>

int main() {
    char nome[21];
    int M[20][20];
    int N[20][20];
    int somma;
    double count;
    int MAX = -1;//<-- Min Value
    int Mi, Mj;
    int nr, nc, g, starti, startj;
    FILE *fp;
    printf("Inserisci nome file\n");
    scanf("%s", nome);
    fp = fopen(nome, "r");
    if (fp == NULL) {
        printf("Impossibile aprire");
        return 1;
    }
    fscanf(fp, "%d%d", &nr, &nc);
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            if (!feof(fp)) {
                fscanf(fp, "%d", &M[i][j]);
            }
        }
    }
    //CHIUDO IL FILE
    fclose(fp);

    printf("Inserisci la grandezza matriciale");
    scanf("%d", &g);

    while (g > 1 && g < nr && g < nc) {
        starti = 0;
        startj = 0;
        somma = 0;
        for (int K = 0; K < ((nr / g) + (nc / g)); K++) {
            for (int i = starti; i < starti + g; i++) {
                for (int j = startj; j < startj + g; j++) {
                    printf("%d", M[i][j]);
                    somma = somma + M[i][j];
                }
                printf("\n");
            }
            if (somma > MAX) {
                MAX = somma;
                Mi = starti;
                Mj = startj;
            }
            starti += g;
            startj += g;
        }
        //MEMORIZZO LA MATRICE CON SOMMA MAGGIORE
        count = 0;
        for (int q = 0; q < g; q++) {
            for (int p = 0; p < g; p++) {
                N[q][p] = M[q + Mi][p + Mj];
                count = g;
            }
        }
    }

    printf("La matrice trovata con dimensione maggiore è: \n");
    for (int q = 0; q < count; q++) {
        for (int p = 0; p < count; p++) {
            N[q][p];
        }
    }

    return 0;
}