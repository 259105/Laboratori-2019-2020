//
// Created by s259105 on 23/12/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "diagonale.h"
#define MAXDIAG 3
#define file "elementi.txt"

int checkelem(int k,int pos,elemento elem){
    if(pos==0 && elem->prec==1){
        return 0;
    }
    if(pos==0 && elem->ingr!=1){
        return 0;
    }
    if(pos!=k-1 && elem->finl==1){
        return 0;
    }
    return 1;
}

void disp_rip(int pos,int k,int n,diagonale sol,diagonale  b_sol,elemento *elem,int dd){
    int i;
    if(pos>=k){
        if(sol->diff<=dd && sol->pnt>b_sol->pnt && sol->diff<b_sol->diff){
            DIAGONALEcopy(b_sol,sol);
        }
        return;
    }
    for(i=0;i<n;i++){
        if(sol->diff+elem[i]->diff<=dd && checkelem(k,pos,elem[i])){
            DIAGONALEinsert(sol,elem[i]);
            disp_rip(pos+1,k,n,sol,b_sol,elem,dd);
            DIAGONALEremove(sol);
        }
    }
}

diagonale* disp_rip_R(int max_diag,int max_elem,elemento *elem,int n_elem,int dd,int dp){

}

diagonale* disp_rip_w(int max_diag,int max_elem,elemento *elem,int n_elem,int dd,int dp){
    int k,i;
    diagonale *programma=NULL,*b_p;
    b_p=programma=DIAGONALEarrayinit(max_diag);
    for(i=0;i<max_diag;i++){//inizializzo con valori iniziali
        b_p[i]->pnt=0;
        b_p[i]->diff=dp;
    }
    for(i=0;i<max_diag;i++){
        for(k=1;k<max_elem;k++){// la soluzione è composta di sicuro da almeno 1 elemento
            disp_rip(0,k,n_elem,programma[i],b_p[i],elem,dd);
        }
        if(i==1 && b_p[i]->diff>=8) {
            b_p[i]->pnt *= 1.5;
        }
        dp-=b_p[i]->diff;
    }

}

int main(void){
    diagonale *d;
    elemento *elementi=NULL;
    FILE *fp;
    int n;//numero di elementi totali
    int dd=10,dp=20;
    fp=fopen(file,"r");
    if(fp==NULL){
        fprintf(stderr,"Errore file inserito non valido.\n");
        return 1;
    }
    elementi=inputelementi(fp,elementi,&n);
    ELEMENTIprint(elementi,n);

    d=disp_rip_w(MAXDIAG,MAXELEM,elementi,n,dd,dp);
    //stampa diagonali



    ELEMENTOarrayfree(elementi,n);
    return 0;
}
