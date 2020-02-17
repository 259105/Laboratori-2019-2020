#ifndef GRAPH_H
#define GRAPH_H

#include "ST.h"

typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
void Gpathsemplmax(Graph G,FILE *fout);
void GRAPHvincoli(Graph G,FILE *fout);
int GRAPHcc(Graph G,int *sol,int n);

#endif
