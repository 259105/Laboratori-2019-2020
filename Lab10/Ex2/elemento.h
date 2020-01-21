//
// Created by s259105 on 23/12/2019.
//

#ifndef ELEMENTO_H
#define ELEMENTO_H

#define MAXCHAR 100
#include <stdio.h>

typedef struct elemento_* elemento;
struct elemento_{// quasi ADT elemento
    char nome[MAXCHAR];
    int tipo,ingr,usct,prec,finl,diff;
    float val;
};

elemento ELEMENTOinit(char *nome,int tipo,int ingr,int usct, int prec, int finl,float val,int diff);
void ELEMENTOfree(elemento t);
void ELEMENTOarrayfree(elemento *t,int n);
int ELEMENTOsequenza(elemento el1,elemento el2);
elemento* inputelementi(FILE *fp,elemento *elementi,int *n);
void ELEMENTIprint(elemento *t,int n);


#endif //ELEMENTO_H
