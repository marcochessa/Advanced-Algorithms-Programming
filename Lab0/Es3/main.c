#include <stdio.h>

#define maxN 30

void ruota(int v[maxN], int N, int P, int dir);

int main() {
    int N = 0;
    int n[maxN];
    int P = 0, j = 0;
    int dir = 1;

    printf("Inserisci un numero minore di %d\n", maxN);
    scanf("%d", &N);

    printf("Inseristi i valori del vettore separati da invio\n");
    for (j = 0; j < N; j++) {
        printf("Valore %d\n", j);
        scanf(" %d ", &n[j]);
    }

    printf("Inserisci di quanto vuoi ruotare\n");
    scanf("%d", &P);
    while (P != 0) {
        printf("Inserisci la direzione, 1 o -1\n");
        scanf("%d", &dir);
        ruota(n, N, P, dir);
        for (int j = 0; j < N; j++) {
            printf(" %d ", n[j]);
        }
        printf("\n");
        printf("Inserisci di quanto vuoi ruotare\n");
        scanf("%d", &P);
    }

    return 0;
}

void ruota(int v[maxN], int N, int P, int dir) {
    int temp[N], pos;
    for (int i = 0; i < N; i++) {
        if (dir == -1) {
            pos = i + P;
            if (pos > N) {
                pos = pos - N;
            }
        }
        if (dir == 1) {
            pos = i - P;
            if (pos < 0) {
                pos = pos + N;
            }
        }

        temp[pos] = v[i];


    }
    for (int j = 0; j < N; j++) {
        v[j] = temp[j];
    }
}