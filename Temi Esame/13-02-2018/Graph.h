#ifndef GRAPH_H
#define GRAPH_H

#include "ST.h"

typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *);
void  GRAPHinsertE(Graph G, int id1, int id2);
int   GRAPHdiametro(Graph G);
int*  GRAPHspD(Graph G, int id);
Edge* EDGEload(Graph G, FILE *fp,int *ne);
int   confrontoD(Graph G,Edge *E1,Edge *E2,int ne1,int ne2);
Edge* EDGEbest(Graph G,int *ne);
void EDGEstore(Graph G,Edge *E,FILE *fo,int n);

#endif
