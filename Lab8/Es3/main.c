#include <stdio.h>
#include <mem.h>
#include "personaggio.h"
#include "inventario.h"

typedef enum {
    r_inserisci_personaggio, r_rimuovi_personaggio, r_equipaggia_oggetto,
    r_sottrai_oggetto, r_stampa_statistiche, r_dettagli_oggetto, r_fine, r_err
} comando_e;

comando_e leggiComando(void);


void istruzione(comando_e codiceComando, tabPg_t *tabPg, tabInv_t *tabInv);

int main() {
    int continua = 1;
    comando_e com;
    tabPg_t tabPg;
    tabPg.headPg = NULL;
    tabPg.tailPg = NULL;
    tabPg.nPg = 0;

    tabInv_t tabInv;
    caricaPersonaggi(&tabPg);
    caricaInventario(&tabInv);

    printf("Totale personaggi:%d\n",tabPg.nPg);

    while (continua) {
        com = leggiComando();
        if (com == r_fine) {
            continua = 0;
        } else if (com == r_err) {
            printf("comando inserito non valido\n");
        } else {
            istruzione(com, &tabPg, &tabInv);
        }
    }

    liberaInventario(&tabInv);

    return 0;
}

comando_e leggiComando(void) {
    comando_e c;
    char cmd[100];
    char tabella[r_err][50] = {"inserisci_personaggio",
                               "rimuovi_personaggio",
                               "equipaggia_oggetto",
                               "sottrai_oggetto",
                               "stampa_stat",
                               "dettagli_oggetto",
                               "fine"};

    printf("*****************************"
           "\nInserisci comando: "
           "\n-->\"inserisci_personaggio\", "
           "\n-->\"rimuovi_personaggio\", "
           "\n-->\"equipaggia_oggetto\" (assegna un oggetto dell'inventario a un personaggio dato),"
           "\n-->\"sottrai_oggetto\" (sottrae un oggetto a un personaggio dato), "
           "\n-->\"stampa_stat\" (stampa le statistiche di un personaggio dato), "
           "\n-->\"dettagli_oggetto\" (stampa i dettagli di un oggetto),"
           "\n-->\"fine\"\n");

    scanf("%s", cmd);

    //Si presume un inserimento del comando con tutti i caratteri minuscoli;
    c = r_inserisci_personaggio;
    while (c < r_err && strcmp(cmd, tabella[c]) != 0)
        c++;
    return c;

}

void istruzione(comando_e codiceComando, tabPg_t *tabPg, tabInv_t *tabInv) {
    pg_t pgTmp;
    char nomeAccessorio[50];
    switch (codiceComando) {
        case r_inserisci_personaggio:
            printf("Inserire dati personaggio\n"
                   "<codice> <nome> <classe>\n");
            scanf("%s %s %s", pgTmp.codice, pgTmp.nome, pgTmp.classe);
            printf("Inserire statistiche personaggio\n"
                   "<hp> <mp> <atk> <def> <mag> <spr>\n");
            scanf("%d %d %d %d %d %d", &pgTmp.stat.hp, &pgTmp.stat.mp, &pgTmp.stat.atk, &pgTmp.stat.def,
                  &pgTmp.stat.mag, &pgTmp.stat.spr);
            pgTmp.equip.inUso = 0;
            if (pgPresente(tabPg, pgTmp.codice)==0){
                listInsTailFast(tabPg, pgTmp);
                printf("Personaggio %s aggiunto\n", pgTmp.codice);
                printf("Totale personaggi:%d\n",tabPg->nPg);
            } else
                printf("Codice personaggio gia' presente in lista\n");
            break;

        case r_rimuovi_personaggio:
            printf("Inserire il codice del personaggio da rimuovere\n");
            scanf("%s", pgTmp.codice);
            if (listDelKey(tabPg, pgTmp.codice))
                printf("Personaggio %s rimosso\n", pgTmp.codice);
            else
                printf("Non e' possibile rimuovere il personaggio indicato\n");
            break;

        case r_equipaggia_oggetto:
            printf("Inserire il codidce del personaggio a cui equipaggiare\n");
            scanf("%s", pgTmp.codice);
            eqPersonaggio(pgTmp.codice, tabPg, tabInv);
            break;

        case r_sottrai_oggetto:
            printf("Inserire il codidce del personaggio a cui disequipaggiare un oggetto\n");
            scanf("%s", pgTmp.codice);
            disEqPersonaggio(pgTmp.codice, tabPg, tabInv);
            break;

        case r_stampa_statistiche:
            printf("Inserire il codidce del personaggio di cui vuoi conoscere i dati\n");
            scanf("%s", pgTmp.codice);
            stampaDettagliPg(pgTmp.codice, *tabPg);
            break;

        case r_dettagli_oggetto:
            printf("Inserire il nome dell'oggetto di cui vuoi conoscere i dati\n");
            scanf("%s", nomeAccessorio);
            stampaDettagliOggetto(nomeAccessorio, *tabInv);
            break;

    }
}