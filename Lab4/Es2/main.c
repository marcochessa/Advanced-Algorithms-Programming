#include <stdio.h>

int majority(int *a, int N);

int main() {
    int N = 9;
    int vet[9] = {4, 4, 5, 5, 4, 5, 4, 5, 5};

    int mag = majority(vet, N);

    if (mag != -1) {
        printf("Elemento maggioritario: %d\n", mag);
    } else {
        printf("Nessun elemento maggioritario\n");
    }
    return 0;
}

int majority(int *a, int N) {
    int m1, m2, i;
    int occ = 0;
    if (N == 1) {
        return *a;
    }
    //Controllo la metà di sinistra
    m1 = majority(a, N / 2);



    //Controllo la metà di destra
    if (N % 2 == 1) //Nel caso di vettore dispari
        m2 = majority(a + N / 2, (N / 2) + 1);
    else
        m2 = majority(a + N / 2, N / 2);

    if (m1 == m2) {
        return m1;
    }


    if (m1 != -1) {
        occ = 0;
        for (i = 0; i < N; i++) {
            if (a[i] == m1) {
                occ++;
            }
            if (occ > N / 2) {
                return m1;
            }
        }
    }

    if (m2 != -1) {
        occ = 0;
        for (i = 0; i < N; i++) {
            if (a[i] == m2) {
                occ++;
            }
            if (occ > N / 2) {
                return m2;
            }
        }
    }

    return -1;
}
