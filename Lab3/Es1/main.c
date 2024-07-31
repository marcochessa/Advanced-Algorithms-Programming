#include <stdio.h>

#define K 50

int leggiMatrice(int M[][K], int MAXR, int *nr, int *nc);

int riconosciRegione(int M[][K], int nr, int nc, int r, int c, int *b, int *h);


int main() {
    /*Trascurando i problemi dell'esercizio presente nel Lab02 e quindi,
     * parzialmente la soluzione da me adottata in esso, provvederò a
     * risolvere escusivamente le problematiche relative ai problemi dell'esercizio
     * corrente
     */

    int M[K][K] = {0};

    int r, c;
    int nr = 0, nc = 0;
    int b = 0, h = 0;

    //Il passaggio seguente è superfluo ma viene svolto per rispettare il prototipo dato
    int MAXR = K;

    if (leggiMatrice(M, MAXR, &nr, &nc)) {
        return 1;
    }

    printf("Inserisci riga e colonna dove effettuare la ricerca\n");
    scanf("%d %d", &r, &c);
    if (riconosciRegione(M, nr, nc, r, c, &b, &h)) {
        printf("Il rettangolo con estremi (%d,%d) ha base %d e altezza %d", r, c, b, h);
    } else {
        printf("Nelle coordinate scelte non si ha un'estremo superiore sinistro");
    }

    return 0;
}


int leggiMatrice(int M[][K], int MAXR, int *nr, int *nc) {
    FILE *fp;
    int i, j;
    int R, C;

    fp = fopen("mappa.txt", "r");

    if (fp == NULL) {
        printf("Errore nella lettura del file");
        return 1;
    }

    fscanf(fp, "%d %d", &R, &C);

    if (R <= MAXR) {
        *nr = R;
    } else {
        printf("Numero di righe superiore a quelle permesse");
        return 1;
    }

    if (C <= MAXR) {
        *nc = C;
    } else {
        printf("Numero di colonne superiore a quelle permesse");
        return 1;
    }


    for (i = 0; i < *nr; i++) {
        for (j = 0; j < *nc; j++) {
            fscanf(fp, "%d", &M[i][j]);
        }
    }

    fclose(fp);

    return 0;

}

int riconosciRegione(int M[][K], int nr, int nc, int r, int c, int *b, int *h) {
    int i, j;
    int valido = 1;
    if (M[r][c] == 1) {
        if (r != 0) {
            if (M[r - 1][c] == 1) {
                return 0;
            }
        }
        if (c != 0) {
            if (M[r][c - 1] == 1) {
                return 0;
            }
        }

        //Appurato che le coordinate indicato un estremo superiore sinistro calcolo la base e l'altezza
        for (i = r; i < nr - r && valido == 1; i++) {
            if (M[i][c] == 1) {
                *h = *h + 1;
            } else {
                valido = 0;
            }
        }
        valido = 1;
        for (j = c; j < nc - r && valido == 1; j++) {
            if (M[r][j] == 1) {
                *b = *b + 1;
            } else {
                valido = 0;
            }
        }

    } else {
        return 0;
    }
    return 1;
}
