#include <stdio.h>

#define K 50+1


struct regione {
    int base;
    int altezza;
    int area;
    int XY[2];
};


void riempiMatrice(FILE *fp, int M[K][K], int nc, int nr);

void ricerca(FILE *fp, int M[K][K], int nr, int nc, struct regione MaxReg[]);

int contaArea(int M[K][K], int i, int j, int cord[2]);

void aggiornaMax(int cord[2], struct regione MaxReg[], int i, int j);

int main() {

    //Creo una matrice con una riga e una colonna in più in modo da semplificare i controlli
    int M[K][K] = {0};
    FILE *fp;
    int nc, nr;

    struct regione MaxReg[3];

    fp = fopen("mappa.txt", "r");

    if (fp == NULL) {
        printf("Errore nella lettura del file");
        return 1;
    }

    fscanf(fp, "%d %d", &nr, &nc);

    //Inserisco i valori del file nella matrice creata
    riempiMatrice(fp, M, nr, nc);

    fclose(fp);

    //Ricerco le regioni e aggiorno le regioni delle dimensioni maggiori
    ricerca(fp, M, nr, nc, MaxReg);

    //Stampo Risultati
    printf("Max Base: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", MaxReg[0].XY[0], MaxReg[0].XY[1], MaxReg[0].base,
           MaxReg[0].altezza, MaxReg[0].area);
    printf("Max Altezza: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", MaxReg[1].XY[0], MaxReg[1].XY[1], MaxReg[1].base,
           MaxReg[1].altezza, MaxReg[1].area);
    printf("Max Area: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", MaxReg[2].XY[0], MaxReg[2].XY[1], MaxReg[2].base,
           MaxReg[2].altezza, MaxReg[2].area);


    return 0;
}


void riempiMatrice(FILE *fp, int M[K][K], int nr, int nc) {
    int i, j;
    for (i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            //Non si effettuano ulteriori controlli perchè il file non contiene errori
            fscanf(fp, "%d", &M[i][j]);
        }
    }

}

void ricerca(FILE *fp, int M[K][K], int nr, int nc, struct regione MaxReg[]) {
    int dim[2];
    int n;
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            if (M[i][j] == 1) {
                //Si conta la grandezza della regione e si trasla j in modo da evitare alcuni controlli superflui
                n = contaArea(M, i, j, dim);
                aggiornaMax(dim, MaxReg, i, j);
                j = j + n;
            }
        }
    }
}


int contaArea(int M[K][K], int i, int j, int cord[2]) {
    int base = 1, altezza = 1;
    int finito = 0;
    while (!finito) {
        if (M[i][j + 1] == 1) {
            base++;
            j++;
        } else if (M[i + 1][j] == 1) {
            altezza++;
            i++;
        } else {
            finito = 1;
        }
    }
    cord[0] = base;
    cord[1] = altezza;
    return base;
}

void aggiornaMax(int cord[2], struct regione MaxReg[], int i, int j) {
    if (cord[0] > MaxReg[0].base) {
        MaxReg[0].base = cord[0];
        MaxReg[0].altezza = cord[1];
        MaxReg[0].area = cord[0] * cord[1];

        MaxReg[0].XY[0] = i;
        MaxReg[0].XY[1] = j;
    }
    if (cord[1] > MaxReg[1].altezza) {
        MaxReg[1].base = cord[0];
        MaxReg[1].altezza = cord[1];
        MaxReg[1].area = cord[0] * cord[1];

        MaxReg[1].XY[0] = i;
        MaxReg[1].XY[1] = j;
    }
    if ((cord[1] * cord[0]) > MaxReg[2].area) {
        MaxReg[2].base = cord[0];
        MaxReg[2].altezza = cord[1];
        MaxReg[2].area = cord[0] * cord[1];

        MaxReg[2].XY[0] = i;
        MaxReg[2].XY[1] = j;
    }

}