//
// Created by s259105 on 19/01/2020.
//

#ifndef GRAPH_H
#define GRAPH_H

typedef struct _graph *graph;
typedef struct _edge{
    int v,w,wt;
}edge;
typedef struct _ListEdges *LE;


graph GRAPHinit(int n);
void GRAPHfree(graph G);
graph GRAPHload(FILE *fp);
int GRAPHdfs(graph G,int id);
void GRAPHprintLadj(graph G);
edge EDGEcreate(int v,int w,int wt);
void EDGEprint(graph G,edge e);
edge* Pwrst_CmbSmpl_W(graph G,edge *b_sol,int *card);
void GraphToDAG(graph G,edge* e,int card);
void DAGmaxD(graph G);

#endif //GRAPH_H
