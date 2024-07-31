#include <stdio.h>
#include <malloc.h>

typedef struct att {
    int tInizio;
    int tFine;
} att;

void attSel(int N, att *v);

void powersetDispRip(int pos, att *val, int *sol, int *migliore, int k, int *sommaMax);

int valida(int *sol, att *val, int k);

int somma(int *sol, att *val, int k);

int stampaRis(int *migliore, int N, att *v, int sommaMax);

int main() {
    int N = 6;
    att v[6];

    v[0].tInizio = 1;
    v[0].tFine = 2;

    v[1].tInizio = 2;
    v[1].tFine = 4;

    v[2].tInizio = 2;
    v[2].tFine = 5;

    v[3].tInizio = 3;
    v[3].tFine = 5;

    v[4].tInizio = 5;
    v[4].tFine = 7;

    v[5].tInizio = 6;
    v[5].tFine = 8;

    attSel(N, v);
    return 0;
}

void attSel(int N, att *v) {
    int migliore[N];
    int sol[N];
    int pos = 0;
    int sommaMax = 0;

    powersetDispRip(pos, v, sol, migliore, N, &sommaMax);

    stampaRis(migliore, N, v, sommaMax);


}

void powersetDispRip(int pos, att *val, int *sol, int *migliore, int k, int *sommaMax) {
    int j;
    int s = 0;
    if (pos >= k) {


        if (valida(sol, val, k)) {

            /*Stampa di tutte le soluzioni valide*
             * SOLO PER VERIFICA
            printf("{");
            for (j=0; j<k; j++)
                if (sol[j]!=0)
                    printf(" (%d,%d) ", val[j].tInizio, val[j].tFine);
            printf("} \n");
             */

            s = somma(sol, val, k);
            if (s > *sommaMax) {
                for (j = 0; j < k; j++) {
                    migliore[j] = sol[j];
                }
                *sommaMax = s;
            }
        }
        return;
    }
    sol[pos] = 0;
    powersetDispRip(pos + 1, val, sol, migliore, k, sommaMax);
    sol[pos] = 1;
    powersetDispRip(pos + 1, val, sol, migliore, k, sommaMax);
    return;
}

int valida(int *sol, att *val, int k) {
    int i;
    //Si presume di avere durate in un intervallo di tempo positivo
    int finePrec=-1;
    for (i = 1; i < k; i++) {
        if (sol[i] != 0) {
            if (finePrec > val[i].tInizio)
                return 0;
            finePrec = val[i].tFine;
        }
    }
    return 1;
}

int somma(int *sol, att *val, int k) {
    int i, somma = 0;
    for (i = 0; i < k; i++) {
        if (sol[i] != 0)
            somma = somma + (val[i].tFine - val[i].tInizio);
    }
    return somma;
}


int stampaRis(int *migliore, int N, att *v, int sommaMax) {
    int j;
    printf("La somma delle durate massima e': %d\n", sommaMax);
    printf("Le attivita' sono:\n");
    for (j = 0; j < N; j++)
        if (migliore[j] != 0)
            printf("(%d,%d) \t", v[j].tInizio, v[j].tFine);

}
