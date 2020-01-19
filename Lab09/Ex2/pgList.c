//
// Created by s259105 on 12/12/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgList.h"

struct pgList_s{
    link headPg;
    link tailPg;
    int nPg;
};

pgList_t pgList_init(){
    pgList_t t;
    t=malloc(sizeof(*t));
    if(t==NULL) {
        fprintf(stderr, "Errore di allocazione");
        exit(1);
    }
    t->headPg=NULL;
    t->tailPg=NULL;
    t->nPg=0;
    return t;
}
void pgList_free(pgList_t pgList){
    pgList_freeR(pgList->headPg);
    free(pgList);
}
void pgList_freeR(link n){
    if(n==NULL) return;
    pgList_freeR(n->next);//ricorro in salita per non perdere i link
    pg_clean(&n->pg);
    free(n);
}

void pgList_read(FILE *fp, pgList_t pgList){
    pg_t pg;
    while (pg_read(fp,&pg))
        pgList_insert(pgList,pg);
}
void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    pgList_printR(fp,pgList->headPg,invArray);
}
void pgList_printR(FILE *fp,link node, invArray_t invArray){
    if(node==NULL) return;
    pg_print(fp,&node->pg,invArray);
    pgList_printR(fp,node->next,invArray);
}

void pgList_insert(pgList_t pgList, pg_t pg){
    //inserimento in coda
    link n;
    if(pgList_searchByCode(pgList,pg.cod)!=NULL){//controllo se quel cod è gia nella lista
        fprintf(stderr,"Errore cod PG gia' in uso.\n");
        return;
    }
    n=newNode(pg,NULL);
    if(pgList->tailPg==NULL && pgList->headPg==NULL) {// caso iniziale tutti e 2 puntano a null
        pgList->headPg=pgList->tailPg=n;
        return;
    }
    pgList->tailPg->next=n;// imposto che il successico della coda deve essere il nuovo nodo
    pgList->tailPg=pgList->tailPg->next; //aggiorno coda
    pgList->nPg++;
}
void pgList_remove(pgList_t pgList, char* cod){
    link n,p;
    for(p=NULL,n=pgList->headPg;n!=NULL && confronta_stringhe(cod,n->pg.cod)!=0;p=n,n=n->next);
    if(n==NULL){
        fprintf(stderr,"Errore cod PG non trovato.\n");
        return;
    }
    if (p==NULL){
        if(pgList->headPg==pgList->tailPg) pgList->headPg=pgList->tailPg=NULL; //nel caso ci fosse un solo elemento e lo si vuole eliminare
        pgList->headPg=n->next;//nel caso fosse il primo elemento allora cambio l'head
    }
    else{
        if(n==pgList->tailPg){
            pgList->tailPg=p; //nel caso che vuoi eliminare l'ultimo elemento aggirono la tail
            pgList->tailPg->next=NULL;
            pgList->nPg--;
        }
        p->next=n->next;//by-pass collego il precendete a n con il successivo
    }
    pg_clean(&n->pg);
    free(n);
}

link newNode(pg_t pg,link next){
    link n;
    n=malloc(sizeof(*n));
    if(n==NULL) {
        fprintf(stderr, "Errore di allocazione");
        exit(1);
    }
    n->pg=pg;
    n->next=next;
    return n;
}

pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    return (pgList_searchByCodeR(pgList->headPg,cod));
}
pg_t *pgList_searchByCodeR(link node,char* cod){
    if(node==NULL)
        return NULL;
    if(confronta_stringhe(node->pg.cod,cod)==0)
        return &node->pg;
    return pgList_searchByCodeR(node->next,cod);
}
