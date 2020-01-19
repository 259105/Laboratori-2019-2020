//
// Created by s259105 on 19/01/2020.
//

#ifndef QUOTAZIONI_H
#define QUOTAZIONI_H
#include "data.h"
#include <stdio.h>

typedef struct{
    int valtot,n;
    data d;
}quotazione;

typedef struct _quotazioni *quotazioni;
float QUOTAZIONE(quotazione q);
quotazione quotazioneSetNULL();
quotazioni QUOTAZIONIinit();
quotazione QUOTAZIONEinit(int val,int n,data d);
void QUOTAZIONIfree(quotazioni q);
void QUOTAZIONIinsert(quotazioni Q,quotazione q);
quotazione QUOTAZIONIsearch(quotazioni Q,data d);
//void QUOTAZIONIprint(quotazioni bst, FILE *fp);
void QUOTAZIONEprint(FILE *fp,quotazione q);
void QUOTAZIONIsearchIntervalPrintMaxMin(quotazioni Q,data d1,data d2,FILE *fp);
data QUOTAZIONImaxdataW(quotazioni Q);
int BilanciamentoSoglia(quotazioni bst,int soglia);

#endif //QUOTAZIONI_H
