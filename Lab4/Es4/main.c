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
    r_stampa, r_ordina_data, r_ordina_tratta, r_ordina_partenza, r_ordina_arrivo, r_ricerca_partenza, r_fine, r_err
} comando_e;

comando_e leggiComando(void);

void selezionaDati(comando_e codiceComando, struct tratta tabella[], char richiesta[], int nrighe, int *ordinamento);

void stampaVideo(struct tratta tabella[], int nrighe);

void stampaFile(struct tratta tabella[], int nrighe);

void ordinaData(struct tratta tabella[], int nrighe);

int confrontaData(struct tratta n1, struct tratta n2);

void ordinaTratta(struct tratta tabella[], int nrighe);

void ordinaPartenza(struct tratta tabella[], int nrighe);

void ordinaArrivo(struct tratta tabella[], int nrighe);

void ricercaPartenza(struct tratta tabella[], int nrighe, char fermata[], int ordinamento);

void ricercaPartLineare(struct tratta tabella[], int nrighe, char fermata[]);

int ricercaPartDicotomica(struct tratta tabella[], int inizio, int fine, char fermata[]);

void stampaRicerca(struct tratta tabella[], int nrighe, int indice, char fermata[]);

int main() {
    FILE *fp;
    int nrighe;
    int i;
    int ordinamento = -1;

    struct tratta tabella[1000];
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

    while (continua) {
        codiceComando = leggiComando();
        //Gestisco i comandi non validi e quello di fine dal main gli altri tramite la funzione selezionaDati
        if (codiceComando == r_err) {
            printf("Comando inserito non valido");
        } else if (codiceComando == r_fine) {
            continua = 0;
        } else {
            gets(richiesta); //copio il resto della richiesta

            selezionaDati(codiceComando, tabella, richiesta, nrighe, &ordinamento);

        }
        printf("\n***************************************************\n");
    }

    return 0;
}

comando_e leggiComando(void) {
    comando_e c;
    char cmd[L];
    char tabella[r_err][L] = {"stampa",
                              "ordina_data",
                              "ordina_tratta",
                              "ordina_partenza",
                              "ordina_arrivo",
                              "ricerca_partenza",
                              "fine"};
    printf("Inserisci comando: "
           "\n-->\"stampa <file/video>\", "
           "\n-->\"ordina_data\", "
           "\n-->\"ordina_tratta\", "
           "\n-->\"ordina_partenza\", "
           "\n-->\"ordina_arrivo\", "
           "\n-->\"ricerca_partenza <nome fermata(anche parziale)>\", "
           "\n-->\"fine\"\n");
    scanf("%s", cmd);

    //Si presume un inserimento del comando con tutti i caratteri minuscoli;
    c = r_stampa;
    while (c < r_err && strcmp(cmd, tabella[c]) != 0)
        c++;
    return c;

}

void selezionaDati(comando_e codiceComando, struct tratta tabella[], char richiesta[], int nrighe, int *ordinamento) {

    char sceltaStampa[6];
    char fermata[30];

    switch (codiceComando) {
        case r_stampa:
            sscanf(richiesta, "%s", sceltaStampa);
            if (!strcmp(sceltaStampa, "video")) {
                stampaVideo(tabella, nrighe);
            } else if (!strcmp(sceltaStampa, "file")) {
                stampaFile(tabella, nrighe);
            } else {
                printf("Comando non valido\n");
            }
            break;
        case r_ordina_data:
            if (*ordinamento != 0) {
                ordinaData(tabella, nrighe);
                *ordinamento = 0;
            } else {
                printf("Tabella gia' ordinata per data\n");
            }
            break;
        case r_ordina_tratta:
            if (*ordinamento != 1) {
                ordinaTratta(tabella, nrighe);
                *ordinamento = 1;
            } else {
                printf("Tabella gia' ordinata per tratta\n");
            }
            break;
        case r_ordina_partenza:
            if (*ordinamento != 2) {
                ordinaPartenza(tabella, nrighe);
                *ordinamento = 2;
            } else {
                printf("Tabella gia' ordinata per stazione di partenza\n");
            }
            break;
        case r_ordina_arrivo:
            if (*ordinamento != 3) {
                ordinaArrivo(tabella, nrighe);
                *ordinamento = 3;
            } else {
                printf("Tabella gia' ordinata per stazione di arrivo\n");
            }
            break;
        case r_ricerca_partenza:
            sscanf(richiesta, "%s", fermata);
            ricercaPartenza(tabella, nrighe, fermata, *ordinamento);

    }
}

void stampaVideo(struct tratta tabella[], int nrighe) {
    int i;
    for (i = 0; i < nrighe; ++i) {
        printf("%s %s %s %s %s %s %d\n", tabella[i].codice_tratta, tabella[i].partenza, tabella[i].destinazione,
               tabella[i].data, tabella[i].ora_partenza, tabella[i].ora_arrivo, tabella[i].ritardo);
    }
}

void stampaFile(struct tratta tabella[], int nrighe) {
    FILE *fo;
    int i;
    fo = fopen("output.txt", "w");
    if (fo == NULL) {
        printf("Errore nell'apertura del file\n");
        return;
    }

    for (i = 0; i < nrighe; ++i) {
        fprintf(fo, "%s %s %s %s %s %s %d\n", tabella[i].codice_tratta, tabella[i].partenza, tabella[i].destinazione,
                tabella[i].data, tabella[i].ora_partenza, tabella[i].ora_arrivo, tabella[i].ritardo);
    }

    fclose(fo);
    printf("Tabella stampata nel file output.txt");

}

void ordinaData(struct tratta tabella[], int nrighe) {
    int i, j, l = 0, r = nrighe - 1;
    /*In questo caso viene utilizzato il bubble sort
     * visto che viene richiesta la stabilità dell'algoritmo.
     * Inoltre visto il formato della data aaaa/mm/gg viene utilizzata
     * la funzione strcmp per verificare quale data viene prima.
     * Analogamente per quanto riguarda le ore.
     */
    struct tratta temp;
    for (i = l; i < r; i++) {
        for (j = l; j < (r - i + l); j++)
            if (confrontaData(tabella[j], tabella[j + 1]) ) {
                temp = tabella[j];
                tabella[j] = tabella[j + 1];
                tabella[j + 1] = temp;
            }
    }
    printf("Tratte ordinate per data\n");
}

int confrontaData(struct tratta n1, struct tratta n2) {
    if (strcmp(n1.data, n2.data) > 0) {
        return 1;
    } else if (strcmp(n1.data, n2.data) == 0) //A parità di data controllo le ore
        if (strcmp(n1.ora_partenza, n2.ora_partenza) > 0) {
            return 1;
        }
    return 0;
}

void ordinaTratta(struct tratta tabella[], int nrighe) {
    int i, j, l = 0, r = nrighe - 1;
    struct tratta temp;
    for (i = l; i < r; i++) {
        for (j = l; j < (r - i + l); j++)
            if (strcmp(tabella[j].codice_tratta, tabella[j + 1].codice_tratta) > 0) {
                temp = tabella[j];
                tabella[j] = tabella[j + 1];
                tabella[j + 1] = temp;
            }
    }
    printf("Tratte ordinate per codice tratta\n");

}

void ordinaPartenza(struct tratta tabella[], int nrighe) {
    int i, j, l = 0, r = nrighe - 1;
    struct tratta temp;
    for (i = l; i < r; i++) {
        for (j = l; j < (r - i + l); j++)
            if (strcmp(tabella[j].partenza, tabella[j + 1].partenza) > 0) {
                temp = tabella[j];
                tabella[j] = tabella[j + 1];
                tabella[j + 1] = temp;
            }
    }
    printf("Tratte ordinate per nome partenza\n");
}

void ordinaArrivo(struct tratta tabella[], int nrighe) {
    int i, j, l = 0, r = nrighe - 1;
    struct tratta temp;
    for (i = l; i < r; i++) {
        for (j = l; j < (r - i + l); j++)
            if (strcmp(tabella[j].destinazione, tabella[j + 1].destinazione) > 0) {
                temp = tabella[j];
                tabella[j] = tabella[j + 1];
                tabella[j + 1] = temp;
            }
    }
    printf("Tratte ordinate per nome destinazione\n");
}

void ricercaPartenza(struct tratta tabella[], int nrighe, char fermata[], int ordinamento) {
    if (ordinamento == 2) {
        int inizio = 0;
        int fine = nrighe-1;
        int indice = ricercaPartDicotomica(tabella, inizio, fine, fermata);

        if(indice==-1){
            printf("L'elemento cercato non e' presente");
            return;
        }
        //La funzione seguente stampa tutte le tratte accettabili al di sopra o al di sotto del risultato della ricerca
        stampaRicerca(tabella, nrighe, indice, fermata);

    } else {
        ricercaPartLineare(tabella, nrighe, fermata);
    }
}

int ricercaPartDicotomica(struct tratta tabella[], int inizio, int fine, char fermata[]) {

    int m = (inizio + fine) / 2;
    if (m < inizio || fine < 0) {
        // l'elemento cercato non c'è
        return -1;
    } else if (strncmp(fermata, tabella[m].partenza, strlen(fermata)) < 0) {
        // Si ripete la ricerca nella parte inferiore
        return ricercaPartDicotomica(tabella, inizio, m - 1, fermata);
    } else if (strncmp(fermata, tabella[m].partenza, strlen(fermata)) > 0) {
        // Si ripete la ricerca nella parte superiore
        return ricercaPartDicotomica(tabella, m + 1, fine, fermata);
    } else {
        return m;
    }
}

void ricercaPartLineare(struct tratta tabella[], int nrighe, char fermata[]) {
    int i, j, valido = -1;
    for (i = 0; i < nrighe; i++) {
        if (tabella[i].partenza[0] == fermata[0]) {
            valido = 1;
            for (j = 1; j < strlen(fermata); j++) {
                if (tabella[i].partenza[j] != fermata[j]) {
                    valido = 0;
                }
            }
            if (valido == 1) {
                printf("%s %s %s %s %s %s %d\n", tabella[i].codice_tratta, tabella[i].partenza, tabella[i].destinazione,
                       tabella[i].data, tabella[i].ora_partenza, tabella[i].ora_arrivo, tabella[i].ritardo);
            }
        }
    }
    if (valido == -1) {
        printf("Nessuna corrispondenza\n");
    }
}

void stampaRicerca(struct tratta tabella[], int nrighe, int indice, char fermata[]) {
    int i = indice;
    //Risultato della ricerca
    printf("%s %s %s %s %s %s %d\n", tabella[i].codice_tratta, tabella[i].partenza, tabella[i].destinazione,
           tabella[i].data, tabella[i].ora_partenza, tabella[i].ora_arrivo, tabella[i].ritardo);
    i--;

    //Risultati superiori
    while (i >= 0 && strncmp(fermata, tabella[i].partenza, strlen(fermata)) == 0) {
        printf("%s %s %s %s %s %s %d\n", tabella[i].codice_tratta, tabella[i].partenza, tabella[i].destinazione,
               tabella[i].data, tabella[i].ora_partenza, tabella[i].ora_arrivo, tabella[i].ritardo);
        i--;
    }

    //Risultati inferiori
    i = indice + 1;
    while (i < nrighe && strncmp(fermata, tabella[i].partenza, strlen(fermata)) == 0) {
        printf("%s %s %s %s %s %s %d\n", tabella[i].codice_tratta, tabella[i].partenza, tabella[i].destinazione,
               tabella[i].data, tabella[i].ora_partenza, tabella[i].ora_arrivo, tabella[i].ritardo);
        i++;
    }

}