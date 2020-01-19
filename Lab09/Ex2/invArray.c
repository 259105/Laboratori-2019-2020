//
// Created by s259105 on 11/12/2019.
//
#include <stdio.h>
#include <stdlib.h>

#include "invArray.h"
#include "mylib.h"

struct invArray_s{
    inv_t *vettInv;
    int nInv;
    int maxInv;
};

invArray_t invArray_init(){
    invArray_t t;
    t=malloc(sizeof(*t));
    if(t==NULL) {
        fprintf(stderr, "Errore di allocazione");
        exit(1);
    }
    t->vettInv=NULL;
    t->nInv=0;
    t->maxInv=0;
    return t;
}
void invArray_free(invArray_t invArray){
    free(invArray->vettInv);
    free(invArray);
}

void invArray_read(FILE *fp, invArray_t invArray){
    fscanf(fp,"%d",&invArray->maxInv);
    invArray->vettInv=malloc(invArray->maxInv*sizeof(inv_t));
    if(invArray->vettInv==NULL) {
        fprintf(stderr, "Errore di allocazione");
        exit(1);
    }
    for(int i=0;i<invArray->maxInv;i++){
        inv_read(fp,&invArray->vettInv[i]);
        invArray->nInv++;
    }
}
void invArray_print(FILE *fp, invArray_t invArray){
    stat_t t;
    for(int i=0;i<invArray->nInv;i++){
        inv_print(fp,&invArray->vettInv[i]);
        t=inv_getStat(&invArray->vettInv[i]);
        stat_print(fp,&t,-1);
    }
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    if(index>=0 && index<invArray->nInv){
        stat_t t;
        inv_print(fp,&invArray->vettInv[index]);
        t=inv_getStat(&invArray->vettInv[index]);
        stat_print(fp,&t,-1);
    }else{
        fprintf(stderr,"Oggetto non presente");
    }
}

inv_t *invArray_getByIndex(invArray_t invArray, int index){
    if(index>=0 && index<invArray->nInv)
        return &(invArray->vettInv[index]);
    return NULL; //non ho trovato nulla
}

int invArray_searchByName(invArray_t invArray, char *name){
    int i;
    for(i=0;i<invArray->nInv && confronta_stringhe(inv_getName(&invArray->vettInv[i]),name)!=0;i++);
    if(i==invArray->nInv) return -1; //non ho trovato niente
    return i;
}

int invArray_getNinv(invArray_t invArray){
    return (invArray->nInv);
}

