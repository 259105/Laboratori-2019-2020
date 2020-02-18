#include <stdlib.h>
#include <stdio.h>
#include "ST.h"
#include "Graph.h"

#define MAXC 11

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
      if(id1<0) STinsert(pretab,label1,V++);
      id2=STsearch(pretab,label2);
      if(id2<0) STinsert(pretab,label2,V++);
  }
  STfree(pretab); rewind(fin);
  G=GRAPHinit(V); V=0;
  while(fscanf(fin, "%s %s", label1, label2) == 2) {
    id1 = STsearch(G->tab, label1);
    if(id1<0) {id1=V++; STinsert(G->tab,label1,id1);}
    id2 = STsearch(G->tab, label2);
    if(id2<0) {id2=V++; STinsert(G->tab,label2,id2);}
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

int Gcheckregalo(Graph G,int *sol){
    for(int i=0;i<G->V;i++)
        for(int j=0;j<G->V;j++)
            if(G->madj[i][j]>0 && sol[i]==sol[j])
                return 0;
    return 1;
}
int* GSolload(Graph G,FILE *fin,int *N){
    int n,na,id,*sol=malloc(sizeof(int));
    char label[MAXC];
    for(int i=0;i<G->V;i++) sol[i]=-1;

    fscanf(fin,"%d",&n);
    for(int i=0;i<n;i++){
        fscanf(fin,"%d",&na);
        for(int j=0;j<na;j++){
            fscanf(fin,"%s",label);
            id=STsearch(G->tab,label);
            if(sol[id]!=-1) return NULL; //prima condizione
            sol[id]=i;
        }
    }
    *N=n;
    return sol;
}

int bestsolR(Graph G,int *sol,int m,int pos){
    if(pos==G->V){
        if(Gcheckregalo(G,sol))
            return 1;
        return 0;
    }
    for(int i=0;i<m;i++){
        sol[pos]=i;
        if(bestsolR(G,sol,m,pos+1)) return 1;
    }
    return 0;
}
void GRAPHbestsol(Graph G){
    int *sol=malloc(sizeof(int)*G->V),i,N;
    for(i=0;i<G->V;i++) sol[i]=-1;

    for(i=1;i<=G->V;i++)
        if(bestsolR(G,sol,i,0))
            break;
    N=i;
    printf("Numero minimo di tipologie e' %d.\n",N);
    for(i=0;i<N;i++){
        printf("{");
        for(int j=0;j<G->V;j++)
            if(sol[j]==i) printf("%s ",STsearchByIndex(G->tab,j));
        printf("}");
    }
}
