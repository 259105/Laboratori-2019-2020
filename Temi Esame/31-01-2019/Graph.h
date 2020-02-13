#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

typedef struct edge { int v; int w; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHstore(Graph G, FILE *fout);
int   GRAPHgetIndex(Graph G, char *label);
void  GRAPHinsertE(Graph G, int id1, int id2);
void  GRAPHremoveE(Graph G, int id1, int id2);
void  GRAPHedges(Graph G, Edge *a);
void  GRAPHpath(Graph G, int id1, int id2);
void  GRAPHbfs(Graph G, int id);
int   GRAPHv(Graph G);
int   check(Graph G,int* k,int n);
int*  KERNELmin(Graph G,FILE *fo,int *n);
int   LpathSempl(Graph G,int *K,int nk);
int*  KERNELload(Graph G,FILE *fp,int *n);

#endif
