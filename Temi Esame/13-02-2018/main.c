//
// Created by s259105 on 13/02/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(){
    Graph G;
    FILE *fg,*fs1,*fs2;
    int ne1,ne2,ne;
    Edge *E1,*E2,*E;
    //apertura file
    fg=fopen("grafo.txt","r");
    fs1=fopen("sol1.txt","r");
    fs2=fopen("sol2.txt","r");
    G=GRAPHload(fg);
    E1=EDGEload(G,fs1,&ne1);
    E2=EDGEload(G,fs2,&ne2);
    printf("La sol %d ha il diametro inferirore\n",confrontoD(G,E1,E2,ne1,ne2)<=0 ? 1:2);
    E=EDGEbest(G,&ne);
    EDGEstore(G,E,stdout,ne);
    //GRAPHfree(G);
    //free(E1);
    //free(E2);
    //free(E);
    return 6;
}
