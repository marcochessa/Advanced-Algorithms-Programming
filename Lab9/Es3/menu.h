//
// Created by marco on 13/12/2018.
//

#ifndef ESERCIZIO3_MENU_H
#define ESERCIZIO3_MENU_H

#include "pgList.h"

typedef enum {
    r_inserisci_personaggio, r_rimuovi_personaggio, r_equipaggia_oggetto,
    r_sottrai_oggetto, r_stampa_statistiche, r_dettagli_oggetto, r_fine, r_err
} comando_e;

void allocaStruct(TabPg *tabPg, TabInv *tabInv);

comando_e leggiComando(void);

void istruzione(comando_e codiceComando, TabPg tabPg, TabInv tabInv);

#endif //ESERCIZIO3_MENU_H
