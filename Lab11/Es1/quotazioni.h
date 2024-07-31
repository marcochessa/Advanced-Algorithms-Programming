//
// Created by marco on 15/01/2019.
//

#ifndef ESERCIZIO1_QUOTAZIONI_H
#define ESERCIZIO1_QUOTAZIONI_H

#include "data.h"

typedef date_t *Key;

typedef struct quotazione_t {
    int nTrans;
    float vTrans;
    float val;
    date_t data;
} quotazione_t;

typedef struct quotazione_t *quota;

typedef struct binarysearchtree *quotBST;

quotBST BSTinit();

void BSTfree(quotBST bst);

int BSTcount(quotBST bst);

int BSTempty(quotBST bst);

quota BSTsearch(quotBST bst, Key k);

void BSTinsert_leafR(quotBST bst, quota x);

void BSTmaxminDate(quotBST bst, Key kMin, Key kMax);

void BSTmaxminAbs(quotBST bst);

void BSTbalance(quotBST bst);

Key KEYget(quota);

void printInfoQuot(quota q);

int BSTdist(quotBST bst);

#endif //ESERCIZIO1_QUOTAZIONI_H
