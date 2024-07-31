#include <stdio.h>

#define m 5
#define n 5

int capolista(int M[n][m], int k);
int valido(int N);
void aggiornapunti(int M[n][m], int k);

int main() {
    int M[n][m];
    int i, j, k;
    int N,X = 0;
    FILE *fp;

    fp = fopen("nome.txt", "r");
    if (fp == NULL) {
        printf("Impossibile aprire");
        return 1;
    }

    //Riempio la matrice effettuando un controllo sui dati
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            fscanf(fp, "%d", &X);
            if(valido(X)){
                M[i][j]=X;
            } else{
                printf("Valore [%d][%d] non valido",i,j);
                M[i][j]=0;
            }
        }
    }

    fclose(fp);

    //Per ogni giornata stampo la capolista
    for (k = 0; k < m; k++) {
        N = capolista(M, k);
        printf("Giorno %d: capolista numero %d \n",k, N);
    }

    return 0;
}

int valido(int X){
    switch (X){
        case 0:
            return 1;
        case 1:
            return 1;
        case 3:
            return 1;
        default:
            return 0;

    }
}

int capolista(int M[n][m], int k) {
    int MAX = -1;
    int i;
    int ret;
    for (i = 0; i < n; i++) {
        if (M[i][k] > MAX) {
            MAX = M[i][k];
            ret = i;
        }
    }

    /*La funzione aggiorna punti somma nella colonna che verrà letta al prossimo richiamo della funzione capolista
     * tutti i punti delle giornate precedenti, chiaramente verrà chiamata una volta in meno rispetto a capolista, visto
     * che l'ultimo giorno viene considerato in precedenza.
     * Il tutto è motivato dal fatto che per il primo giorno non è necessaio sommare le giornate precedenti.
     */
    if (k < m - 1) {
        aggiornapunti(M, k);
    }

    return ret;
}

void aggiornapunti(int M[n][m], int k) {
    int i;
    for (i = 0; i < n; i++) {
        M[i][k + 1] += M[i][k];
    }
}