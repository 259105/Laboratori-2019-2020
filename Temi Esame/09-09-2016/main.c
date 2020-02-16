//
// Created by s259105 on 16/02/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc,char** argv){
    if(argc!=4) exit(1);
    FILE *fg,*fs,*fout;
    fg=fopen(argv[1],"r");
    fs=fopen(argv[2],"r");
    fout=fopen(argv[3],"w");
    if(fg==NULL || fs==NULL || fout==NULL) exit(2);
    Graph G=GRAPHload(fg);
    int ns,*sol=SOLload(G,fs,&ns);

    printf("La soluzione %se' un insieme indipendente\n",checkIS(G,sol,ns)? "":"NON ");
    free(sol);
    ISM(G,fout);

    GRAPHfree(G);
    fclose(fg);fclose(fs);fclose(fout);
    return 0;
}
