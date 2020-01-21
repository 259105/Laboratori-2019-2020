//
// Created by s259105 on 21/12/2019.
//
#include <stdlib.h>

#include "pietre.h"

struct pietre{
    int pietre[NP];
};

P Pinit_insert(int zaf,int sme,int rub, int top){
    P p=malloc(sizeof(*p));
    p->pietre[z]=zaf;
    p->pietre[s]=sme;
    p->pietre[r]=rub;
    p->pietre[t]=top;
    return p;
}
void Pfree(P p){
    free(p);
}
P Pdup_insert_remove(P p,Nome nome_p,int x1){
    P t=p;// creo una copia e la restituisco
    t->pietre[nome_p]+=x1;
    return t;
}

int Ptot(P p){
    return p->pietre[z]+p->pietre[s]+p->pietre[r]+p->pietre[t];
}

int Pz(P p){
    return p->pietre[z];
}
int Ps(P p){
    return p->pietre[s];
}
int Pr(P p){
    return p->pietre[r];
}
int Pt(P p){
    return p->pietre[t];
}
