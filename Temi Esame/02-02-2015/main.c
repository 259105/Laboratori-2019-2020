//
// Created by s259105 on 18/02/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc,char** argv){
    if(argc!=3) exit(1);
    FILE *fg,*fs;
    fg=fopen(argv[1],"r");
    fs=fopen(argv[2],"r");
    if(fs==NULL || fg==NULL) exit(2);
    Graph G=GRAPHload(fg);
    int *sol,N;

    sol=GSolload(G,fs,&N);
    if(sol==NULL) printf("Soluzione non valida.\n");
    else if(Gcheckregalo(G,sol)) printf("Soluzione valida.\n");
    else printf("Soluzione non valida.\n");
    free(sol);
    GRAPHbestsol(G);

    GRAPHfree(G); //non funziona non so perche...
    fclose(fg); fclose(fs);
    return 0;
}
