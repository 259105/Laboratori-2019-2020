#ifndef GRAPH_H
#define GRAPH_H

#include "ST.h"
#include "List.h"

typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
int   GRAPHv(Graph G);
int   checkcriccamassimale(Graph G,Lista l);
Lista* cricchemassimali(Graph G,int *ns);
void pathH(Graph G,Lista l);
Lista LISTAload(Graph G,FILE *fp);

#endif
