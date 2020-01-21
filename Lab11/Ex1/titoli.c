//
// Created by s259105 on 19/01/2020.
//
#include <stdlib.h>
#include <string.h>
#include "titoli.h"


typedef struct node *link;
struct node{
    titolo t;
    link next;
};
struct _titoli{
    link h;
    link z;
    int n;
};


static titolo titoloSetNULL(){
    return NULL;
}
static link NEWnode(titolo val,link next){
    link t=malloc(sizeof *t);
    t->t=val;
    t->next=next;
    return t;
}

titoli TITOLIinit(){
    titoli t=malloc(sizeof *t);
    t->n=0;
    t->h=(t->z=NEWnode(titoloSetNULL(),NULL));
    return t;
}
static void listafree(link h,link z){
    if(h==z) return;
    listafree(h->next,z);
    TITOLOfree(h->t);
    free(h);
}
void TITOLIfree(titoli t){
    if(t==NULL) return;
    listafree(t->h,t->z);
    TITOLOfree(t->z->t);
    free(t->z);
    free(t);
}
static void TITOLIinsert(titoli T,titolo t){
    link x,p;
    if(T->h==T->z || strcmp(CodbyT(T->h->t),CodbyT(t))>0){
        T->h=NEWnode(t,T->h);
        return;
    }
    for(x=T->h->next,p=T->h;x!=T->z && strcmp(CodbyT(t),CodbyT(x->t))>0;p=x,x=x->next);
    p->next=NEWnode(t,x);
    return;
}
static titolo searchlist(link h,char *cod,link z){
    if(h==z) return titoloSetNULL();
    if(strcmp(CodbyT(h->t),cod)==0)
        return h->t;
    return searchlist(h->next,cod,z);
}
titolo TITOLIsearch(titoli T,char *cod){
    return searchlist(T->h,cod,T->z);
}

titolo TITOLIinsertW(titoli T,char *cod){
    titolo t;
    if((t=TITOLIsearch(T,cod))!=NULL)
        return t;
    t=TITOLOinit(cod);
    TITOLIinsert(T,t);
    return t;
}
