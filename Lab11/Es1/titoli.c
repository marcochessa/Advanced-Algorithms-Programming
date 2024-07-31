//
// Created by marco on 09/01/2019.
//

#include <mem.h>
#include <malloc.h>
#include "titoli.h"

typedef struct title_t {
    char *nome;
    quotBST quotazioni;
} title_t;

typedef struct node *link;

typedef struct titleList_t {
    link head;
    int nTitle;
} titleList_t;

struct node {
    title title;
    link next;
};


static link newNode(title val, link next);

static link SortListIns(link h, title val);

static link newNode(title val, link next) {
    link x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;
    else {
        x->title = val;
        x->next = next;
    }
    return x;
}

KeyTitle titleGetKey(title t) {
    return t->nome;
}

static int KEYtitleCmp(KeyTitle kt1, KeyTitle kt2) {
    return strcmp(kt1, kt2);
}

void loadTitle(FILE *in, titList tList) {
    char nome[20];
    int N, i;
    quota q;
    title t;
    date_t d;
    quotBST BST;

    while (!feof(in)) {
        fscanf(in, "%s", nome);
        t = malloc(sizeof(*t));
        t->nome = strdup(nome);
        BST = BSTinit();
        fscanf(in, "%d", &N);
        for (i = 0; i < N; i++) {
            q = malloc(sizeof(*q));
            fscanf(in, "%d/%d/%d %*d:%*d %f %d", &q->data.anno, &q->data.mese, &q->data.giorno,
                   &q->vTrans, &q->nTrans);
            q->vTrans = q->vTrans * q->nTrans;
            BSTinsert_leafR(BST, q);
        }
        t->quotazioni = BST;
        insertTitle(tList, t);
    }
}

static title titleSetVoid() {
    title tVoid = malloc(sizeof(*tVoid));
    tVoid->nome = NULL;
    tVoid->quotazioni = NULL;
    return tVoid;
}

titList listInit() {
    titList l = malloc(sizeof(*l));
    if (l == NULL)
        return NULL;
    l->head = NULL;
    return l;
}

void insertTitle(titList tL, title t) {
    /*Si assume che i titoli del file non siano ripetuti, altrimenti andrebbe fatta una
     *verifica sulla presenza del titolo dato per evitare duplicati*/
    tL->head = SortListIns(tL->head, t);
    tL->nTitle++;
}

static link SortListIns(link h, title val) {
    link x, p;
    KeyTitle k = titleGetKey(val);

    if (h == NULL || (KEYtitleCmp(titleGetKey(h->title), k) > 0)) {
        return newNode(val, h);
    }

    for (x = h->next, p = h; x != NULL && (KEYtitleCmp(k, titleGetKey(x->title)) > 0);
         p = x, x = x->next); //attraversamento per ricerca posizione
    p->next = newNode(val, x);

    return h;
}

title searchTitle(titList tL, KeyTitle k) {
    link x;
    for (x = tL->head; x != NULL && (KEYtitleCmp(k, titleGetKey(x->title)) >= 0); x = x->next)
        if (KEYtitleCmp(titleGetKey(x->title), k) == 0)
            return x->title;
    return titleSetVoid();
}

quota getDateQuotation(title t, char *date) {
    quota q;
    date_t d = dateCreate(date);
    q = BSTsearch(t->quotazioni, &d);
    return q;
}

void getBetweenDateQuotation(title t, char *date1, char *date2) {
    date_t d1 = dateCreate(date1);
    date_t d2 = dateCreate(date2);
    if (dateCompare(d1, d2) < 0) {
        BSTmaxminDate(t->quotazioni, &d1, &d2);
    } else {
        BSTmaxminDate(t->quotazioni, &d2, &d1);
    }
}

void getMaxMinQuotation(title t) {
    BSTmaxminAbs(t->quotazioni);

}

void quotBalance(title t, int soglia) {
    if (BSTdist(t->quotazioni) > soglia) {
        BSTbalance(t->quotazioni);
        printf("Albero bilanciato\n");
    } else {
        printf("Albero gia' bilanciato\n");
    }
}

static void titleFree(title t) {
    BSTfree(t->quotazioni);
    free(t);
}

void tFree(titList tL) {
    link x, head;
    head = tL->head;
    for (x = head; x != NULL; x = x->next) {
        titleFree(x->title);
    }
    free(tL);
}
