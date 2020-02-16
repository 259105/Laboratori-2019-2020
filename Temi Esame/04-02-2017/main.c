//
// Created by s259105 on 15/02/2020.
//

#include "List.h"
#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc,char** argv){
    if(argc!=3) exit(1);
    FILE *fg,*fs;
    Graph G;
    int ns;
    Lista *sol;
    Lista solf;
    fg=fopen(argv[1],"r");
    fs=fopen(argv[2],"r");
    if(fg==NULL || fs==NULL) exit(2);
    G=GRAPHload(fg);
    solf=LISTAload(G,fs);
    if(checkcriccamassimale(G,solf)) printf("La soluzione proposta e' una cricca massimale\n\n");
    else printf("La soluzione proposta NON e' una cricca massimale\n\n");
    LISTAfree(solf);
    sol=cricchemassimali(G,&ns);
    for(int i=0;i<ns;i++){
        printf("Cricca massimale: ");
        LISTAstorage(stdout,sol[i]);
        if(sol[i].n>3) //soluzione banale
            pathH(G,sol[i]);
    }
    for(int i=0;i<GRAPHv(G);i++)
        LISTAfree(sol[i]);
    free(sol);
    GRAPHfree(G);
    fclose(fg);fclose(fs);
    return 6;
}
