//
// Created by marco on 15/01/2019.
//

#include "quotazioni.h"
#include <stdlib.h>
#include <stdio.h>

#define MAXINT 9999

typedef struct BSTnode *link;
struct BSTnode {
    quota quot;
    link l;
    link r;
    int N;
};
struct binarysearchtree {
    link root;
    link z;
};

static int KEYcmp(Key k1, Key k2);

static void treeFree(link h, link z);

static void treePrintR(link h, link z);

static link partR(link h, link z, int r);

static void calcQuotVal(quota q);

static void countDist(link h, link z, int *min, int *max, int *count);

static void refreshQuot(quota q, quota agg);

static link NEW(quota item, link l, link r, int N);

static quota searchR(link h, Key k, link z);

static quota quotaSetVoid();

static quota minR(link h, link z);

static quota maxR(link h, link z);

static void maxminRDate(link h, link z, quota *max, quota *min, Key kMin, Key kMax);


static link NEW(quota item, link l, link r, int N) {
    link x = malloc(sizeof *x);
    x->quot = item;
    calcQuotVal(x->quot);
    x->l = l;
    x->r = r;
    x->N = N;
    return x;
}

quotBST BSTinit() {
    quotBST bst = malloc(sizeof *bst);
    bst->root = (bst->z = NEW(quotaSetVoid(), NULL, NULL, 0));
    return bst;
}

Key KEYget(quota q) {
    Key k = &q->data;
    return k;
}

void BSTfree(quotBST bst) {
    if (bst == NULL)
        return;
    treeFree(bst->root, bst->z);
    free(bst->z);
    free(bst);
}


static int KEYcmp(Key k1, Key k2) {
    return dateCompare(*k1, *k2);
};

static void treeFree(link h, link z) {
    if (h == z)
        return;
    //Funzione ricorsiva di liberazione, libero il sottoalbero sinistro poi destro
    treeFree(h->l, z);
    treeFree(h->r, z);
    free(h);
}

static int countR(link h, link z) {
    if (h == NULL || h == z)
        return 0;
    return countR(h->l, z) + countR(h->r, z) + 1;
}

int BSTcount(quotBST bst) {
    return countR(bst->root, bst->z);
}

static void countDist(link h, link z, int *min, int *max, int *count) {
    if (h == z) {
        if (*count > *max)
            *max = *count;
        if (*count < *min)
            *min = *count;
        *count = 0;
        return;
    }

    *count = *count + 1;

    countDist(h->l, z, min, max, count);
    countDist(h->r, z, min, max, count);


}

int BSTdist(quotBST bst) {
    int min = MAXINT;
    int max = -1;

    int count = 0;
    countDist(bst->root, bst->z, &min, &max, &count);
    if (max == -1) {
        printf("Nessun cammino trovato\n");
        return -1;
    }
    return max - min;
}

static int minQuotR(link h, link z, quota minQuot) {
    if (h == z)
        return 0;
    return countR(h->l, z) + countR(h->r, z) + 1;
}

int BSTMinQuot(quotBST bst, quota minQuot) {
    return minQuotR(bst->root, bst->z, minQuot);
}

static link insertR(link h, quota x, link z) {
    if (h == z)
        return NEW(x, z, z, 0);
    if (KEYcmp(KEYget(x), KEYget(h->quot)) == -1)
        h->l = insertR(h->l, x, z);
    else
        h->r = insertR(h->r, x, z);
    return h;
}

void BSTinsert_leafR(quotBST bst, quota x) {
    quota tmp = searchR(bst->root, KEYget(x), bst->z);
    if (tmp->val != -1) {
        refreshQuot(tmp, x);
        return;
    }
    bst->root = insertR(bst->root, x, bst->z);
}

static void refreshQuot(quota q, quota agg) {
    q->nTrans = q->nTrans + agg->nTrans;
    q->vTrans = q->vTrans + agg->vTrans;
    calcQuotVal(q);
}

static void calcQuotVal(quota q) {
    q->val = (q->vTrans) / q->nTrans;
}

static quota searchR(link h, Key k, link z) {
    if (h == z)
        return quotaSetVoid();
    if (KEYcmp(k, KEYget(h->quot)) == 0)
        return h->quot;
    if (KEYcmp(k, KEYget(h->quot)) == -1)
        return searchR(h->l, k, z);
    else
        return searchR(h->r, k, z);
}

quota BSTsearch(quotBST bst, Key k) {
    return searchR(bst->root, k, bst->z);
}

static quota minR(link h, link z) {
    if (h == z)
        return quotaSetVoid();
    if (h->l == z)
        return (h->quot);
    return minR(h->l, z);
}

static quota maxR(link h, link z) {
    if (h == z)
        return quotaSetVoid();
    if (h->r == z)
        return (h->quot);
    return maxR(h->r, z);
}

static void maxminRAbs(link h, link z, quota *min, quota *max) {
    if (h == z)
        return;

    if ((h->quot->val) < ((*min)->val))
        *min = h->quot;
    if ((h->quot->val) > ((*max)->val))
        *max = h->quot;

    maxminRAbs(h->l, z, min, max);

    maxminRAbs(h->r, z, min, max);
}

void BSTmaxminAbs(quotBST bst) {
    quota min = quotaSetVoid();
    quota max = quotaSetVoid();
    min->val = MAXINT;
    maxminRAbs(bst->root, bst->z, &min, &max);

    if (min->val == -1 || max->val == -1) {
        printf("Nessuna quotazione trovata nell'intervallo\n");
        return;
    }
    printf("MIN %f %d/%d/%d, MAX %f %d/%d/%d,\n", min->val, min->data.anno, min->data.mese,
           min->data.giorno,
           max->val, max->data.anno, max->data.mese, max->data.giorno);
}

static void maxminRDate(link h, link z, quota *min, quota *max, Key kMin, Key kMax) {
    if (h == z)
        return;

    if (KEYcmp(KEYget(h->quot), kMin) >= 0 && KEYcmp(KEYget(h->quot), kMax) <= 0) {
        if ((h->quot->val) < ((*min)->val))
            *min = h->quot;
        if ((h->quot->val) > ((*max)->val))
            *max = h->quot;
    }

    if (KEYcmp(KEYget(h->l->quot), kMin) >= 0)
        maxminRDate(h->l, z, min, max, kMin, kMax);

    if (KEYcmp(KEYget(h->r->quot), kMax) <= 0)
        maxminRDate(h->r, z, min, max, kMin, kMax);
}

void BSTmaxminDate(quotBST bst, Key kMin, Key kMax) {
    quota min = quotaSetVoid();
    quota max = quotaSetVoid();
    min->val = 9999;
    maxminRDate(bst->root, bst->z, &min, &max, kMin, kMax);
    if (min->val == -1 || max->val == -1) {
        printf("Nessuna quotazione trovata nell'intervallo\n");
        return;
    }
    printf("MIN %f %d/%d/%d, MAX %f %d/%d/%d,\n", min->val, min->data.anno, min->data.mese, min->data.giorno,
           max->val, max->data.anno, max->data.mese, max->data.giorno);
}

static quota quotaSetVoid() {
    quota q = malloc(sizeof(*q));
    q->data = dataSetVoid();
    q->val = -1;
    q->nTrans = -1;
    q->vTrans = -1;
    return q;
}

int BSTempty(quotBST bst) {
    if (BSTcount(bst) == 0)
        return 1;
    return 0;
}

static void BSTbalanceR(link h, link z) {
    if (h == z)
        return;
    int N = countR(h, z);
    if (N == 1) {
        return;
    }

    int med = (N + 1) / 2;
    h = partR(h, z, med);

    BSTbalanceR(h->l, z);
    BSTbalanceR(h->r, z);
}

void BSTbalance(quotBST bst) {
    if (BSTempty(bst))
        return;
    BSTbalanceR(bst->root, bst->z);
}

link rotR(link h) {
    link x = h->l;
    h->l = x->r;
    x->r = h;
    return x;
}

link rotL(link h) {
    link x = h->r;
    h->r = x->l;
    x->l = h;
    return x;
}

static link partR(link h, link z, int r) {
    int t = countR(h->l, z);
    if (t > r) {
        h->l = partR(h->l, z, r);
        h = rotR(h);
    }
    if (t < r) {
        h->r = partR(h->r, z, r - t - 1);
        h = rotL(h);
    }

    return h;
}


void printInfoQuot(quota q) {
    printf("%d/%d/%d %f\n", q->data.anno, q->data.mese, q->data.giorno, q->val);
}