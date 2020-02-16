#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>

typedef struct edge { int v; int w; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHinsertE(Graph G, int id1, int id2);
int   checkIS(Graph G,int *V,int n);
void  ISM(Graph G,FILE *fo);
int* SOLload(Graph G,FILE *f,int *ns);

#endif
