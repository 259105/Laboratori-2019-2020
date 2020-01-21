//
// Created by s259105 on 23/12/2019.
//
#include <stdlib.h>

#include "diagonale.h"

diagonale DIAGONALEinit(void){
    diagonale t=malloc(sizeof(*t));
    return t;
}

diagonale* DIAGONALEarrayinit(int n){
    diagonale *t;
    t=malloc(n* sizeof(*t));
    return t;
}

void DIAGONALEfree(diagonale t){
    free(t);
}

void DIAGONALEinsert(diagonale t,elemento elem){
    t->e[t->n_elem]=elem;
    t->pnt+=elem->val;
    t->diff+=elem->diff;
    t->n_elem++;
}
void DIAGONALEremove(diagonale t){
    t->n_elem--;
    t->pnt-=t->e[t->n_elem]->val;
    t->diff-=t->e[t->n_elem]->diff;
    t->e[t->n_elem]=NULL;
}
void DIAGONALEcopy(diagonale t1,diagonale t2){
    t1->diff=t2->diff;
    t1->pnt=t2->pnt;
    t1->n_elem=t2->n_elem;
    for(int i=0;i<MAXELEM;i++){
        t1->e[i]=t2->e[i];
    }
}
