#include <stdio.h>
#include <mem.h>
#include <ctype.h>

char *cercaRegexp(char *src, char *regexp);

int corrisponde(char *src, char *regexp, int *j);

int main() {
    //Viene considerata la possibilità di avere una stringa con più parole come sorgente
    char *src="Aolo noto loko Foto";
    char *regexp="\\ao[^t].";

    /*Vengono stampate tutti i caratteri successivi all'occorrenza.
     * Se richiesto l'output sarebbe facilmente modificabile in modo da stampare
     * solo la parola che ha dato esito positivo alla ricerca*/
    printf("%s", cercaRegexp(src, regexp));

    return 0;
}

char *cercaRegexp(char *src, char *regexp) {
    char *occorrenza;
    int j = 0;
    int lenRg = strlen(regexp);
    while (*src != '\0') {
        if (j < lenRg) {
            if (j == 0) {
                occorrenza = src;
            }
            /* Nel controllo se la lettera non rispetta la corrispondenza o se si ha un carattere di spaziatura
             * l'occorrenza viene portata a NULL e l'indice del vettore della stringa da cercare viene portato a 0
             * In questo caso si considera che fra i caratteri ricoperti da '.' non rientrino i caratteri di spaziatura.
             */
            if (!corrisponde(src, regexp, &j)) {
                //Visto che la parola non corrisponde, sposto il puntatore fino al prossimo spazio
                while(!isspace(*src)){
                    src = src+1;
                }
            }
            if (isspace(*src)) {
                occorrenza = NULL;
                j = 0;
            }

        } else {
            return occorrenza;
        }

        src = src + 1;
    }
    return occorrenza;
}


int corrisponde(char *src, char *regexp, int *j) {
    int valido = 0;
    if (!isalpha(regexp[*j])) {
        switch (regexp[*j]) {
            case 46: //punto .
                *j = *j + 1;
                return 1;

            case 91: //parentesi[
                *j = *j + 1;
                if (regexp[*j] == '^') {
                    *j = *j + 1;
                    valido = 1;
                    while (regexp[*j] != ']') {
                        if (*src == regexp[*j]) {
                            valido = 0;
                        }
                        //Scorro fino ad arrivare alla partentesi chiusa
                        *j = *j + 1;
                    }
                }
                while (regexp[*j] != ']') {
                    if (*src == regexp[*j]) {
                        valido = 1;
                    }
                    //Scorro fino ad arrivare alla partentesi chiusa
                    *j = *j + 1;
                }
                //Supero la parentesi chiusa e restituisco il valore di valido
                *j = *j + 1;
                return valido;

            case 92: //escape\
                valido = 0;
                *j = *j + 1;
                /*Controllo se la lettera dopo escape \a è dello stesso tipo (maiuscolo\minuscolo) della
                 *rispettiva nella stringa "src". Se lo è ritorno 1 altrimenti 0
                 */
                if (isupper(regexp[*j]) == isupper(*src)) {
                    valido = 1;
                }
                *j = *j + 1;
                return valido;

        }
    } else {
        if (*src == regexp[*j]) {
            *j = *j + 1;
            return 1;
        } else {
            return 0;
        }

    }
}