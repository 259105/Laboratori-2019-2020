//
// Created by s259105 on 23/12/2019.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "elemento.h"

elemento ELEMENTOinit(char *nome,int tipo,int ingr,int usct,int prec,int finl,float val,int diff){
    elemento t=malloc(sizeof(*t));
    strcpy(t->nome,nome);
    t->tipo=tipo;
    t->ingr=ingr;
    t->usct=usct;
    t->prec=prec;
    t->finl=finl;
    t->val=val;
    t->diff=diff;
    return t;
}

void ELEMENTOfree(elemento t){
    free(t);
}
void ELEMENTOarrayfree(elemento *t,int n){
    for(int i=0;i<n;i++){
        free(t[i]);
    }
    free(t);
}

int ELEMENTOsequenza(elemento el1,elemento el2){
    return el1->usct==el2->ingr;
}

elemento* inputelementi(FILE *fp,elemento *elementi,int *n){
    char nome[MAXCHAR];
    int tipo,ingr,usct,prec,finl,diff;
    float val;
    fscanf(fp,"%d",n);
    elementi=malloc(*n * sizeof(elemento));
    for(int i=0;i<*n;i++){
        fscanf(fp,"%s%d%d%d%d%d%f%d",nome,&tipo,&ingr,&usct,&prec,&finl,&val,&diff);
        elementi[i]=ELEMENTOinit(nome,tipo,ingr,usct,prec,finl,val,diff);
    }
    return elementi;
}

void ELEMENTIprint(elemento *t,int n){
    for(int i=0;i<n;i++){
        printf("Nome: %s\n\tTipo: %d \n\tIngresso: %d \n\tUscita: %d \n\tPrecendeza: %d \n\tFinale: %d \n\tValore: %.2f \n\tDifficolta': %d\n\n",t[i]->nome,t[i]->tipo,t[i]->ingr,t[i]->usct,t[i]->prec,t[i]->finl,t[i]->val,t[i]->diff);
    }
}
