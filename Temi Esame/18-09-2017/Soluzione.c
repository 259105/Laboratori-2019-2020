//
// Created by s259105 on 15/02/2020.
//
#include <stdlib.h>
#include "Soluzione.h"

Sol* SOLvettload(FILE *fin,int N){
    Sol *sol;
    sol=malloc(sizeof(Sol)*N);
    for(int i=0;i<N;i++)
        fscanf(fin,"K%d %d",&sol[i].k,&sol[i].t);
    return sol;
}
void SOLvettfree(Sol *sol){
    free(sol);
}
Sol SOLcreate(int k,int t){
    Sol s;
    s.k=k;
    s.t=t;
    return s;
}
void SOLvettstorage(FILE *fo,Sol *sol,int N){
    for(int i=0;i<N;i++)
        fprintf(fo,"K%d %d\n",sol[i].k,sol[i].t);
}
