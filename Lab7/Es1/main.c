#include <stdio.h>
#include <malloc.h>

int componiCollana(int pos, char *val, char *sol, char *collana, int tipiPietre, int *quantitaPietre, int MAX);

int promising(char *sol, int pos, char corrente);

int main() {
    FILE *fp;
    char pietre[4] = {'z', 'r', 't', 's'};
    char *sol;
    char *collana;
    int quantitaPietre[4];
    int max = 0;
    int N, tot;


    fp = fopen("Test.txt", "r");
    if (fp == NULL) {
        printf("Impossibile leggere file\n");
        return 1;
    }

    fscanf(fp, "%d ", &N);
    for (int j = 0; j < N; j++) {
        printf("TEST #%d\n", j + 1);
        fscanf(fp, "%d %d %d %d", &quantitaPietre[0], &quantitaPietre[1], &quantitaPietre[2], &quantitaPietre[3]);
        tot = quantitaPietre[0] + quantitaPietre[1] + quantitaPietre[2] + quantitaPietre[3];
        printf("Z= %d, R=%d, T=%d, S=%d\n", quantitaPietre[0], quantitaPietre[1], quantitaPietre[2], quantitaPietre[3]);

        sol = malloc(tot * sizeof(char));
        collana = malloc(tot * sizeof(char));

        max = 0;
        max = componiCollana(0, pietre, sol, collana, 4, quantitaPietre, max);

        if (max == 0) {
            printf("Errore");
            return 1;
        }

        printf("La collana di dimensione %d e' la seguente:\n-> ", max);
        for (int i = 0; i < max; i++)
            printf("%c ", collana[i]);
        printf("\n*******\n");

        free(sol);
        free(collana);

    }
    return 0;
}

int componiCollana(int pos, char *pietre, char *sol, char *collana, int tipiPietre, int *quantitaPietre, int MAX) {
    int i;

    /*Sarebbe opportuno evitare  variazioni del valore MAX all'interno della ricorsione.
     * Nonostante questo si è optato per effettuare il calcolo delle disposizioni una sola volta,
     * rimuovendo la condizione iniziale di terminazione della ricorsione e terminando una volta finito
     * il numero di ogni pietra.*/
    if (pos > MAX) {
        for (i = 0; i < pos; i++)
            collana[i] = sol[i];
        MAX = pos;
    }

    for (i = 0; i < tipiPietre; i++) {
        if (quantitaPietre[i] > 0) {
            if (promising(sol, pos, pietre[i])) {
                quantitaPietre[i]--;
                sol[pos] = pietre[i];
                MAX = componiCollana(pos + 1, pietre, sol, collana, tipiPietre, quantitaPietre, MAX);
                quantitaPietre[i]++;
            }
        }
    }
    return MAX;
}

int promising(char *sol, int pos, char corrente) {
    if (pos == 0)
        return 1;

    switch (sol[pos - 1]) {
        case 'z':
            if (corrente == 'z' || corrente == 'r')
                return 1;
            else
                return 0;
        case 's':
            if (corrente == 's' || corrente == 't')
                return 1;
            else
                return 0;
        case 'r':
            if (corrente == 's' || corrente == 't')
                return 1;
            else
                return 0;
        case 't':
            if (corrente == 'z' || corrente == 'r')
                return 1;
            else
                return 0;
    }
    return 0;
}
