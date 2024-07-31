#include <stdio.h>
#include <mem.h>

int conta(char[], int);

int main() {
    char nome[21];
    char S[21];
    FILE *fp;
    int N, n;
    int i = 0;
    int somma = 0;

    printf("Inserisci nome file\n");
    scanf("%s", nome);

    printf("Inserisci lunghezza\n");
    scanf("%s", n);

    fp = fopen(nome, "r");
    if (fp == NULL) {
        printf("Impossibile aprire");
        return 1;
    }

    fscanf(fp, "%d", &N);
    for (i = 0; i < N; i++) {
        if (!feof(fp)) {
            fscanf(fp, "%s", S);
            somma = somma + conta(S, n);
        }
    }

    fclose(fp);


    printf("Il totale di sottostringhe è %d", somma);

    return 0;
}

int conta(char S[20], int n) {
    char vocali[] = {'a', 'e', 'i', 'o', 'u'};
    int sottostringhe = 0;
    int i, j = 0;
    int nVoc = 0;
    for (i = 0; i < strlen(S) - n; i++) {
        for (j = i; j < n; j++) {
            for (int v = 0; v < 5; v++) {
                if (S[j] == vocali[v]) {
                    nVoc++;
                }
            }
            if (nVoc == 2) {
                sottostringhe++;
            }
            nVoc = 0;
        }
    }
    return sottostringhe;
}