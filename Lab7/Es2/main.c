#include <stdio.h>
#include <malloc.h>


int componiCollana(int pos, int *quantitaPietre, int tipiPietre, int *sol, int *valorePietre, int *collanaMigliore,
                   int max_rip, int valoreMax, int len, int *lunghezza);

int promising(int *sol, int pos, int corrente);

int oltreRipMax(int *sol, int pos, int corrente, int max_rip);

int solValida(int *sol, int len);

int calcolaValore(int *sol, int len, int *valorePietre);

int main() {
    FILE *fp;
    char pietre[4] = {'z', 'r', 't', 's'};
    int *sol;
    int tipiPietre = 4;
    int *collanaMigliore;
    int quantitaPietre[4];
    int valorePietre[4];
    int valoreMax = 0, max_rip, max_len;
    int N, tot, lunghezza;
    int pos = 0;


    fp = fopen("e2_test_set.txt", "r");
    if (fp == NULL) {
        printf("Impossibile leggere file\n");
        return 1;
    }

    fscanf(fp, "%d ", &N);
    for (int j = 0; j < N; j++) {
        printf("TEST #%d\n", j + 1);
        fscanf(fp, "%d %d %d %d", &quantitaPietre[0], &quantitaPietre[1], &quantitaPietre[2], &quantitaPietre[3]);
        tot = quantitaPietre[0] + quantitaPietre[1] + quantitaPietre[2] + quantitaPietre[3];
        fscanf(fp, "%d %d %d %d", &valorePietre[0], &valorePietre[1], &valorePietre[2], &valorePietre[3]);
        printf("Z= %d [%d], R=%d [%d], T=%d [%d], S=%d [%d]\n",
               quantitaPietre[0], valorePietre[0],
               quantitaPietre[1], valorePietre[1],
               quantitaPietre[2], valorePietre[2],
               quantitaPietre[3], valorePietre[3]);

        fscanf(fp, "%d", &max_rip);
        sol = malloc(tot * sizeof(int));
        collanaMigliore = malloc(tot * sizeof(int));

        valoreMax = 0;
        max_len = 0;
        //Calcolo per ogni insieme di pietre la lunghezza massima della collana
        for (int k = 0; k < tipiPietre; k++)
            max_len += quantitaPietre[k];

        /*Chiamo la funzione per grandezze crescenti, da 1 a lunghezza massima, si sarebbe potuto effettuare
         *analogamente per grandezze descrescenti*/
        for (int i = 1; i < max_len; i++) {
            valoreMax = componiCollana(pos, quantitaPietre, tipiPietre, sol, valorePietre, collanaMigliore,
                                       max_rip, valoreMax, i, &lunghezza);
        }
        if (valoreMax == 0) {
            printf("Errore");
            return 1;
        }

        printf("La collana di valore massimo: %d con %d pietre e' la seguente:\n-> ", valoreMax, lunghezza);
        //Nella fase di stampa viene "convertito" il vettore di interi nei caratteri che rappresentano le pietre
        for (int i = 0; i < lunghezza; i++)
            printf("%c ", pietre[collanaMigliore[i]]);
        printf("\n*******\n");

        free(sol);
        free(collanaMigliore);
    }
    return 0;
}

int componiCollana(int pos, int *quantitaPietre, int tipiPietre, int *sol, int *valorePietre, int *collanaMigliore,
                   int max_rip, int valoreMax, int len, int *lunghezza) {
    int i, valoreCorr;
    if (pos >= len) {
        if (solValida(sol, len)) {
            valoreCorr = calcolaValore(sol, len, valorePietre);
            if (valoreCorr > valoreMax) {
                valoreMax = valoreCorr;
                *lunghezza = len;
                for (i = 0; i < len; i++) {
                    collanaMigliore[i] = sol[i];
                }
            }
        }
        return valoreMax;
    }
    for (i = 0; i < tipiPietre; i++) {
        if (quantitaPietre[i] > 0) {
            if (promising(sol, pos, i))
                if (oltreRipMax(sol, pos, i, max_rip)) {
                    quantitaPietre[i]--;
                    sol[pos] = i;
                    valoreMax = componiCollana(pos + 1, quantitaPietre, tipiPietre, sol, valorePietre, collanaMigliore,
                                               max_rip, valoreMax, len, lunghezza);
                    quantitaPietre[i]++;
                }

        }
    }
    return valoreMax;

}

int promising(int *sol, int pos, int corrente) {
    //Ad esclusione della posizione iniziale verifico le regole di composizione prima dell'inserimento
    if (pos == 0)
        return 1;

    switch (sol[pos - 1]) {
        case 0: //Z
            if (corrente == 0 || corrente == 1)
                return 1;
            else
                return 0;
        case 1: //R
            if (corrente == 2 || corrente == 3)
                return 1;
            else
                return 0;
        case 2: //T
            if (corrente == 0 || corrente == 1)
                return 1;
            else
                return 0;
        case 3: //S
            if (corrente == 2 || corrente == 3)
                return 1;
            else
                return 0;
    }
    return 0;
}

int oltreRipMax(int *sol, int pos, int corrente, int max_rip) {
    //Ritorno 0 se sono state superate le ripetizioni consecutive massime altrimenti ritorno 1
    int count = 0;
    pos--;
    while (pos >= 0 && count < max_rip) {
        if (sol[pos] == corrente) {
            count++;
            pos--;
        } else //Siccome devono essere ripetizioni consecutive posso interrompere il ciclo
            break;
    }
    if (count >= max_rip)
        return 0;
    return 1;
}

int solValida(int *sol, int len) {
    //Verifico se il numero di zaffiri supera quello degli smeraldi, se è così la soluzione non è valida
    int i, count_zaf, count_sme;
    for (i = 0; i < len; i++) {
        if (sol[i] == 0)
            count_zaf++;
        if (sol[i] == 3)
            count_sme++;
        if (count_zaf > count_sme)
            return 0;
    }
    return 1;
}

int calcolaValore(int *sol, int len, int *valorePietre) {
    int valore = 0, i;
    for (i = 0; i < len; i++) {
        valore = valore + valorePietre[sol[i]];
    }
    return valore;
}