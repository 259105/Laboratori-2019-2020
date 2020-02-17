//
// Created by s259105 on 17/02/2020.
//
#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

int main(int argc,char** argv){
    //int sol[3]={0,1,2};
    if(argc!=2) exit(1);
    FILE *fin;
    fin=fopen(argv[1],"r");
    if(fin==NULL) exit(2);
    Graph G=GRAPHload(fin);
    Gpathsemplmax(G,stdout);
    //printf("%d",GRAPHcc(G,sol,3));
    GRAPHvincoli(G,stdout);
    GRAPHfree(G);
    fclose(fin);
    return 0;
}
