//
// Created by s259105 on 15/02/2020.
//
#include "List.h"
#include "Graph.h"

static link NEW(int v,link next){
    link t=malloc(sizeof(*t));
    t->v=v;
    t->next=next;
    return t;
}

Lista LISTAinit(void){
    Lista l;
    l.n=0;
    l.h=(l.z=NEW(-1,NULL));
    return l;
}

void NODEfree(link h,link z){
    if(h==z) return;
    NODEfree(h->next,z);
    free(h);
}
void LISTAfree(Lista l){
    NODEfree(l.h,l.z);
    free(l.z);
}

Lista LISTAinsert(Lista l,int v){
    l.h=NEW(v,l.h);
    l.n++;
    return l;
}

Lista LISTAremove(Lista l){
    if(l.h==l.z) return l;
    link t=l.h;
    l.h=l.h->next;
    free(t);
    l.n--;
    return l;
}

link NODEdup(link h1,link h2,link z){
    if(h2->next==NULL) return z;
    h1=NODEdup(h1,h2->next,z);
    h1=NEW(h2->v,h1);
    return h1;
}
Lista LISTAdup(Lista l1,Lista l2){
    l1=LISTAinit();
    l1.n=l2.n;
    l1.h=NODEdup(l1.h,l2.h,l1.z);
    return l1;
}
static int NODEcmp(link h1,link h2,link z){
    //aver scelto come calcolo le combinazioni semplici, mi garantisce che le soluzioni trovare abbiano
    //sempre la stessa combinazione di numeri(senza variazione delle posizioni).
    if(h1->next==NULL && h2->next==NULL) return 0;
    if(h1->next==NULL || h2->next==NULL) return 1;
    if(h1->v==h2->v)
        return NODEcmp(h1->next,h2->next,z);
    return 1;
}
int LISTAcmp(Lista l1,Lista l2){
    if(l1.n!=l2.n) return 1;
    if(NODEcmp(l1.h,l2.h,l1.z)==0) return 0;
    return 1;
}

void LISTAstorage(FILE *fo,Lista l){
    link t;
    for(t=l.h;t!=l.z;t=t->next)
        fprintf(fo,"%d ",t->v);
    fprintf(fo,"\n");
}
