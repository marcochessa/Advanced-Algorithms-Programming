//
// Created by marco on 09/01/2019.
//

#ifndef ESERCIZIO1_DATA_H
#define ESERCIZIO1_DATA_H
typedef struct date{
    int anno;
    int mese;
    int giorno;
}date_t;

date_t dataSetVoid();

date_t dateCreate(char *date);

int dateCompare(date_t d1, date_t d2);

#endif //ESERCIZIO1_DATA_H
