//
// Created by s259105 on 18/02/2020.
//
#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

int main(int argc,char** argv){
    if(argc!=3) exit(1);
    FILE *fg,*fs;
    fg=fopen(argv[1],"r");
    fs=fopen(argv[2],"r");
    if(fg==NULL || fs==NULL) exit(2);
    Graph G=GRAPHload(fg);
    int **M,nv[2],*I=NULL,ni;
    int k,p;
    char label1[21],label2[21];
    M=GRAPHsolLoad(G,fs,nv);
    I=intersezione(G,M[0],M[1],nv[0],nv[1],&ni);
    Gpathstoreintersection(G,stdout,M,I,ni,nv);
    printf("Inserisci <k> <p> <sorgente> <destinazione>:\n");
    scanf("%d %d %s %s",&k,&p,label1,label2);
    GRAPHpathvincoled(G,stdout,k,p,label1,label2);
    GRAPHfree(G);
    fclose(fg);fclose(fs);
    return 0;
}
