//
// Created by marco on 31/01/2019.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ST.h"

struct symbtab {
    char **a;
    int size;
    int maxN;
};

ST STinit(int N) {
    ST st;
    int i;
    st = malloc(sizeof(*st));
    st->a = malloc(N * sizeof(char *));
    for (i = 0; i < N; i++)
        st->a[i] = NULL;
    st->maxN = N;
    st->size = 0;
    return st;
}

void STfree(ST st) {
    int i;
    for (i = 0; i < st->size; i++)
        free(st->a[i]);
    free(st->a);
    free(st);
}

void STinsert(ST st, char *val) {
    int i = st->size;
    if (st->size >= st->maxN) {
        //Ridefinisco la dimensione del vettore
        st->a = realloc(st->a, (2*st->maxN)*sizeof(char *));
        if (st->a == NULL)
            return;
        st->maxN = 2*st->maxN;
    }
    st->a[i] = strdup(val);
    st->size++;
}

int STsearch(ST st, char *k) {
    int i;
    if (st->size == 0)
        return -1;
    for (i = 0; i < st->size; i++)
        if (strcmp(k, st->a[i]) == 0)
            return i;
    return -1;
}

int STcount(ST st) {
    return st->size;
}


char* STsearchByIndex(ST st, int ind){
    return st->a[ind];
}