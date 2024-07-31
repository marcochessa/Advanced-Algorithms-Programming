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
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine, r_err
} comando_e;

comando_e leggiComando(void);

void selezionaDati(comando_e codiceComando, struct tratta tabella[], char richiesta[], int nrighe);

void date(struct tratta tabella[], int nrighe, char data_inizio[], char data_fine[]);

void partenza(struct tratta tabella[], int nrighe, char fermata[]);

void capolinea(struct tratta tabella[], int nrighe, char fermata[]);

void ritardo(struct tratta tabella[], int nrighe, char data_inizio[], char data_fine[]);

void ritardoTot(struct tratta tabella[], int nrighe, char codice_tratta[]);

int confrontaData(int Vett_inizio[], int Vett_contr[], int Vett_fine[]);

void convertiData(char data[], int Vett[]);

int main() {
    FILE *fp;
    int nrighe;
    int i;
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


    while (continua) {
        codiceComando = leggiComando();
        //Gestisco i comandi non validi e quello di fine dal main gli altri tramite la funzione selezionaDati
        if (codiceComando == r_err) {
            printf("Comando inserito non valido");
        } else if (codiceComando == r_fine) {
            continua = 0;
        } else {
            gets(richiesta); //copio il resto della richiesta

            selezionaDati(codiceComando, tabella, richiesta, nrighe);

        }
        printf("\n***************************************************\n");
    }

    return 0;
}

comando_e leggiComando(void) {
    comando_e c;
    char cmd[L];
    char tabella[r_err][L] = {"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};
    printf("Inserisci comando: \"date\", \"partenza\", \"capolinea\", \"ritardo\", \"ritardo_tot\" e \"fine\"\n");
    scanf("%s", cmd);

    //Si presume un inserimento del comando con tutti i caratteri minuscoli;
    c = r_date;
    while (c < r_err && strcmp(cmd, tabella[c]) != 0)
        c++;
    return c;

}

void selezionaDati(comando_e codiceComando, struct tratta tabella[], char richiesta[], int nrighe) {
    char data_inizio[Max], data_fine[Max];
    char fermata[Max];
    char codice_tratta[Max];

    switch (codiceComando) {
        case r_date:
            sscanf(richiesta, "%s %s", data_inizio, data_fine);
            date(tabella, nrighe, data_inizio, data_fine);
            break;
        case r_partenza:
            sscanf(richiesta, "%s", fermata);
            partenza(tabella, nrighe, fermata);
            break;
        case r_capolinea:
            sscanf(richiesta, "%s", fermata);
            capolinea(tabella, nrighe, fermata);
            break;
        case r_ritardo:
            sscanf(richiesta, "%s %s", data_inizio, data_fine);
            ritardo(tabella, nrighe, data_inizio, data_fine);
            break;
        case r_ritardo_tot:
            sscanf(richiesta, "%s", codice_tratta);
            ritardoTot(tabella, nrighe, codice_tratta);
            break;
    }
}

void date(struct tratta tabella[], int nrighe, char data_inizio[], char data_fine[]) {
    int i;
    int Vett_inizio[3];
    int Vett_fine[3];
    int Vett_contr[3];
    int flag;
    convertiData(data_inizio, Vett_inizio);
    convertiData(data_fine, Vett_fine);

    for (i = 0; i < nrighe; i++) {
        if (tabella[i].ritardo > 0) {
            convertiData(tabella[i].data, Vett_contr);
            flag = confrontaData(Vett_inizio, Vett_contr, Vett_fine);
        }
        if (flag == 1) {
            printf("Codice: %s Destinazione: %s Data: %s\n", tabella[i].codice_tratta, tabella[i].destinazione,
                   tabella[i].data);
        }
    }
}

void partenza(struct tratta tabella[], int nrighe, char fermata[]) {
    int i;
    printf("fermata: %s\n", fermata);
    for (i = 0; i < nrighe; i++) {
        if (strcmp(tabella[i].partenza, fermata) == 0) {
            printf("Codice: %s Destinazione: %s Data: %s\n", tabella[i].codice_tratta, tabella[i].destinazione,
                   tabella[i].data);
        }
    }
}

void capolinea(struct tratta tabella[], int nrighe, char fermata[]) {
    int i;
    printf("fermata: %s\n", fermata);
    for (i = 0; i < nrighe; i++) {
        if (strcmp(tabella[i].destinazione, fermata) == 0) {
            printf("Codice: %s Partenza: %s Data: %s\n", tabella[i].codice_tratta, tabella[i].partenza,
                   tabella[i].data);
        }
    }
}

void ritardo(struct tratta tabella[], int nrighe, char data_inizio[], char data_fine[]) {
    int i;
    int Vett_inizio[3];
    int Vett_fine[3];
    int Vett_contr[3];
    int flag;
    convertiData(data_inizio, Vett_inizio);
    convertiData(data_fine, Vett_fine);

    for (i = 0; i < nrighe; i++) {
        if (tabella[i].ritardo > 0) {
            convertiData(tabella[i].data, Vett_contr);
            flag = confrontaData(Vett_inizio, Vett_contr, Vett_fine);

            if (flag == 1) {
                printf("Codice: %s Destinazione: %s Data: %s Ritardo: %d min \n", tabella[i].codice_tratta,
                       tabella[i].destinazione, tabella[i].data, tabella[i].ritardo);
            }
        }
    }
}

void ritardoTot(struct tratta tabella[], int nrighe, char codice_tratta[]) {
    int i;
    int ritardoTOT = 0;
    for (i = 0; i < nrighe; i++) {
        if (strcmp(tabella[i].codice_tratta, codice_tratta) == 0) {
            //Si presume da un punto di vista computazionale che sommare zero sia migliore di verificare l'effettivo ritardo
            ritardoTOT += tabella[i].ritardo;
        }
    }
    printf("Ritardo totale sulla tratta %s risulta:%d min\n", codice_tratta, ritardoTOT);
}


int confrontaData(int Vett_inizio[], int Vett_contr[], int Vett_fine[]) {
    int valido = 1;
    for (int j = 0; j < 3 && valido == 1; j++) {
        if (Vett_contr[j] < Vett_inizio[j] || Vett_contr[j] > Vett_fine[j]) {
            valido = 0;
        } else if (Vett_fine[j] > Vett_contr[j]) {
            /*Se l'anno/mese/giorno della data da controllare è maggiore uguale della data di inizio
             * ma è strettamente minore della data finale non ho motivo di effettuare ulteriori controlli
             */
            return valido;
        }
    }
    return valido;
}

void convertiData(char data[], int Vett[]) {
    sscanf(data, "%4d/%2d/%2d", &Vett[0], &Vett[1], &Vett[2]);
}