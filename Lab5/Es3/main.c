#include <stdio.h>
#include <malloc.h>
#include <mem.h>

#define L 200

struct tratta {
    char *codice_tratta;
    char *partenza;
    char *destinazione;
    char data[11]; // La dimensioni di data e ora sono conosciute e fisse all'interno del programma
    char ora_partenza[9];
    char ora_arrivo[9];
    int ritardo;
};

typedef enum {
    r_nuovo_file, r_stampa_data, r_stampa_tratta, r_stampa_partenza, r_stampa_arrivo, r_ricerca_partenza, r_fine, r_err
} comando_e;

comando_e leggiComando(void);

int leggiFile(struct tratta **tabella, struct tratta ***tabRif0, struct tratta ***tabRif1,
              struct tratta ***tabRif2, struct tratta ***tabRif3);


void riempiTab(struct tratta *tabella, struct tratta **tabRif0, struct tratta **tabRif1, struct tratta **tabRif2,
               struct tratta **tabRif3, int nrighe, FILE *fp);

void liberaMemoria(struct tratta *tabella, int nrighe, struct tratta **tabRif0, struct tratta **tabRif1,
                   struct tratta **tabRif2, struct tratta **tabRif3);

void selezionaDati(comando_e codiceComando, struct tratta **tabRif0, struct tratta **tabRif1, struct tratta **tabRif2,
                   struct tratta **tabRif3, char richiesta[], int nrighe);

void stampaVideo(struct tratta **tabRif, int nrighe);

void stampaFile(struct tratta **tabRif, int nrighe);

void ordinaPerData(struct tratta **tabRif, int nrighe);

int confrontaData(struct tratta *tr1, struct tratta *tr2);

void ordinaPerTratta(struct tratta **tabRif, int nrighe);

void ordinaPerPartenza(struct tratta **tabRif, int nrighe);

void ordinaPerArrivo(struct tratta **tabRif, int nrighe);

void ricercaPartenza(struct tratta **tabRif, int nrighe, char fermata[]);

int ricercaPartDicotomica(struct tratta **tabRif, int inizio, int fine, char fermata[]);

void stampaRicerca(struct tratta **tabRif, int nrighe, int indice, char fermata[]);

int main() {
    comando_e codiceComando;
    char richiestaTmp[L];
    char *richiesta;
    int continua = 1;
    struct tratta *tabella;
    struct tratta **tabRif0, **tabRif1, **tabRif2, **tabRif3;
    int nrighe;

    nrighe = leggiFile(&tabella, &tabRif0, &tabRif1, &tabRif2, &tabRif3);

    if (nrighe == -1)
        return 1;


    ordinaPerData(tabRif0, nrighe);
    ordinaPerTratta(tabRif1, nrighe);
    ordinaPerPartenza(tabRif2, nrighe);
    ordinaPerArrivo(tabRif3, nrighe);

    /*Per comodità alcuni comandi vengono gestiti dal main, ma potrebbero facilmente essere gestiti dalla funzione
     * selezionaDati
     */

    while (continua) {
        codiceComando = leggiComando();

        switch (codiceComando) {
            case r_fine:
                continua = 0;
                break;
            case r_nuovo_file:
                liberaMemoria(tabella, nrighe, tabRif0, tabRif1, tabRif2, tabRif3);

                nrighe = leggiFile(&tabella, &tabRif0, &tabRif1, &tabRif2, &tabRif3);
                if (nrighe == -1)
                    return 1;

                ordinaPerData(tabRif0, nrighe);
                ordinaPerTratta(tabRif1, nrighe);
                ordinaPerPartenza(tabRif2, nrighe);
                ordinaPerArrivo(tabRif3, nrighe);
                break;
            default:
                gets(richiestaTmp); //copio il resto della richiesta
                richiesta = strdup(richiestaTmp);
                selezionaDati(codiceComando, tabRif0, tabRif1, tabRif2, tabRif3, richiesta, nrighe);
                break;
        }
        printf("\n***************************************************\n");
    }

    liberaMemoria(tabella, nrighe, tabRif0, tabRif1, tabRif2, tabRif3);

    return 0;
}

int leggiFile(struct tratta **tabella, struct tratta ***tabRif0, struct tratta ***tabRif1, struct tratta ***tabRif2,
              struct tratta ***tabRif3) {
    FILE *fp;
    int nrighe;
    char nome[30];

    printf("Inserisci nome file\n");
    scanf("%s", nome);
    fp = fopen(nome, "r");

    if (fp == NULL) {
        printf("Impossibile aprire file");
        return -1;
    }

    fscanf(fp, "%d", &nrighe);
    *tabella = malloc(nrighe * sizeof(struct tratta));


    //Alloco dinamicamente i vettori di puntatori destinati all'ordinamento
    *tabRif0 = malloc(nrighe * sizeof(struct tratta *));
    *tabRif1 = malloc(nrighe * sizeof(struct tratta *));
    *tabRif2 = malloc(nrighe * sizeof(struct tratta *));
    *tabRif3 = malloc(nrighe * sizeof(struct tratta *));


    riempiTab(*tabella, *tabRif0, *tabRif1, *tabRif2, *tabRif3, nrighe, fp);
    fclose(fp);

    printf("File letto correttamente\n");

    return nrighe;

}

void riempiTab(struct tratta *tabella, struct tratta **tabRif0, struct tratta **tabRif1, struct tratta **tabRif2,
               struct tratta **tabRif3, int nrighe, FILE *fp) {
    //Dichiaro delle variabili di appoggio
    char codiceTratta[30], partenza[30], destinazione[30];
    int i;
    for (i = 0; i < nrighe; ++i) {
        fscanf(fp, "%s %s %s %s %s %s %d", codiceTratta, partenza, destinazione,
               tabella[i].data, tabella[i].ora_partenza, tabella[i].ora_arrivo, &tabella[i].ritardo);

        //Alloco dinamicamente le seguenti stringhe
        tabella[i].codice_tratta = strdup(codiceTratta);
        tabella[i].partenza = strdup(partenza);
        tabella[i].destinazione = strdup(destinazione);
    }

    for (i = 0; i < nrighe; i++)
        tabRif0[i] = tabRif1[i] = tabRif2[i] = tabRif3[i] = &tabella[i];
}

void liberaMemoria(struct tratta *tabella, int nrighe, struct tratta **tabRif0, struct tratta **tabRif1,
                   struct tratta **tabRif2, struct tratta **tabRif3) {

    /*Libero prima lo spazio riservato alle stringhe interne alla struct tabella e successivamente lo spazio
     * allocato per i vettori
     */
    for(int i=0; i<nrighe; i++){
        free(tabella[i].codice_tratta);
        free(tabella[i].partenza);
        free(tabella[i].destinazione);
    }
    free(tabella);
    free(tabRif0);
    free(tabRif1);
    free(tabRif2);
    free(tabRif3);
}

comando_e leggiComando(void) {
    comando_e c;
    char cmd[L];
    char tabella[r_err][L] = {"nuovo_file",
                              "stampa_data",
                              "stampa_tratta",
                              "stampa_partenza",
                              "stampa_arrivo",
                              "ricerca_partenza",
                              "fine"};
    printf("Inserisci comando: "
           "\n-->\"nuovo_file <nome>\", "
           "\n-->\"stampa_data <video/file>\", "
           "\n-->\"stampa_tratta <video/file>\", "
           "\n-->\"stampa_partenza <video/file>\","
           "\n-->\"stampa_arrivo <video/file>\","
           "\n-->\"ricerca_partenza <nome stazione>\", "
           "\n-->\"fine\"\n");
    scanf("%s", cmd);

    //Si presume un inserimento del comando con tutti i caratteri minuscoli;
    c = r_nuovo_file;
    while (c < r_err && strcmp(cmd, tabella[c]) != 0)
        c++;
    return c;

}

void selezionaDati(comando_e codiceComando, struct tratta **tabRif0, struct tratta **tabRif1, struct tratta **tabRif2,
                   struct tratta **tabRif3, char richiesta[], int nrighe) {

    char sceltaStampa[6];
    char fermata[30];

    switch (codiceComando) {
        case r_err:
            printf("Comando inserito non valido");
            break;
        case r_stampa_data:
            sscanf(richiesta, "%s", sceltaStampa);
            if (!strcmp(sceltaStampa, "video")) {
                stampaVideo(tabRif0, nrighe);
            } else if (!strcmp(sceltaStampa, "file")) {
                stampaFile(tabRif0, nrighe);
            } else {
                printf("Comando non valido, inserire destinazione di stampa\n");
            }
            break;
        case r_stampa_tratta:
            sscanf(richiesta, "%s", sceltaStampa);
            if (!strcmp(sceltaStampa, "video")) {
                stampaVideo(tabRif1, nrighe);
            } else if (!strcmp(sceltaStampa, "file")) {
                stampaFile(tabRif1, nrighe);
            } else {
                printf("Comando non valido, inserire destinazione di stampa\n");
            }
            break;
        case r_stampa_partenza:
            sscanf(richiesta, "%s", sceltaStampa);
            if (!strcmp(sceltaStampa, "video")) {
                stampaVideo(tabRif2, nrighe);
            } else if (!strcmp(sceltaStampa, "file")) {
                stampaFile(tabRif2, nrighe);
            } else {
                printf("Comando non valido, inserire destinazione di stampa\n");
            }
            break;
        case r_stampa_arrivo:
            sscanf(richiesta, "%s", sceltaStampa);
            if (!strcmp(sceltaStampa, "video")) {
                stampaVideo(tabRif3, nrighe);
            } else if (!strcmp(sceltaStampa, "file")) {
                stampaFile(tabRif3, nrighe);
            } else {
                printf("Comando non valido, inserire destinazione di stampa\n");
            }
            break;
        case r_ricerca_partenza:
            sscanf(richiesta, "%s", fermata);
            ricercaPartenza(tabRif2, nrighe, fermata);

    }
}

void stampaVideo(struct tratta **tabRif, int nrighe) {
    int i;
    for (i = 0; i < nrighe; ++i) {
        printf("%s %s %s %s %s %s %d\n", tabRif[i]->codice_tratta, tabRif[i]->partenza, tabRif[i]->destinazione,
               tabRif[i]->data, tabRif[i]->ora_partenza, tabRif[i]->ora_arrivo, tabRif[i]->ritardo);
    }
}

void stampaFile(struct tratta **tabRif, int nrighe) {
    FILE *fo;
    int i;
    fo = fopen("output.txt", "w");
    if (fo == NULL) {
        printf("Errore nell'apertura del file\n");
        return;
    }

    for (i = 0; i < nrighe; ++i) {
        fprintf(fo, "%s %s %s %s %s %s %d\n", tabRif[i]->codice_tratta, tabRif[i]->partenza, tabRif[i]->destinazione,
                tabRif[i]->data, tabRif[i]->ora_partenza, tabRif[i]->ora_arrivo, tabRif[i]->ritardo);
    }

    fclose(fo);
    printf("Tabella stampata nel file output.txt");

}

void ordinaPerData(struct tratta **tabRif, int nrighe) {
    int i, j, l = 0, r = nrighe - 1;
    /*Viene utilizzato il bubble sort*/

    struct tratta *temp;
    for (i = l; i < r; i++) {
        for (j = l; j < (r - i + l); j++)
            if (confrontaData(tabRif[j], tabRif[j + 1])) {
                temp = tabRif[j];
                tabRif[j] = tabRif[j + 1];
                tabRif[j + 1] = temp;
            }
    }

}

int confrontaData(struct tratta *tr1, struct tratta *tr2) {
    if (strcmp(tr1->data, tr2->data) > 0) {
        return 1;
    }
    if (strcmp(tr1->data, tr2->data) == 0) //A parità di data controllo le ore
        if (strcmp(tr1->ora_partenza, tr2->ora_partenza) > 0) {
            return 1;
        }
    return 0;
}

void ordinaPerTratta(struct tratta **tabRif, int nrighe) {
    int i, j, l = 0, r = nrighe - 1;
    struct tratta *temp;
    for (i = l; i < r; i++) {
        for (j = l; j < (r - i + l); j++)
            if (strcmp(tabRif[j]->codice_tratta, tabRif[j + 1]->codice_tratta) > 0) {
                temp = tabRif[j];
                tabRif[j] = tabRif[j + 1];
                tabRif[j + 1] = temp;
            }
    }

}

void ordinaPerPartenza(struct tratta **tabRif, int nrighe) {
    int i, j, l = 0, r = nrighe - 1;
    struct tratta *temp;
    for (i = l; i < r; i++) {
        for (j = l; j < (r - i + l); j++)
            if (strcmp(tabRif[j]->partenza, tabRif[j + 1]->partenza) > 0) {
                temp = tabRif[j];
                tabRif[j] = tabRif[j + 1];
                tabRif[j + 1] = temp;
            }
    }
}

void ordinaPerArrivo(struct tratta **tabRif, int nrighe) {
    int i, j, l = 0, r = nrighe - 1;
    struct tratta *temp;
    for (i = l; i < r; i++) {
        for (j = l; j < (r - i + l); j++)
            if (strcmp(tabRif[j]->destinazione, tabRif[j + 1]->destinazione) > 0) {
                temp = tabRif[j];
                tabRif[j] = tabRif[j + 1];
                tabRif[j + 1] = temp;
            }
    }
}

void ricercaPartenza(struct tratta **tabRif, int nrighe, char fermata[]) {
    int inizio = 0;
    int fine = nrighe - 1;
    int indice = ricercaPartDicotomica(tabRif, inizio, fine, fermata);

    if (indice == -1) {
        printf("L'elemento cercato non e' presente");
        return;
    }

    //La funzione seguente stampa tutte le tratte accettabili al di sopra o al di sotto del risultato della ricerca
    stampaRicerca(tabRif, nrighe, indice, fermata);

}

int ricercaPartDicotomica(struct tratta **tabRif, int inizio, int fine, char fermata[]) {
    int m;
    m = (inizio + fine) / 2;
    if (m < inizio || fine < 0) {
        // l'elemento cercato non c'è
        return -1;
    } else if (strncmp(fermata, tabRif[m]->partenza, strlen(fermata)) < 0) {
        // Si ripete la ricerca nella parte inferiore
        return ricercaPartDicotomica(tabRif, inizio, m - 1, fermata);
    } else if (strncmp(fermata, tabRif[m]->partenza, strlen(fermata)) > 0) {
        // Si ripete la ricerca nella parte superiore
        return ricercaPartDicotomica(tabRif, m + 1, fine, fermata);
    } else {
        return m;
    }
}

void stampaRicerca(struct tratta **tabRif, int nrighe, int indice, char fermata[]) {
    int i = indice;
    //Risultato della ricerca
    printf("%s %s %s %s %s %s %d\n", tabRif[i]->codice_tratta, tabRif[i]->partenza, tabRif[i]->destinazione,
           tabRif[i]->data, tabRif[i]->ora_partenza, tabRif[i]->ora_arrivo, tabRif[i]->ritardo);
    i--;

    //Risultati superiori
    while (i >= 0 && strncmp(fermata, tabRif[i]->partenza, strlen(fermata)) == 0) {
        printf("%s %s %s %s %s %s %d\n", tabRif[i]->codice_tratta, tabRif[i]->partenza, tabRif[i]->destinazione,
               tabRif[i]->data, tabRif[i]->ora_partenza, tabRif[i]->ora_arrivo, tabRif[i]->ritardo);
        i--;
    }

    //Risultati inferiori
    i = indice + 1;
    while (i < nrighe && strncmp(fermata, tabRif[i]->partenza, strlen(fermata)) == 0) {
        printf("%s %s %s %s %s %s %d\n", tabRif[i]->codice_tratta, tabRif[i]->partenza, tabRif[i]->destinazione,
               tabRif[i]->data, tabRif[i]->ora_partenza, tabRif[i]->ora_arrivo, tabRif[i]->ritardo);
        i++;
    }

}
