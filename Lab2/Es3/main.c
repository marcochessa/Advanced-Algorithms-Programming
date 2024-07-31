#include <stdio.h>
#include <mem.h>
#include <ctype.h>

int pos = 0;
int occorrenze = 0;


//Dati il puntatore a file e la sequenza da cercare chiama le funzioni di ricerca e analizza i risultati
void ricercaOccorrenze(FILE *fl, char seqCorr[]);

//Data una riga trovo le parole contenute in essa e verifico la corrispondenza
int trovaParole(char riga[], char seqCorr[]);

//Data una stringa la rendo minuscola
void toLow(char stringa[]);

//Data la parola letta dal testo la parola corrente da sequenza verifica se è presente al suo interno
int cercaSequenza(char parola[], char seqCorr[]);

int main() {
    char seqCorr[6];
    FILE *fp, *fl;
    int N;
    fp = fopen("sequenze.txt", "r");
    if (fp == NULL) {
        printf("Impossibile aprire");
        return 1;

    }
    fl = fopen("testo.txt", "r");
    if (fl == NULL) {
        printf("Impossibile aprire");
        return 1;
    }

    fscanf(fp, "%d", &N);
    //Effettuo la ricerca per ogni parola del file sequenze
    for (int i = 0; i < N; ++i) {
        fscanf(fp, "%s", seqCorr);
        //Trascuro la differenza fra maiuscole e minuscole trasformando la stringa
        toLow(seqCorr);
        ricercaOccorrenze(fl, seqCorr);
        printf("\n******************\n");
        //Riporto l'indicatore di posizione all'inizio del file
        rewind(fl);
    }

    fclose(fp);
    fclose(fl);

    return 0;
}

void ricercaOccorrenze(FILE *fl, char seqCorr[]) {
    char riga[200];
    int info;
    //Azzero il contatore delle posizioni e quello delle occorrenze
    pos = 0;
    occorrenze = 0;

    printf("La sequenza (%s) risulta contenuta in: ", seqCorr);
    fgets(riga, 200, fl);
    while (!feof(fl)) {
        info = trovaParole(riga, seqCorr);
        fgets(riga, 200, fl);
    }
    if (info == -1) {
        printf("\nRisultati limitati\n");
    } else if (occorrenze == 0) {
        printf("Nessuna corrispondenza\n");
    }
}

int trovaParole(char riga[], char seqCorr[]) {
    int k = strlen(riga);
    int i, j = 0;
    int trovata;
    char parola[26];
    for (i = 0; i < k; i++) {
        if (isalnum(riga[i])) {
            parola[j] = tolower(riga[i]);
            j++;
        } else if (isspace(riga[i]) || ispunct(riga[i])) {
            parola[j] = '\0';
            if (strlen(parola) != 0) {
                pos++;
                trovata = cercaSequenza(parola, seqCorr);
                if (trovata) {
                    //Limito le occorrenze a 10
                    if (occorrenze < 10) {
                        printf("\n--> %s (parola in posizione %d)", parola, pos);
                        occorrenze++;
                    } else {
                        return -1;
                    }
                }
            }
            j = 0;
        }
    }
    return 0;
}

int cercaSequenza(char parola[], char seqCorr[]) {
    int i, j = 0;
    int count = 0;
    int trovato = 0;
    int c = strlen(parola);
    int k = strlen(seqCorr);
    for (i = 0; i < c; i++) {
        if (seqCorr[j] == parola[i]) {
            j++;
            count++;
            if (count == k) {
                trovato = 1;
                return trovato;
            }
        } else {
            count = 0;
            j = 0;
        }
    }
    return trovato;
}

void toLow(char stringa[]) {
    for (int i = 0; i < strlen(stringa); ++i) {
        stringa[i] = tolower(stringa[i]);
    }
}