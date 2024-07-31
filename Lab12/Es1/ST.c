//
// Created by marco on 16/01/2019.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ST.h"

struct symbtab {
    char **a;
    int size;
    int N;
};

ST STinit(int N) {
    ST st;
    int i;
    st = malloc(sizeof(*st));
    st->a = malloc(N * sizeof(char *));
    for (i = 0; i < N; i++)
        st->a[i] = NULL;
    st->N = N;
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


char* STsearchByIndex(ST st, int ind){
    return st->a[ind];
}