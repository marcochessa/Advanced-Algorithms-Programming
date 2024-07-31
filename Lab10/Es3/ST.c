//
// Created by marco on 11/01/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ST.h"


struct symboltable {
    elab_t *vElab;
    int maxN;
    int size;
};

static int searchR(ST st, int l, int r, char *k);

ST STinit(int maxN) {
    ST st;
    int i;
    st = malloc(sizeof(*st));
    if (st == NULL) {
        printf("Memory allocation error\n");
        return NULL;
    }
    st->vElab = malloc(maxN * sizeof(elab_t));
    if (st->vElab == NULL) {
        printf("Memory allocation error\n");
        free(st);
        return NULL;
    }
    for (i = 0; i < maxN; i++){
        st->vElab[i].name=NULL;
        st->vElab[i].subnet=NULL;
    }
    st->maxN = maxN;
    st->size = 0;
    return st;
}

int STcount(ST st) {
    return st->size;
}

void STfree(ST st) {
    int i;
    for (i = 0; i < st->maxN; i++)
        if (st->vElab[i].name != NULL) {
            free(st->vElab[i].name);
            free(st->vElab[i].name);
        }
    free(st->vElab);
    free(st);
}

int STinsert(ST st, elab_t elab) {
    int i = st->size++;
    if (st->size > st->maxN) {
        //Nel caso in cui viene superato il valore previsto viene raddoppiato lo spazio allocato
        st->vElab = realloc(st->vElab, (2 * st->maxN) * sizeof(elab_t));
        st->maxN = 2 * st->maxN;
    }
    if(st->vElab==NULL)
        return -1;
    while ((i > 0) && strcmp(elab.name, st->vElab[i - 1].name) < 0) {
        st->vElab[i] = st->vElab[i - 1];
        i--;
    }
    st->vElab[i] = elab;
    return i;
}

/*
int STsearch(ST st, char *s) {
    int i;
    for (i = 0; i < st->maxN; i++)
        if (st->a[i] != NULL && strcmp(s, st->a[i]) == 0)
            return i;
    return -1;
}
*/

//Viene utilizzata la ricerca dicotomica nel caso di ricarca tramite chiave
int STsearch(ST st, char *k) {
    return searchR(st, 0, st->size - 1, k);
}

static int searchR(ST st, int l, int r, char *k) {
    int m;
    m = (l + r) / 2;
    if (l > r)
        return -1;
    if (strcmp(k, st->vElab[m].name) == 0)
        return m;
    if (l == r)
        return -1;
    if (strcmp(k, st->vElab[m].name) < 0)
        return searchR(st, l, m - 1, k);
    else
        return searchR(st, m + 1, r, k);
}

elab_t STsearchByIndex(ST st, int i) {
    return st->vElab[i];
}
