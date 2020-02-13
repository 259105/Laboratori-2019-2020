//
// Created by s259105 on 13/02/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc,char** argv){
    if(argc!=4) exit(1);;
    Graph G;
    FILE *fg,*fk,*fo;
    int nk=0,*K,l=0;
    fg=fopen(argv[1],"r");
    fk=fopen(argv[2],"r");
    fo=fopen(argv[3],"w");
    if(fg==NULL || fk==NULL || fo==NULL) exit(1);
    G=GRAPHload(fg);
    K=KERNELload(G,fk,&nk);
    if(!check(G,K,nk)) printf("Non e' un Kernel.\n");
    else printf("E' un Kernel.\n");
    K=KERNELmin(G,fo,&nk);
    l=LpathSempl(G,K,nk);
    printf("distanza %d.\n",l);
    free(K);GRAPHfree(G);
    fclose(fg);
    fclose(fk);
    fclose(fo);
}
