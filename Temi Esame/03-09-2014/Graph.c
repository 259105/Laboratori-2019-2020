#include <stdlib.h>
#include <stdio.h>
#include "ST.h"
#include "Queue.h"
#include "Graph.h"

#define MAXC 21

struct graph {int V; ST tab; };
static Edge  EDGEcreate(int v, int w);
static int **MATRIXint(int r, int c, int val);
static void  bfs(Graph G, Edge e, int *time, int *pre, int *st,int *d,int**M);

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
  G->tab = STinit(V);
  if (G->tab == NULL)
    return NULL;
  return G;
}

void GRAPHfree(Graph G) {
  STfree(G->tab);
  free(G);
}

Graph GRAPHload(FILE *fin) {
  int V=0, id;
  char label[MAXC];
  Graph G;
  G = GRAPHinit(1);

  while(fscanf(fin, "%s", label) == 1) {
    id = STsearch(G->tab, label);
    if (id<0) {id=V++; STinsert(G->tab,label,id);}
  }
  G->V=V;
  return G;
}

int* GRAPHbfs(Graph G, int id,int **M) {
  int v, time=0, *pre, *st,*d;
  pre = malloc(G->V*sizeof(int));
  st = malloc(G->V*sizeof(int));
  d=malloc(G->V* sizeof(int));
  if ((pre == NULL) || (st == NULL))
    return NULL;

  for (v=0; v < G->V; v++) {
    pre[v] = -1;
    st[v] = -1;
    d[v]=-1;
  }
  bfs(G, EDGEcreate(id,id), &time, pre, st,d,M);
  return d;
}
static void bfs(Graph G, Edge e, int *time, int *pre, int *st,int *d,int** M) {
  int v;
  Q q = Qinit();
  Qput(q, e);
  while (!Qempty(q))
    if (pre[(e = Qget(q)).w] == -1) {
      pre[e.w] = (*time)++;
      st[e.w] = e.v;
      d[e.w]= d[e.v]+1;
      for (v = 0; v < G->V; v++)
        if (M[e.w][v] == 1)
          if (pre[v] == -1)
            Qput(q, EDGEcreate(e.w, v));
    }
  Qfree(q);
}
static int check(Graph G,Edge *E,int k,int m,int ne){
    //mi creo la madtrice delle adiacenza
    int **M=MATRIXint(G->V,G->V,0);
    for(int i=0;i<ne;i++)
        M[E[i].v][E[i].w]=M[E[i].w][E[i].v]=1;
    /*
    //Verifico che ogni vertice non abbia un grado maggiore(stretto) a m
    for(int i=0;i<G->V;i++){
        int g=0;
        for(int j=0;j<G->V;j++)
            if(M[i][j]==1) g++;
        if(g>m) return 0;
    }
    //controllo il secondo vincolo
    int *d;
    for(int i=0;i<G->V;i++){
        d=GRAPHbfs(G,i,M);
        for(int j=0;j<G->V;j++)
            if(d[j]>k || d[j]<0) return 0;
    }
     */
    //Tutto in un solo doppo ciclo
    int g,*d;
    for(int i=0;i<G->V;i++){
        g=0;
        d=GRAPHbfs(G,i,M);
        for(int j=0;j<G->V;j++){
            if(d[j]>k || d[j]<0)
                return 0;
            if(M[i][j]==1) g++;
        }
        if(g>m) return 0;
    }
    return 1;
}
int GRAPHchecksol(Graph G,FILE *fin,int k,int m){
    int id1,id2,ne=0,ne_max=1;
    char label1[MAXC],label2[MAXC];
    Edge *E=malloc(sizeof(Edge));
    while (fscanf(fin,"%s %s",label1,label2)==2){
        id1=STsearch(G->tab,label1);
        id2=STsearch(G->tab,label2);
        if(id1<0 || id2<0) return 0;
        if(ne==ne_max){
            E=realloc(E,sizeof(Edge)*ne_max*2);
            ne_max*=2;
        }
        E[ne++]=EDGEcreate(id1,id2);
    }
    E=realloc(E,sizeof(Edge)*ne);
    return check(G,E,k,m,ne);
}

static int netvincoledR(Graph G,Edge *E,int N,int pos,int k,int m){
    if(pos==N){
        if(check(G,E,k,m,N))
            return 1;
        return 0;
    }
    for(int i=0;i<G->V;i++)
        for(int j=0;j<G->V;j++){
            E[pos]=EDGEcreate(i,j);
            if(netvincoledR(G,E,N,pos+1,k,m))
                return 1;
        }
    return 0;
}
void GRAPHnetvincoled(Graph G,FILE *fout,int k,int m){
    Edge* sol;
    int i,V=G->V;
    for(i=0;i<(V*(V-1))/2;i++){
        sol=malloc(sizeof(Edge)*i);
        if(netvincoledR(G,sol,i,0,k,m))
            break;
        free(sol);
    }
    //Esiste sicuramente una soluzione
    for(int j=0;j<i;j++)
        fprintf(fout,"%s %s\n",STsearchByIndex(G->tab,sol[j].v),STsearchByIndex(G->tab,sol[j].w));
}



