#include <stdio.h>
#include <mem.h>

#define L 200
#define Max 30

struct tratta {
    char codice_tratta[Max];
    char partenza[Max];
    char destinazione[Max];
    char data[Max];
    char ora_partenza[Max];
    char ora_arrivo[Max];
    int ritardo;
};

typedef enum {
    r_stampa_data, r_stampa_tratta, r_stampa_partenza, r_stampa_arrivo, r_ricerca_partenza, r_fine, r_err
} comando_e;

comando_e leggiComando(void);

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
    FILE *fp;
    int nrighe;
    int i;

    struct tratta tabella[1000];

    struct tratta *tabRif0[1000], *tabRif1[1000], *tabRif2[1000], *tabRif3[1000];


    comando_e codiceComando;
    char richiesta[L];
    int continua = 1;
    fp = fopen("corse.txt", "r");
    if (fp == NULL) {
        printf("Impossibile aprire il file");
        return 1;
    }

    fscanf(fp, "%d", &nrighe);

    for (i = 0; i < nrighe; ++i) {
        fscanf(fp, "%s %s %s %s %s %s %d", tabella[i].codice_tratta, tabella[i].partenza, tabella[i].destinazione,
               tabella[i].data, tabella[i].ora_partenza, tabella[i].ora_arrivo, &tabella[i].ritardo);
    }

    fclose(fp);

    //Riempo i vettori di puntatori destinati agli ordinamenti
    for (i = 0; i < nrighe; i++)
        tabRif0[i] = tabRif1[i] = tabRif2[i] = tabRif3[i] = &tabella[i];

    ordinaPerData(tabRif0, nrighe);
    ordinaPerTratta(tabRif1, nrighe);
    ordinaPerPartenza(tabRif2, nrighe);
    ordinaPerArrivo(tabRif3, nrighe);


    while (continua) {
        codiceComando = leggiComando();
        //Gestisco i comandi non validi e quello di fine dal main gli altri tramite la funzione selezionaDati
        if (codiceComando == r_err) {
            printf("Comando inserito non valido");
        } else if (codiceComando == r_fine) {
            continua = 0;
        } else {
            gets(richiesta); //copio il resto della richiesta

            selezionaDati(codiceComando, tabRif0, tabRif1, tabRif2, tabRif3, richiesta, nrighe);

        }
        printf("\n***************************************************\n");
    }

    return 0;
}

comando_e leggiComando(void) {
    comando_e c;
    char cmd[L];
    char tabella[r_err][L] = {"stampa_data",
                              "stampa_tratta",
                              "stampa_partenza",
                              "stampa_arrivo",
                              "ricerca_partenza",
                              "fine"};
    printf("Inserisci comando: "
           "\n-->\"stampa_data <file/video>\", "
           "\n-->\"stampa_tratta <file/video>\", "
           "\n-->\"stampa_partenza <file/video>\","
           "\n-->\"stampa_arrivo <file/video>\", "
           "\n-->\"ricerca_partenza <partenza>(totale o parziale)\", "
           "\n-->\"fine\"\n");
    scanf("%s", cmd);

    //Si presume un inserimento del comando con tutti i caratteri minuscoli;
    c = r_stampa_data;
    while (c < r_err && strcmp(cmd, tabella[c]) != 0)
        c++;
    return c;

}

void selezionaDati(comando_e codiceComando, struct tratta **tabRif0, struct tratta **tabRif1, struct tratta **tabRif2,
                   struct tratta **tabRif3, char richiesta[], int nrighe) {

    char sceltaStampa[6];
    char fermata[30];

    switch (codiceComando) {
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
    printf("Tabella stampata nel file output.txr");

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
    int fine = nrighe-1;
    int indice = ricercaPartDicotomica(tabRif, inizio, fine, fermata);

    if (indice == -1) {
        printf("L'elemento cercato non e' presente");
        return;
    }
    //La funzione seguente stampa tutte le tratte accettabili al di sopra o al di sotto del risultato della ricerca
    stampaRicerca(tabRif, nrighe, indice, fermata);

}

int ricercaPartDicotomica(struct tratta **tabRif, int inizio, int fine, char fermata[]) {

    int m = (inizio + fine) / 2;
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

/*Vista la struttura dell'algoritmo non viene presa in considerazione
 * la ricerca lineare
 */