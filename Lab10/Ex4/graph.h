//
// Created by s259105 on 08/01/2020.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include "st.h"


typedef struct edge{
    int v;
    int w;
    int wt;
}Edge;
typedef struct graph *Graph;

Graph GRAPHinit(int v);
void GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin,int v);
void GRAPHstore(Graph G,FILE *fout);
void GRAPHinsertE(Graph G,int id1,int id2,int wt);
void GRAPHladj(Graph G);
int GRAPHverifiaLadj(Graph G);
int GRAPHadiacentiMadj(Graph G);
int GRAPHadiacentiLadj(Graph G);
//Graph GRAPHsortST(Graph G);

#endif //GRAPH_H
