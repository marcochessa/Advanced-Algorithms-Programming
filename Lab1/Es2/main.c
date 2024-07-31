#include <stdio.h>
#include <mem.h>
#include <ctype.h>

struct dizionario {
    /*Per comodità la codifica viene memorizzata come stringa, tenendo in considerazione, per la lunghezza
     * della stringa numeri compresi nell'intervallo positivo coperto da int [0,32767] + 2 elementi per
     * il simbolo $ + 1 elemento per il carattere di fine stringa.*/
    char codifica[8];

    /*Per quanto riguarda la dimensione della stringa da ricercare si è pensato, in riferimento al testo,
     * ad una eventuale parola lunga quanto la dimensione massima della riga. In questo modo nel caso peggiore
     * si ha una parola lunga 200 caratteri + il carattere di fine stringa.*/
    char parola[201];
};

/*La funzione confronto si occupa di trovare nella parola data la parola del dizionario passata
 * se la trova si occupa di codificarla e restituisce vero se la trova o falso se non la trova
 */
int confronto(char parolaData[], char parolaDiz[], char codifica[], char risultato[]);

/*Ricerca utilizza la funzione prova per ogni parola del dizionario finché non trova quella richiesta.
 *Se non la trova va a salvare la parola senza essere codificata nella stringa risultato
 */
void ricerca(char parola[], struct dizionario diz[], int N, char risultato[]);

int main() {
    FILE *fp;
    FILE *fl;
    FILE *ff;
    char riga[201];
    char parola[201];
    //Creo risultato con la dimensione massima possibile dim(parola)+dim(codifica)
    char risultato[209];
    int N, i, j, n, lun;

    fl = fopen("dizionario.txt", "r");
    if (fl == NULL) {
        printf("Impossibile aprire");
        return 1;
    }

    //Controllo qunante perole ho nel dizionario
    if (!feof(fl))
        fscanf(fl, "%d", &N);

    struct dizionario diz[N];
    for (i = 0; i < N; i++) {
        if (!feof(fl))
            fscanf(fl, "%s%s", diz[i].codifica, diz[i].parola);
    }

    fclose(fl);

    fp = fopen("sorgente.txt", "r");
    if (fp == NULL) {
        printf("Impossibile aprire");
        return 2;
    }
    ff = fopen("ricodificato.txt", "w");
    if (ff == NULL) {
        printf("Impossibile aprire");
        return 3;
    }


    fgets(riga, 200, fp);
    while (!feof(fp)) {
        n = 0;
        lun = strlen(riga);
        for (j = 0; j < lun; j++) {
            if (!isspace(riga[j])) {
                parola[n] = riga[j];
                n++;
            } else {
                parola[n] = '\0';
                ricerca(parola, diz, N, risultato);
                fprintf(ff, " %s ", risultato);
                n = 0;
            }
        }
        fprintf(ff, "\n");
        fgets(riga, 200, fp);
    }

    fclose(fp);
    fclose(ff);


    return 0;
}

void ricerca(char parola[], struct dizionario diz[], int N, char risultato[]) {
    int i, k;
    int trovata = 0;
    for (i = 0; i < N && trovata == 0; i++) {
        k = confronto(parola, diz[i].parola, diz[i].codifica, risultato);
        if (k == 1) {
            trovata = 1;
        }
    }
    if (trovata == 0) {
        strcpy(risultato, parola);
    }

}

int confronto(char parolaData[], char parolaDiz[], char codifica[], char risultato[]) {
    int n = 0, i, j;
    char *parTrovata;
    int q, k;
    int lun;
    parTrovata=strstr(parolaData, parolaDiz);
    if (parTrovata != NULL) {

        /*Effettuo la sottrazione fra la cella di memoria dove ha inizio l'occorrenza trovata e quella
         *dove ha inizio la parola data dal testo. In questo modo so quante lettere vi sono prima dell'occorrenza
         */
        n = parTrovata - parolaData;

        //Copio la prima parte della parola
        for (i = 0; i < n; i++) {
            risultato[i] = parolaData[i];
        }

        //Aggiungo la parte codificata
        k = n;
        lun = strlen(codifica);
        for (i = 0; i < lun; i++) {
            risultato[k] = codifica[i];
            k++;
        }

        //Aggiungo la parte finale
        k = n + lun;
        q = n + strlen(parolaDiz);
        lun = strlen(parolaData);
        for (j = q; j < lun; j++) {
            risultato[k] = parolaData[j];
            k++;
        }
        risultato[k] = '\0';
        return 1;
    } else {
        return 0;
    }
}