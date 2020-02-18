#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>

typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
int** GRAPHsolLoad(Graph G,FILE *fs,int *ns);
void Gpathstoreintersection(Graph G,FILE *fout,int **M,int *I,int ni,int *nv);
void GRAPHpathvincoled(Graph G,FILE *fout,int k,int p,char* lab1,char *lab2);
int* intersezione(Graph G,int V1[], int V2[], int v1, int v2, int* ni);


#endif
