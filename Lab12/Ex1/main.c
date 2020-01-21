//
// Created by s259105 on 19/01/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#define nome_file "grafo5.txt"

int main(void){
    graph G;
    edge* edgetoremove=NULL;
    int cardi;
    FILE *fp;

    fp=fopen(nome_file,"r");
    if(fp==NULL){
        fprintf(stderr,"Errore apertura file.\n");
        exit(1);
    }
    G=GRAPHload(fp);
    printf("Stampa grafo corrente:\n");
    GRAPHprintLadj(G);
    printf("\n");
    if(GRAPHdfs(G,0)){
        printf("Stampa  insieme archi che possono essere tagliati per formare un DAG;\n");
        edgetoremove=Pwrst_CmbSmpl_W(G,edgetoremove,&cardi);
        printf("Taglio insieme di archi con peso massimo:\n");
        GraphToDAG(G,edgetoremove,cardi);
        free(edgetoremove);
        printf("Stampo DAG creato:\n");
        GRAPHprintLadj(G);
    } else
        printf("Il grafo e' gia' un DAG:\n");

    DAGmaxD(G);

    GRAPHfree(G);
    return 0;
}
