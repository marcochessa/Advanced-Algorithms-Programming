//
// Created by marco on 31/01/2019.
//

#ifndef ESAME_ST_H
#define ESAME_ST_H

typedef struct symbtab *ST;

ST STinit(int maxN);

void STfree(ST st);

void STinsert(ST st, char *val);

int STcount(ST st);

int STsearch(ST st, char *k);

char* STsearchByIndex(ST st, int ind);

#endif //ESAME_ST_H
