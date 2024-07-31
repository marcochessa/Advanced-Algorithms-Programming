#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

int main() {
    int continua = 1;
    comando_e com;
    TabPg tabPg;
    TabInv tabInv;

    tabInv=creaTabInv();
    tabPg=creaTabPg();

    caricaPersonaggi(tabPg);
    caricaInventario(tabInv);

    printf("Totale personaggi:%d\n",getNumPg(tabPg));

    while (continua) {
        com = leggiComando();
        if (com == r_fine) {
            continua = 0;
        } else if (com == r_err) {
            printf("comando inserito non valido\n");
        } else {
            istruzione(com, tabPg, tabInv);
        }
    }

    liberaInventario(tabInv);
    freeTabPg(tabPg);

    return 0;
}