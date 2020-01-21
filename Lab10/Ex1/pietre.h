//
// Created by s259105 on 21/12/2019.
//

#ifndef PIETRE_H
#define PIETRE_H

#define NP 4
typedef enum{
    z=0,s,r,t
}Nome;
typedef struct pietre *P; // ADT di 1a classe

P Pinit_insert(int z,int s,int r, int t);
void Pfree(P p);
P Pdup_insert_remove(P p,Nome nome_p,int x1);
int Ptot(P p);
int Pz(P p);
int Ps(P p);
int Pr(P p);
int Pt(P p);

#endif //PIETRE_H
