#include <stdio.h>
#include <mem.h>
#include <malloc.h>


typedef struct {
    char **scelte;
    char *nome;
    int num_scelte;
} scelte;

typedef struct {
    char *canzone;
    char *nome;
} playlist;

int combinazioni(int pos, scelte *elenco, playlist *el_canzoni, int n, int count);

int main() {
    FILE *fp;
    scelte *elenco;
    playlist *el_canzoni;
    char stringTmp[255];
    char nomeTmp[50];

    int A;
    int C;
    fp = fopen("brani.txt", "r");

    if (fp == NULL) {
        printf("Impossibile aprire file");
        return 1;
    }

    fscanf(fp, "%d", &A);


    elenco= malloc(A* sizeof(scelte));
    el_canzoni= malloc(A* sizeof(playlist));

    /*Parte aggiuntiva, per offrire la possibilità di tenere memoria di chi ha scelto una determinata canzone,
     * vengono letti dalla prima riga i nomi degli utenti che hanno effettuato delle proposte.
     */
    for (int i = 0; i < A; i++) {
        fscanf(fp,"%s", nomeTmp);
        //Alloco dinamicamente lo spazio riservato al nome
        elenco[i].nome = strdup(nomeTmp);
    }

    for (int i = 0; i < A; i++) {
        fscanf(fp, "%d", &C);
        elenco[i].num_scelte = C;
        //Alloco dinamicamente la memoria necessaria a tenere traccia dei puntatori ai titoli delle tracce
        elenco[i].scelte=malloc(C* sizeof(char*));
        for (int j = 0; j < C; j++) {
            fscanf(fp, "%s", stringTmp);
            //Alloco dinamicamente lo spazio riservato al nome della canzone
            elenco[i].scelte[j] = strdup(stringTmp);
        }
    }

    int occ=combinazioni(0,elenco,el_canzoni,A,0);

    /*Per verifica-> il numero "occ" deve essere uguale alla moltiplicazine fra il numero di scelte per
     * ogni amico, per il PRINCIPIO DI MOLTIPLICAZIONE.
     */
    printf("\nNumero playlist %d", occ);

    free(elenco);
    free(el_canzoni);

    return 0;
}


int combinazioni(int pos, scelte *elenco, playlist *el_canzoni, int n, int count) {
    int i;
    if (pos >= n) {
        printf("\n--- PLAYLIST %d ---\n",count);
        for (i = 0; i < n; i++)
            printf("%s --> %s \n", el_canzoni[i].nome, el_canzoni[i].canzone);
        printf("\n");
        return count + 1;
    }

    for (i = 0; i < elenco[pos].num_scelte; i++) {
        el_canzoni[pos].canzone = elenco[pos].scelte[i];
        el_canzoni[pos].nome=elenco[pos].nome;
        count = combinazioni(pos + 1, elenco, el_canzoni, n, count);
    }
    return count;
}
