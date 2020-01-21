//
// Created by s259105 on 21/12/2019.
//

#ifndef MATRICI_H
#define MATRICI_H

//Quasi ADT matrici
typedef struct matrici *M;
struct matrici{
    int ****MZ;
    int ****MS;
    int ****MR;
    int ****MT;
};

M Minit(int z,int s,int r, int t);//inizializzazione
void Mfree(M m,int z,int s,int r);
void Mprint(int ****m,int z,int s,int r, int t);
void Minsert(int ****m,int z,int s,int r, int t,int val);
int Mextract(int ****m,int z,int s,int r, int t);

#endif //MATRICI_H
