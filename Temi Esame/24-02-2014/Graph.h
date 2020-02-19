#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#define MAXC 21

typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
int GRAPHcheckregolarita(Graph G);
void GRAPHpathmax(Graph G,char *S);

#endif
