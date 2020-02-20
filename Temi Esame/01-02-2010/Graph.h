#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>

typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V,int C);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHstore(Graph G, FILE *fout);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
void  GRAPHpathsempl(Graph G,char* v);
void GRAPHbestpath(Graph G,char* v,int m);


#endif
