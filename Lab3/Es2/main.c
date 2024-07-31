#include <stdio.h>

void tipoCodifica(int *bigEndian);

void stampaCodifica(void *p, int size, int bigEndian);


void stampa(int size, unsigned char V[]);

int main() {
    float af;
    double ad;
    long double ald = 0;
    int bigEndian = 0;

    //Sovradimensiono il vettore in base alla dimensione del long double riconosciuta in precedenza
    unsigned char N[12];

    tipoCodifica(&bigEndian);
    if (bigEndian) {
        printf("Codifica BigEndian\n");
    } else {
        printf("Codifica LittleEndian\n");
    }

    printf("Size float %d\n", sizeof(af));
    printf("Size double %d\n", sizeof(ad));
    printf("Size long double %d\n", sizeof(ald));

    printf("\nInserisci un numero decimale\n");
    scanf("%s", N);

    /*Per problemi la parte relativa al tipo long double verrà
     * scritta come commento.

     sscanf(N, "%Lf", &ald);
    */

    sscanf(N, "%lf", &ad);

    sscanf(N, "%f", &af);

    printf("%f %lf %Lf\n", af, ad, ald);


    printf("Binario con codifica IEEE 754 \n");

    printf("\nCodifica float \n");
    stampaCodifica((void *) &af, sizeof(af), bigEndian);
    printf("\n*******************");
    printf("\nCodifica double \n");
    stampaCodifica((void *) &ad, sizeof(ad), bigEndian);


    printf("\n*******************");
    printf("\nCodifica long double \n");
    stampaCodifica((void *) &ald, sizeof(ald), bigEndian);


}

void tipoCodifica(int *bigEndian) {
    int x = 1;
    unsigned char *c;
    c = (unsigned char *) &x;

    /*Controllo se il primo byte è quello più significativo
     * in questo caso x occupa quattro byte quindi avrà 3 byte a 0 e l'ultimo
     * contiene \1 in binario. Di conseguenza il puntatore al primo elemento conterrà
     * 0 nel caso di bigEndian e 1 nel caso di littleEndian
     */
    if (*c == 0) {
        *bigEndian = 1;
    }
}

void stampaCodifica(void *p, int size, int bigEndian) {
    unsigned char *N;
    N = p;
    int i, j;
    int k = 0;

    //Per comodità viene creato un vettore di appoggio
    unsigned char numero[size];

    /*Se la codifica è di tipo bigEndian copio gli elementi del vettore nell'ordine in cui si trovano
     *altrimenti in ordine inverso.
     */
    if (bigEndian) {
        for (i = 0; i < size; i++) {
            numero[i] = N[i];
        }
    } else {
        j = size - 1;
        for (i = 0; i < size; i++) {
            numero[j] = N[i];
            j--;
        }
    }

    /*Con il vettore seguente vi sono 7 bit inutilizzati per ogni elemento del vettore
     *Non potendo creare un v ettore di bit si opta comunque per questa soluzione.
     */
    unsigned char V[8 * size];

    for (i = 0; i < size; i++) {
        for (j = 8 - 1; j >= 0; j--) {

            /*Per ogni byte vengono memorizzati i resti delle
             * in ordine decrescente ogni 8 'bit
             */
            V[j + k] = numero[i] % 2;
            numero[i] = numero[i] / 2;
        }
        k = k + 8;
    }

    stampa(size, V);

}


void stampa(int size, unsigned char V[]) {
    int i;

    printf("[Segno][Esponente][Mantissa]\n");

    //Controllo la dimensione in byte della variabile e stampo le varie parti seguendo le regole della codifica

    switch (size) {
        case 4:
            printf("[%d]", V[0]);
            printf(" [");
            for (i = 1; i <= 8; i++) {
                printf("%d ", V[i]);
            }
            printf("] [");
            for (i = 9; i < 32; i++) {
                printf("%d ", V[i]);
            }
            printf("] \n");

            break;

        case 8:
            printf("[%d]", V[0]);
            printf(" [");
            for (i = 1; i <= 11; i++) {
                printf("%d ", V[i]);
            }
            printf("] [");
            for (i = 12; i < 64; i++) {
                printf("%d ", V[i]);
            }
            printf("] \n");
            break;

        /*
        case 12:
            printf("Segno: %d\n", V[0]);
            printf("Esponente: ");
            for (i = 1; i <= 15; i++) {
                printf("%d ", V[i]);
            }
            printf("\nMantissa: ");
            for (i = 16; i < 96; i++) {
                printf("%d ", V[i]);
            }
            printf("] \n");
            break;

            //Analogamente per il caso con 16 byte
        */

        default:
            printf("Formato non supportato dal programma\n");
            break;
    }
}