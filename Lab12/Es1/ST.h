//
// Created by marco on 16/01/2019.
//

#ifndef ESERCIZIO1_ST_H
#define ESERCIZIO1_ST_H

typedef struct symbtab *ST;

ST STinit(int maxN);

void STfree(ST st);

void STinsert(ST st, char *val);

int STsearch(ST st, char *k);

char* STsearchByIndex(ST st, int ind);

#endif //ESERCIZIO1_ST_H
