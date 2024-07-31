#include <stdio.h>
#include <ctype.h>
#include <mem.h>
#include "titoli.h"
#include "quotazioni.h"

#define MAXL 21

int main() {
    FILE *fp;
    int sel;
    char tit[MAXL], date[MAXL], date2[MAXL];

    int stop = 0;

    titList tList = listInit();
    title t = NULL;
    quota tmp;
    fp = fopen("F1.txt", "r");
    if (fp == NULL)
        return -1;
    loadTitle(fp, tList);
    fclose(fp);


    do {
        printf("\nQuale operazione vuoi eseguire?\n");
        printf("\t1: Ricerca titolo\n");
        printf("\t2: Ricerca, cercato un titolo, la sua quot in una certa data\n");
        printf("\t3: Ricerca, cercato un titolo, la sua quot  min e max in una intervallo di date\n");
        printf("\t4: Ricerca, cercato un titolo, la sua quot  min e max in assoluto\n");
        printf("\t5: Bilancia, cercato un titolo, il suo albero delle quotazioni\n");
        printf("\t9: Esci\n");
        scanf("%d", &sel);

        switch (sel) {
            case 1: {
                printf("Quale titolo vuoi cercare?\n");
                scanf("%s", tit);
                t = searchTitle(tList, tit);
                if (titleGetKey(t) == NULL) {
                    printf("Titolo non presente in lista\n");
                    break;
                }
                printf("Titolo trovato: %s\n", titleGetKey(t));
            }
                break;
            case 2: {
                if (t == NULL) {
                    printf("Nessun titolo selezionato\n");
                    break;
                }
                printf("Inserisci una data da esaminare\n");
                scanf("%s", date);

                tmp = getDateQuotation(t, date);
                printf("Quota cercata:\n");
                if (tmp->val == -1) {
                    printf("Quotazione non trovata\n");
                    break;
                }
                printInfoQuot(tmp);
                break;
            }
            case 3:
                if (t == NULL) {
                    printf("Nessun titolo selezionato\n");
                    break;
                }
                printf("Inserisci un intervallo di date da esaminare\n");
                scanf("%s %s", date, date2);

                getBetweenDateQuotation(t, date, date2);
                break;
            case 4:
                if ((t) == NULL) {
                    printf("Nessun titolo selezionato\n");
                    break;
                }
                getMaxMinQuotation(t);
                break;
            case 5:
                if ((t) == NULL) {
                    printf("Nessun titolo selezionato\n");
                    break;
                }
                int soglia;
                printf("Inserisci una soglia per il bilanciamento\n");
                scanf("%d", &soglia);
                quotBalance(t, soglia);
                break;
            case 9: {
                stop = 1;
            }
                break;
            default:
                printf("Scelta non valida!\n");
        }
    } while (!stop);

    tFree(tList);
    return 0;
}

