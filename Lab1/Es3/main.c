#include <stdio.h>
#include <mem.h>
#include <windef.h>

#define L 21
#define K 30

int traduci(char stringa[], int dati[4], int nc, int nr);

void ruota(int M[K][K], int dati[4], int nr, int nc);

void ruotaV(int V[], int N, int dir, int pos);

int main() {
    char nomef[L];
    FILE *fp;
    int M[K][K];
    int nc, nr;
    int i, j;
    int continua;

    char stringa[101];
    int dati[4];

    printf("Inserisci nome file\n");
    gets(nomef);

    fp = fopen(nomef, "r");
    if (fp == NULL) {
        printf("Impossibile aprire");
        return 1;
    }

    fscanf(fp, "%d %d", &nc, &nr);

    for (i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            fscanf(fp, "%d", &M[i][j]);
        }
    }

    printf("Inserisci stringa: <selettore> <indice> <direzione> <posizioni>\n");

    gets(stringa);
    continua = traduci(stringa, dati, nc, nr);
    while (continua) {
        ruota(M, dati, nr, nc);

        for (i = 0; i < nr; i++) {
            for (j = 0; j < nc; j++) {
                printf("%d ", M[i][j]);
            }
            printf("\n");
        }

        printf("\nInserisci stringa: <selettore> <indice> <direzione> <posizioni> oppure fine\n");

        gets(stringa);
        continua = traduci(stringa, dati, nc, nr);
    }

    return 0;
}

int traduci(char stringa[], int dati[4], int nc, int nr) {

    char selettore[8];
    int indice;
    char direzione[9];
    int posizioni;
    sscanf(stringa, "%s %d %s %d", selettore, &indice, direzione, &posizioni);
    if (strcmp(selettore, "fine") == 0) {
        return 0;
    } else {
        if (strcmp(selettore, "riga") == 0) {
            dati[0] = 0;

            if (0 <= indice && indice < nr) {
                dati[1] = indice;
            } else {
                printf("Dati inseriti non validi");
                return 0;
            }

            if (strcmp(direzione, "destra") == 0) {
                dati[2] = -1;
            } else if (strcmp(direzione, "sinistra") == 0) {
                dati[2] = 1;
            } else {
                printf("Dati inseriti non validi");
                return 0;
            }


        } else if (strcmp(selettore, "colonna") == 0) {
            dati[0] = 1;

            if (0 <= indice && indice < nc) {
                dati[1] = indice;
            } else {
                printf("Dati inseriti non validi");
                return 0;
            }

            if (strcmp(direzione, "giu") == 0) {
                dati[2] = -1;
            } else if (strcmp(direzione, "su") == 0) {
                dati[2] = 1;
            } else {
                printf("Dati inseriti non validi");
                return 0;
            }

        } else {
            printf("Dati inseriti non validi");
            return 0;
        }

        dati[3] = posizioni;
        return 1;
    }

}

void ruota(int M[K][K], int dati[4], int nr, int nc) {

    int Vtmp[max(nr, nc)];
    int selettore = dati[0];
    int indice = dati[1];
    int dir = dati[2];
    int pos = dati[3];
    int i, N;

    if (selettore == 0) {
        for (i = 0; i < nc; i++) {
            Vtmp[i] = M[indice][i];
            N = nc;
        }
    }

    if (selettore == 1) {
        for (i = 0; i < nr; i++) {
            Vtmp[i] = M[i][indice];
            N = nr;
        }
    }

    ruotaV(Vtmp, N, dir, pos);

    if (selettore == 0) {
        for (i = 0; i < N; i++) {
            M[indice][i] = Vtmp[i];
        }
    }

    if (selettore == 1) {
        for (i = 0; i < N; i++) {
            M[i][indice] = Vtmp[i];
        }
    }

}

void ruotaV(int V[], int N, int dir, int pos) {
    int tmp[N];
    int i;

    if (pos > N) {
        pos = pos - N*(pos/N);
    }

    if (dir == -1) {
        pos = N - pos;
    }

    //Salvo gli elementi che "fuoriuscirebbero" dalla riga/colonna
    for (i = 0; i < pos; i++) {
        tmp[i] = V[i];
    }

    //Effettuo la rotazione
    for (i = 0; i < N - pos; i++) {
        V[i] = V[i + pos];
    }

    //Ricopio i dati mancanti
    for (i = 0; i < pos; i++) {
        V[N - pos + i] = tmp[i];
    }

}