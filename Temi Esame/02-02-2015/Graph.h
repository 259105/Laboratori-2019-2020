#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>

typedef struct edge { int v; int w; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHinsertE(Graph G, int id1, int id2);
int Gcheckregalo(Graph G,int *sol);
int* GSolload(Graph G,FILE *fin,int *N);
void GRAPHbestsol(Graph G);

#endif
