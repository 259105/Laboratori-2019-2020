//
// Created by s259105 on 21/12/2019.
//
#include <stdlib.h>
#include <stdio.h>

#include "matrici.h"

M Minit(int z,int s,int r, int t){
    M matrici;
    int i,j,k;
    matrici=malloc(sizeof(*matrici));//se da problemi è sicuro lui
    matrici->MZ=(int****)calloc(z,sizeof(int***));
    matrici->MS=(int****)calloc(z,sizeof(int***));
    matrici->MR=(int****)calloc(z,sizeof(int***));
    matrici->MT=(int****)calloc(z,sizeof(int***));
    for(i=0;i<z;i++){
        matrici->MZ[i]=(int***)calloc(s,sizeof(int**));
        matrici->MS[i]=(int***)calloc(s,sizeof(int**));
        matrici->MR[i]=(int***)calloc(s,sizeof(int**));
        matrici->MT[i]=(int***)calloc(s,sizeof(int**));
        for(j=0;j<s;j++){
            matrici->MZ[i][j]=(int**)calloc(r,sizeof(int*));
            matrici->MS[i][j]=(int**)calloc(r,sizeof(int*));
            matrici->MR[i][j]=(int**)calloc(r,sizeof(int*));
            matrici->MT[i][j]=(int**)calloc(r,sizeof(int*));
            for(k=0;k<r;k++){
                matrici->MZ[i][j][k]=(int*)calloc(t,sizeof(int));
                matrici->MS[i][j][k]=(int*)calloc(t,sizeof(int));
                matrici->MR[i][j][k]=(int*)calloc(t,sizeof(int));
                matrici->MT[i][j][k]=(int*)calloc(t,sizeof(int));
            }
        }
    }
    return matrici;
}

void Mfree(M m,int z,int s,int r){
    int i,j,k;
    for(i=0;i<z;i++){
        for(j=0;j<s;j++){
            for (k=0;k<r;k++) {
                free(m->MZ[i][j][k]);free(m->MS[i][j][k]);free(m->MR[i][j][k]);free(m->MT[i][j][k]);
            }
            free(m->MZ[i][j]);free(m->MS[i][j]);free(m->MR[i][j]);free(m->MT[i][j]);
        }
        free(m->MZ[i]);free(m->MS[i]);free(m->MR[i]);free(m->MT[i]);
    }
    free(m->MZ);free(m->MS);free(m->MR);free(m->MT);
    free(m);
}

void Mprint(int ****m,int z,int s,int r, int t){
    int i,j,k,y;
    for(i=0;i<z;i++)
        for(j=0;j<s;j++)
            for(k=0;k<r;k++)
                for(y=0;y<t;y++)
                    printf("%d",m[i][j][k][y]);
}

void Minsert(int ****m,int z,int s,int r, int t,int val){
    m[z][s][r][t]=val;
}
int Mextract(int ****m,int z,int s,int r, int t){
    return m[z][s][r][t];
}
