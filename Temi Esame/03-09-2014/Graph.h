#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>

typedef struct edge { int v; int w; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
int*  GRAPHbfs(Graph G, int id,int**M);
int GRAPHchecksol(Graph G,FILE *fin,int k,int m);
void GRAPHnetvincoled(Graph G,FILE *fout,int k,int m);

#endif
