#include <stdio.h>
#include <malloc.h>
#include <mem.h>

typedef struct Item {
    char codice[6];
    char nome[51];
    char cognome[51];
    char data[11];
    char via[51];
    char citta[51];
    int cap;
} Item;

typedef struct node *link;

struct node {
    Item val;
    link next;
};

/*Visto che nel programma richiesto la lista viene analizzata attraverso diversi fattori(data/codice) si è
 * optato per mantenere fra i parametri delle funzioni le stringhe relative ai parametri di ricerca.
 * Rinunciando così al livello di astrazione offerto dalla struct Key vista a lezione.
 */

typedef enum {
    r_inserisci_file, r_inserisci_tastiera, r_ricerca, r_estrai_codice, r_estrai_date, r_stampa, r_fine, r_err
} comando_e;

comando_e leggiComando(void);

void istruzione(comando_e codiceComando, link *head);

link newNode(Item val, link next);

link SortListIns(link h, Item val);

Item listSearch(link h, char *codice);

Item listExtrKeyP(link *hp, char *codice);

Item SortListExtrDate(link *hp, char *d1, char *d2);

int greaterDate(char *d1, char *d2);

int dateValide(char *data1, char *data2);

int eqCod(char *codice1, char *codice2);

void stampaLista(link h, FILE *fo);

int main() {

    int continua = 1;
    link head = NULL;

    while (continua == 1) {
        comando_e comando = leggiComando();
        if (comando == r_fine) {
            continua = 0;
        } else if (comando == r_err) {
            printf("Comando inserito non valido\n");
        } else {
            istruzione(comando, &head);
        }
    }


    return 0;
}

comando_e leggiComando(void) {
    comando_e c;
    char cmd[200];
    char tabella[r_err][50] = {"inserisci_file", "inserisci_tastiera", "ricerca_codice", "estrai_codice",
                               "estrai_date", "stampa_lista", "fine"};

    printf("*****************************"
           "\nInserisci comando: "
           "\n-->\"inserisci_file\" (aggiorna la lista da file), "
           "\n-->\"inserisci_tastiera\" (aggiorna la lista da tastiera), "
           "\n-->\"ricerca_codice\" (ricerca nella lista l'elemento con il codice dato),"
           "\n-->\"estrai_codice\" (estrae dalla lista l'elemento con il codice dato), "
           "\n-->\"estrai_date\" (estrae dalla lista gli elementi nati in un intervallo di date), "
           "\n-->\"stampa_lista\" (stampa l'intera lista su file), "
           "\n-->\"fine\"\n");

    scanf("%s", cmd);

    //Si presume un inserimento del comando con tutti i caratteri minuscoli;
    c = r_inserisci_file;
    while (c < r_err && strcmp(cmd, tabella[c]) != 0)
        c++;
    return c;

}

int greaterDate(char *d1, char *d2) {
    //Restituisce VERO se d1 è la data più remota
    int gg1, mm1, aa1;
    int gg2, mm2, aa2;
    sscanf(d1, "%d/%d/%d", &gg1, &mm1, &aa1);
    sscanf(d2, "%d/%d/%d", &gg2, &mm2, &aa2);
    if (aa1 < aa2) {
        return 1;
    }
    if (aa1 > aa2) {
        return 0;
    }
    if (mm1 < mm2) {
        return 1;
    }
    if (mm1 > mm2) {
        return 0;
    }
    if (gg1 < gg2) {
        return 1;
    }
    if (gg1 > gg2) {
        return 0;
    }

    //Nel caso di date uguali viene ritornato VERO ma poteva essere gestito analogamente ritornando FAlSO o altro valore
    return 1;
}

int dateValide(char *data1, char *data2){
    if(strcmp(data1,data2)!=0) {
        //Se le date sono diverse e data1 è più remota di data2 allora l'intervallo non è valido
        if (greaterDate(data1, data2)) {
            return 0;
        }
    }
    return 1;
}

void istruzione(comando_e codiceComando, link *head) {
    FILE *fp;
    link *provv;
    char data1[11], data2[11];
    char codice[6];
    Item tmp;
    char nome[30];
    FILE *fo;


    switch (codiceComando) {
        case r_inserisci_file:
            printf("Inserire nome file\n");
            scanf("%s", nome);

            fp = fopen(nome, "r");
            if (fp == NULL) {
                printf("Impossibile aprire file\n");
                break;
            }

            while (!feof(fp)) {
                //Per semplificare il codice non viene effettuata l'allocazione dinamica delle stringhe della struct
                fscanf(fp, "%s %s %s %s %s %s %d", tmp.codice, tmp.nome, tmp.cognome, tmp.data, tmp.via,
                       tmp.citta, &tmp.cap);

                *head = SortListIns(*head, tmp);
            }
            fclose(fp);
            printf("Inseriti valori da file\n");
            break;

        case r_inserisci_tastiera:
            printf("Inserisci stringa:\n <codice> <nome> <cognome> <data_nasc> <via> <citta'> <cap>\n");
            scanf("%s %s %s %s %s %s %d", tmp.codice, tmp.nome, tmp.cognome, tmp.data, tmp.via,
                  tmp.citta, &tmp.cap);

            *head = SortListIns(*head, tmp);

            printf("Inserito valore da tastiera\n");
            break;

        case r_ricerca:
            printf("Inserisci il codice da cercare\n");
            scanf("%s", codice);

            tmp = listSearch(*head, codice);
            if (tmp.cap == -1) {
                printf("Elemento non presente in lista\n");
                break;
            }
            printf("%s %s %s %s %s %s %d\n", tmp.codice, tmp.nome, tmp.cognome, tmp.data, tmp.via,
                   tmp.citta, tmp.cap);
            break;

        case r_estrai_codice:
            printf("Inserisci il codice da cercare ed estrarre\n");
            scanf("%s", codice);
            tmp = listExtrKeyP(head, codice);
            if (tmp.cap == -1) {
                printf("Elemento non presente in lista\n");
                break;
            }
            printf("%s %s %s %s %s %s %d\n", tmp.codice, tmp.nome, tmp.cognome, tmp.data, tmp.via,
                   tmp.citta, tmp.cap);
            break;

        case r_estrai_date:
            /*Si sfrutta il fatto che la lista sia ordinata, utilizzando un puntatore provvisorio, durante la ricerca
             * il puntatore viene aggiornato. Quindi viene considerata una "sottolista" di dimensioni
             * sempre inferiori a ogni iterazione della chiamata.
             * Nel caso in cui siano finiti gli elementi interni all'intervallo, o nel caso in cui non vi siano
             * elementi presenti, viene restituito un Item nullo, in questo caso la ricerca viene terminata.
             */
            provv = head;
            printf("Inserisci l'intervallo di date da <gg/mm/aaaa> a <gg/mm/aaaa>\n");
            //Visto che la lista è ordinata in ordine decrescente di anzianità, vengono invertite le date sottostanti
            scanf("%s %s", data2, data1);

            //Controllo la validità delle date
            if(!dateValide(data1,data2)){
                printf("Intervallo di date non valido\n");
                break;
            }

            tmp = SortListExtrDate(provv, data1, data2);
            if (tmp.cap == -1) {
                printf("Nessun elemento presente, nell'intervallo scelto, in lista\n");
                break;
            } else {
                while (tmp.cap != -1) {
                    printf("%s %s %s %s %s %s %d\n", tmp.codice, tmp.nome, tmp.cognome, tmp.data, tmp.via,
                           tmp.citta, tmp.cap);
                    tmp = SortListExtrDate(provv, data1, data2);
                }
            }
            break;

        case r_stampa:
            fo=fopen("output.txt","w");
            if(fo==NULL){
                printf("Impossibile aprire file\n");
                break;
            }
            stampaLista(*head, fo);
            fclose(fo);
            printf("Lista stampata su file output.txt\n");
            break;
    }
}

int eqCod(char *codice1, char *codice2) {
    //Questa funzione è superflua, viene implementata esclusivamente per facilitare una futura modifica del codice
    if (strcmp(codice1, codice2) == 0)
        return 1;
    return 0;
}

Item ITEMsetvoid() {
    Item i;
    strcpy(i.codice, "");
    strcpy(i.data, "");
    strcpy(i.nome, "");
    strcpy(i.cognome, "");
    strcpy(i.citta, "");
    i.cap = -1;
    return i;
}

link newNode(Item val, link next) {
    link x = malloc(sizeof(*x));
    if (x == NULL)
        return NULL;
    x->val = val;
    x->next = next;
    return x;
}

//INSERZIONE IN TESTA ORDINATA PER DATA
link SortListIns(link h, Item val) {
    link x, p;

    if (h == NULL || greaterDate(h->val.data, val.data))
        return newNode(val, h);
    for (x = h->next, p = h;
         x != NULL && greaterDate(val.data, x->val.data);
         p = x, x = x->next);
    p->next = newNode(val, x);
    return h;
}

//RICERCA PER CODICE
Item listSearch(link h, char *codice) {
    link x;
    for (x = h; x != NULL; x = x->next)
        if (eqCod(x->val.codice, codice))
            return x->val;
    return ITEMsetvoid();
}

//ESTRAZIONE DALLA LISTA PER CODICE
Item listExtrKeyP(link *hp, char *codice) {
    link *xp, t;
    Item i = ITEMsetvoid();
    for (xp = hp; (*xp) != NULL; xp = &((*xp)->next)) {
        if (eqCod((*xp)->val.codice, codice)) {
            t = *xp;
            *xp = (*xp)->next;
            i = t->val;
            free(t);
            break;
        }
    }
    return i;
}

//ESTRAZIONE DALLA LISTA PER INTERVALLO DI DATE
Item SortListExtrDate(link *hp, char *d1, char *d2) {
    link t;
    Item i = ITEMsetvoid();
    if (*hp == NULL)
        return i;

    //Se la lista è nulla o se la data corrente è meno recente della data d2 dell'intervallo termino il ciclo
    while ((*hp) != NULL && greaterDate(d2, (*hp)->val.data)) {
        if (greaterDate((*hp)->val.data, d1)) {
            t = *hp;
            //Aggiorno il valore del nodo puntato al nodo successivo, estraendo così l'elemento "t"
            *hp = (*hp)->next;
            i = t->val;
            free(t);
            break;
        }
        //Mi sposto sul nodo successivo
        hp = &((*hp)->next);
    }

    return i;
}

void stampaLista(link x, FILE *fo) {
    if (x == NULL) {
        return;
    }
    fprintf(fo, "%s %s %s %s %s %s %d\n", x->val.codice, x->val.nome, x->val.cognome,
            x->val.data, x->val.via, x->val.citta, x->val.cap);

    x = x->next;
    stampaLista(x, fo);
}

