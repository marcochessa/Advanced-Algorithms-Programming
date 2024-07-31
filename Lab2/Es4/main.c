#include <stdio.h>

#define Max 30

void SelectionSort(int V[], int len);

void InsertionSort(int V[], int len);

void ShellSort(int V[], int len);

void stampaVett(int V[], int len);

int main() {
    int Vselection[Max];
    int Vshell[Max];
    int Vinsertion[Max];
    int tmp;

    FILE *fp;
    int N, len;

    fp = fopen("sort.txt", "r");
    if (fp == NULL) {
        printf("Impossibile aprire file");
        return 1;
    }
    fscanf(fp, "%d", &N);

    for (int i = 0; i < N; i++) {
    fscanf(fp, "%d", &len);
    for (int j = 0; j < len; j++) {
        fscanf(fp, "%d", &tmp);
        Vselection[j] = tmp;
        Vshell[j] = tmp;
        Vinsertion[j] = tmp;
    }

    printf("\n\nVettore numero %d: \n",i+1);
    stampaVett(Vselection, len);

    SelectionSort(Vselection, len);
    printf("\nVettore ordinato con selection sort:\n");
    stampaVett(Vselection, len);

    InsertionSort(Vinsertion, len);
    printf("\nVettore ordinato con insertion sort:\n");
    stampaVett(Vinsertion, len);

    ShellSort(Vshell, len);
    printf("\nVettore ordinato con shell sort:\n");
    stampaVett(Vshell, len);

    }

    return 0;
}

void SelectionSort(int V[], int len) {

    printf("\n*******************************\n");

    int scambi = 0;
    int itInt = 0;
    int iterazTot = 0;

    int Pmin;
    int tmp;
    printf("\nSelection Sort: iterazioni esterne %d\n", len - 1);
    for (Pmin = 0; Pmin < len - 1; Pmin++) {
        int iMin = Pmin;
        for (int i = Pmin + 1; i < len; i++) {
            if (V[i] < V[iMin]) {
                iMin = i;
            }
            itInt++;
        }
        //Faccio in modo di effettuare gli effettivi scambi necessari
        if (iMin != Pmin) {
            tmp = V[iMin];
            V[iMin] = V[Pmin];
            V[Pmin] = tmp;
            scambi++;
        }
        printf("-->it.esterna %d: it.interne %d\n", Pmin, itInt);

        iterazTot = iterazTot + itInt;
        itInt = 0;
    }
    printf("it. totali %d, scambi: %d\n", iterazTot, scambi);
}

void InsertionSort(int V[], int len) {

    printf("\n*******************************\n");

    int scambi = 0;
    int itInt = 0;
    int iterazTot = 0;

    int j, i;
    int key;


    printf("\nInsertion Sort: iterazioni esterne %d\n", len - 1);
    for (j = 1; j < len; j++) {
        key = V[j];
        for (i = j - 1; i >= 0 && V[i] > key; i--) {
            V[i + 1] = V[i];
            scambi++;
            itInt++;
        }
        V[i + 1] = key;
        //Se esso rientra nella definizione di scambio
        scambi++;
        printf("-->it.esterna %d: it.interne %d\n", j, itInt);

        iterazTot = iterazTot + itInt;
        itInt = 0;

    }
    printf("it. totali %d, scambi: %d\n", iterazTot, scambi);

}

void ShellSort(int V[], int len) {

    printf("\n*******************************\n");

    /*Visto che viene generalizzato l'insertion sort, introducedo un "gap", vi è poca chiarezza
     * su quale sia il ciclo esterno, nella funzione che segue viene considerato il ciclo esterno
     * quello dove viene aggiornato il gap e come ciclo interno il ciclo considerato esterno per
     * l'insertion sort (funzione precedente)
     */

    int scambi = 0;
    int itInt = 0;
    int itExt = 1;
    int iterazTot = 0;

    int i, j, l = 0, h = 1;
    int tmp;

    printf("\nShell Sort:\n");
    while (h < len / 3) {
        h = 3 * h + 1;
    }
    while (h >= 1) {
        for (i = l + h; i <= len - 1; i++) {
            j = i;
            tmp = V[i];
            while (j >= l + h && V[j - h] >= tmp) {
                V[j] = V[j - h];
                j = j - h;
                scambi++;
            }
            V[j] = tmp;
            //Se esso rientra nella definizione di scambio
            scambi++;

            itInt++;
        }

        printf("---->it.esterna %d: it.interne %d\n", itExt, itInt);

        iterazTot = iterazTot + itInt;
        itInt = 0;
        itExt++;
        h = h / 3;

    }
    printf("it. totali %d, scambi: %d\n", iterazTot, scambi);

}


void stampaVett(int V[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", V[i]);
    }
}