//
// Created by s259105 on 15/02/2020.
//
#include <stdlib.h>
#include "Foresta.h"
#include "Koala.h"
#include "Soluzione.h"

struct foresta_{
    int N,T,S,m;
    Koala *K;
    int **nemici;
};

Foresta FORESTAinit(char *N,char *T,char *S,char *m){
    Foresta t=malloc(sizeof(*t));
    t->N=atoi(N);
    t->T=atoi(T);
    t->S=atoi(S);
    t->m=atoi(m);
    t->K=malloc(sizeof(Koala)*t->N);
    t->nemici=calloc(t->S,sizeof(int*));
    for(int i=0;i<t->S;i++)
        t->nemici[i]=calloc(t->S,sizeof(int));
    return t;
}
void FORESTAfree(Foresta F){
    for(int i=0;i<F->N;i++)
        free(F->K[i].t);
    free(F->K);
    for(int i=0;i<F->S;i++)
        free(F->nemici[i]);
    free(F->nemici);
    free(F);
}
Foresta FORESTAload(FILE *fk,FILE *ff,FILE *fe,char *N,char *T,char *S,char *m){
    Foresta t;
    t=FORESTAinit(N,T,S,m);
    int id1,id2,n,c=0;
    while (fscanf(fk,"K%d %d",&t->K[c].id,&t->K[c].n_t)==2){
        t->K[c].t=malloc(sizeof(int)*t->K[c].n_t);
        for(int i=0;i<t->K[c].n_t;i++)
            fscanf(fk,"%d",&t->K[c].t[i]);
        c++;
    }
    while(fscanf(ff,"F%d %d",&id1,&n)==2){
        for(int i=0;i<n;i++){
            fscanf(ff,"K%d",&id2);
            for(int j=0;j<t->N;j++)
                if(t->K[j].id==id2){
                    t->K[j].f=id1;
                    break;
                }
        }
    }
    while (fscanf(fe,"F%d F%d",&id1,&id2)==2)
        t->nemici[id1][id2]=t->nemici[id2][id1]=1;
    return t;
}

static int puovivere(Foresta F,int k,int t){
    for(int i=0;i<F->N;i++)
        if(F->K[i].id==k)
            for(int j=0;j<F->K[i].n_t;j++)
                if(F->K[i].t[j]==t)
                    return 1;
    return 0;
}
static int scontro(Foresta F,int k1,int k2){
    int f1,f2;
    for(int i=0;i<F->N;i++){
        if(F->K[i].id==k1) f1=F->K[i].f;
        if(F->K[i].id==k2) f2=F->K[i].f;
    }
    if(F->nemici[f1][f2]==1) return 1;
    return 0;
}
int check(Foresta F,Sol *sol){
    int **M,*vm;
    M=malloc(sizeof(int*)*F->T);
    vm=calloc(F->T,sizeof(int));
    for(int i=0;i<F->T;i++)
        M[i]=malloc(sizeof(int)*F->m);
    for(int i=0;i<F->T;i++)
        for(int j=0;j<F->m;j++)
            M[i][j]=-1;
    for(int i=0;i<F->N;i++){
        if(!puovivere(F,sol[i].k,sol[i].t)) return 0;
        if(vm[sol[i].t]>=F->m) return 0;
        M[sol[i].t][vm[sol[i].t]]=sol[i].k;
        for (int j=0;j<vm[sol[i].t];j++)
            if(scontro(F,M[sol[i].t][j],sol[i].k)) return 0;
    }
    return 1;
}

static int bestallocR(Foresta F,Sol *sol,int *vm,int pos,int k,int start){
    if(pos>=F->N){
        if(check(F,sol))
            return 1;
        return 0;
    }
    for(int i=0;i<k;i++){
        if(vm[i]>=F->m) continue;
        for(int j=start;j<F->N;j++){
            sol[pos]=SOLcreate(j,i);
            vm[i]++;
            if(bestallocR(F,sol,vm,pos+1,k,i+1))
                return 1;
            vm[i]--;//backtrak;
        }
    }
    return 0;
}
void bestalloc(Foresta F){
    int f=0;
    Sol *sol=malloc(sizeof(Sol)*F->N);
    int *vm=calloc(F->T,sizeof(int));
    for(int i=(F->N)/(F->m);i<F->T;i++)
        if(bestallocR(F,sol,vm,0,i,0)){
            f=1;
            SOLvettstorage(stdout,sol,F->N);
        }
    if(!f) printf("Non esiste una soluzione ottima\n");
    SOLvettfree(sol);
    free(vm);
}

int FORESTAkoala(Foresta F){
    return F->N;
}

