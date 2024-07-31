#include <stdio.h>
#include <malloc.h>

int **malloc2dR(int nr, int nc);

void malloc2dP(int ***m, int nr, int nc);

void riempiMatrice(int **m, int nr, int nc, FILE *fp);

void stampaVettore(int *v, int n);

void separa(int **mat, int nr, int nc, int *vBianchi, int *vNeri);

void free2d(int**m, int nr);

int main() {
    int **m;
    int *vBianchi, *vNeri;
    FILE *fp;
    int nr, nc;

    fp = fopen("matrici.txt", "r");
    if (fp == NULL) {
        printf("Errore nella lettura");
        return 1;
    }
    fscanf(fp, "%d %d", &nr, &nc);

    m = malloc2dR(nr, nc);
    //OPPURE
    //malloc2dP(&m, nr, nc);

    riempiMatrice(m, nr, nc, fp);
    fclose(fp);

    separa(m, nr, nc, vBianchi, vNeri);

    free2d(m, nr);

    return 0;
}

int **malloc2dR(int nr, int nc) {
    int **m;
    int i;
    m = malloc(nr * sizeof(int *));
    for (i = 0; i < nr; i++) {
        m[i] = malloc(nc * sizeof(int));
    }
    return m;
}

void malloc2dP(int ***m, int nr, int nc) {
    int **mp;
    int i;
    mp = malloc(nr * sizeof(int *));
    for (i = 0; i < nr; i++) {
        mp[i] = malloc(nc * sizeof(int));
    }
    *m = mp;
}

void riempiMatrice(int **m, int nr, int nc, FILE *fp) {
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            fscanf(fp, "%d", &m[i][j]);
        }
    }
}

void separa(int **mat, int nr, int nc, int *vBianchi, int *vNeri) {
    int nB, n, B = 0, N = 0;
    int alterna = 1;

    /*Si considera bianca la casella in alto a sinistra:
     * nel caso di una scacchiera con caselle dispari avrò n caselle nere ed n+1 caselle bianche
     */
    int dispari = (nc * nr) % 2;
    n = (nc * nr) / 2;

    if (dispari)
        nB = n + 1;
    else
        nB = n;
    vBianchi = malloc(nB * sizeof(int));
    vNeri = malloc(n * sizeof(int));

    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            if (alterna > 0) {
                vBianchi[B] = mat[i][j];
                B++;
            } else {
                vNeri[N] = mat[i][j];
                N++;
            }
            alterna = alterna * -1;
        }
    }
    printf("Dati contenuti nelle caselle bianche:\n");
    stampaVettore(vBianchi, nB);
    printf("Dati contenuti nelle caselle nere:\n");
    stampaVettore(vNeri, n);

    //Libero la memoria allocata per i due vettori
    free(vBianchi);
    free(vNeri);
}

void stampaVettore(int *v, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void free2d(int**m, int nr){
    int i;
    for(i=0;i<nr;i++){
        free(m[i]);
    }
    free(m);
}