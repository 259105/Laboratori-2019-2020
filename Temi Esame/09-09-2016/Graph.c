#include <stdlib.h>
#include <stdio.h>
#include "ST.h"
#include "Graph.h"

#define MAXC 21

struct graph {int V; int E; int **madj; ST tab; };
static Edge  EDGEcreate(int v, int w);
static int **MATRIXint(int r, int c, int val);
static void  insertE(Graph G, Edge e);

static Edge EDGEcreate(int v, int w) {
  Edge e;
  e.v = v;
  e.w = w;
  return e;
}
static int **MATRIXint(int r, int c, int val) {
  int i, j;
  int **t = malloc(r * sizeof(int *));
  if (t==NULL)
    return NULL;

  for (i=0; i < r; i++) {
    t[i] = malloc(c * sizeof(int));
    if (t[i]==NULL)
      return NULL;
  }
  for (i=0; i < r; i++)
    for (j=0; j < c; j++)
      t[i][j] = val;
  return t;
}
Graph GRAPHinit(int V) {
  Graph G = malloc(sizeof *G);
  if (G == NULL)
    return NULL;
  G->V = V;
  G->E = 0;
  G->madj = MATRIXint(V, V, 0);
  if (G->madj == NULL)
    return NULL;
  G->tab = STinit(V);
  if (G->tab == NULL)
    return NULL;
  return G;
}
void GRAPHfree(Graph G) {
  int i;
  for (i=0; i<G->V; i++)
    free(G->madj[i]);
  free(G->madj);
  STfree(G->tab);
  free(G);
}
Graph GRAPHload(FILE *fin) {
  int V=0, id1, id2;
  char label1[MAXC], label2[MAXC];
  Graph G;
  ST pretab=STinit(1);

  while (fscanf(fin,"%s %s",label1,label2)==2){
      id1=STsearch(pretab,label1);
      if(id1<0)
          STinsert(pretab,label1,V++);
      id2=STsearch(pretab,label2);
      if(id2<0)
          STinsert(pretab,label2,V++);
  }
  STfree(pretab); rewind(fin);
  G = GRAPHinit(V);
  V=0;
  while(fscanf(fin, "%s %s", label1, label2) == 2) {
      id1=STsearch(G->tab,label1);
      if(id1<0){
          id1=V;
          STinsert(G->tab,label1,V++);
      }
      id2=STsearch(G->tab,label2);
      if(id2<0){
          id2=V;
          STinsert(G->tab,label2,V++);
      }
      GRAPHinsertE(G, id1, id2);
  }
  return G;
}
static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w;

  if (G->madj[v][w] == 0)
    G->E++;
  G->madj[v][w] = 1;
  G->madj[w][v] = 1;
}
void GRAPHinsertE(Graph G, int id1, int id2) {
  insertE(G, EDGEcreate(id1, id2));
}

int checkIS(Graph G,int *V,int n){
    int *vadj=calloc(G->V, sizeof(int));
    for(int i=0;i<n;i++)
        for(int j=0;j<G->V;j++)
            vadj[j]+=G->madj[V[i]][j];
    for(int i=0;i<n;i++)
        if(vadj[V[i]]!=0) return 0;
    return 1;
}
static int ISMR(Graph G,int *sol,int k,int pos,int start){
    if(pos==k){
        if(checkIS(G,sol,k))
            return 1;
        return 0;
    }
    for(int i=start;i<G->V;i++){
        sol[pos]=i;
        if(ISMR(G,sol,k,pos+1,i+1))
            return 1;
    }
    return 0;
}
void ISM(Graph G,FILE *fo){
    int *sol,i,f=0;
    for(i=G->V-1;i>0;i--){
        sol=malloc(sizeof(int)*i);
        if(ISMR(G,sol,i,0,0)){
            printf("%d\n",i);
            f=1;
            break;
        }
        free(sol);
    }
    if(f){
        for(int j=0;j<i;j++)
            fprintf(fo,"%s ",STsearchByIndex(G->tab,sol[j]));
        free(sol);
    }
}

int* SOLload(Graph G,FILE *f,int *ns){
    int n=0,*sol=malloc(sizeof(int)),n_max=1,v;
    char label[21];
    while (fscanf(f,"%s",label)==1){
        if(n==n_max){
            sol=realloc(sol,n_max*2* sizeof(int));
            n_max*=2;
        }
        v=STsearch(G->tab,label);
        sol[n++]=v;
    }
    sol=realloc(sol,n* sizeof(int));
    *ns=n;
    return sol;
}
