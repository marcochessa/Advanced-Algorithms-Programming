//
// Created by marco on 09/01/2019.
//

#include <stdio.h>
#include "data.h"

date_t dateCreate(char *date){
    date_t d;
    sscanf(date,"%d/%d/%d",&d.anno,&d.mese,&d.giorno);
    return d;
}

date_t dataSetVoid(){
    date_t t;
    t.giorno=-1;
    t.mese=-1;
    t.anno=-1;
    return t;
}

int dateCompare(date_t d1, date_t d2){
    if(d1.anno>d2.anno)
        return 1;
    if(d1.anno<d2.anno)
        return -1;
    if(d1.mese>d2.mese)
        return 1;
    if(d1.mese<d2.mese)
        return -1;
    if(d1.giorno>d2.giorno)
        return 1;
    if(d1.giorno<d2.giorno)
        return -1;
    return 0;
}