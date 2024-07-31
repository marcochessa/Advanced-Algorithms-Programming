//
// Created by marco on 11/01/2019.
//

#ifndef ESERCIZIO3_ST_H
#define ESERCIZIO3_ST_H
#define MAXL 31

typedef struct symboltable *ST;

typedef struct{
    char *name;
    char *subnet ;
} elab_t;

ST   STinit(int maxN);
void STfree(ST ht);
int STinsert(ST st, elab_t elab);
int STsearch(ST st, char *k);
elab_t STsearchByIndex(ST st, int i);
int STcount(ST st);

#endif //ESERCIZIO3_ST_H
