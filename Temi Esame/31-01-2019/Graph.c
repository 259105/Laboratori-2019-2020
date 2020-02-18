#include <stdlib.h>
#include <stdio.h>
#include "ST.h"
#include "Queue.h"
#include "Graph.h"
#include "UF.h"

#define MAXC 11

struct graph {int V; int E; int **madj;int **madjno; ST tab; };
static Edge  EDGEcreate(int v, int w);
static int **MATRIXint(int r, int c, int val);
static void  insertE(Graph G, Edge e);
static void  removeE(Graph G, Edge e);
static int   pathR(Graph G, int v, int w, int *visited);
static void  bfs(Graph G, Edge e, int *time, int *pre, int *st);

static Edge EDGEcreate(int v, int w) {
  Edge e;
  e.v = v;
  e.w = w;
  return e;
}

static int **MATRIXint(int r, int c, int val) {
  int i, j, **t;
  t = malloc(r * sizeof(int *));
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
  G->madjno= MATRIXint(V,V,0);
  if (G->madj == NULL)
    return NULL;
  if (G->madjno == NULL)
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
  int V, i, id1, id2;
  char label1[MAXC], label2[MAXC];
  Graph G;

  fscanf(fin, "%d", &V);
  G = GRAPHinit(V);

  for (i=0; i<V; i++) {
    fscanf(fin, "%s", label1);
    STinsert(G->tab, label1, i);
  }

  while(fscanf(fin, "%s %s", label1, label2) == 2) {
    id1 = STsearch(G->tab, label1);
    id2 = STsearch(G->tab, label2);
    if (id1 >= 0 && id2 >=0)
      GRAPHinsertE(G, id1, id2);
  }

  for(i=0;i<G->V;i++)
      for(int j=0;j<G->V;j++)
          if(G->madj[i][j]!=0)
              G->madjno[j][i]=G->madjno[i][j]=G->madj[i][j];

  return G;
}

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w;

  if (G->madj[v][w] == 0)
    G->E++;
  G->madj[v][w] = 1;
}

void GRAPHstore(Graph G, FILE *fout) {
  int i;
  Edge *a;

  a = malloc(G->E * sizeof(Edge));
  if (a == NULL)
    return;

  GRAPHedges(G, a);

  fprintf(fout, "%d\n", G->V);
  for (i = 0; i < G->V; i++)
    fprintf(fout, "%s\n", STsearchByIndex(G->tab, i));

  for (i = 0; i < G->E; i++)
    fprintf(fout, "%s  %s\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w));

}

int GRAPHgetIndex(Graph G, char *label) {
  int id;
  id = STsearch(G->tab, label);
  if (id == -1) {
    id = STsize(G->tab);
    STinsert(G->tab, label, id);
  }
  return id;
}

void GRAPHinsertE(Graph G, int id1, int id2) {
  insertE(G, EDGEcreate(id1, id2));
}

void GRAPHremoveE(Graph G, int id1, int id2) {
  removeE(G, EDGEcreate(id1, id2));
}

static void  removeE(Graph G, Edge e) {
  int v = e.v, w = e.w;
  if (G->madj[v][w] == 1)
    G->E--;
  G->madj[v][w] = 0;
}

void  GRAPHedges(Graph G, Edge *a) {
  int v, w, E = 0;
  for (v=0; v < G->V; v++)
    for (w=0; w < G->V; w++)
      if (G->madj[v][w] == 1)
        a[E++] = EDGEcreate(v, w);
}


void GRAPHpath(Graph G, int id1, int id2) {
  int t, found, *visited;

  visited = malloc(G->V*sizeof(int));
  if (visited == NULL)
    return;

  for ( t = 0 ; t < G->V ; t++)
    visited[t] = 0;

  if (id1 < 0 || id2 < 0)
    return;

  found = pathR(G, id1, id2, visited);
  if (found == 0)
    printf("\n Path not found!\n");
}

static int pathR(Graph G, int v, int w, int *visited) {
  int t;
  if (v == w)
    return 1;
  visited[v] = 1;
  for ( t = 0 ; t < G->V ; t++)
    if (G->madj[v][t] == 1)
      if (visited[t] == 0)
        if (pathR(G, t, w, visited)) {
          printf("edge (%s, %s) belongs to path \n", STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, t));
          return 1;
        }
  return 0;
}

void GRAPHbfs(Graph G, int id) {
  int v, time=0, *pre, *st;
  pre = malloc(G->V*sizeof(int));
  st = malloc(G->V*sizeof(int));
  if ((pre == NULL) || (st == NULL))
    return;

  for (v=0; v < G->V; v++) {
    pre[v] = -1;
    st[v] = -1;
  }

  bfs(G, EDGEcreate(id,id), &time, pre, st);

  printf("\n Resulting BFS tree \n");
  for (v=0; v < G->V; v++)
    if (st[v] != -1)
      printf("%s's parent is: %s \n", STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, st[v]));
}

static void bfs(Graph G, Edge e, int *time, int *pre, int *st) {
  int v;
  Q q = Qinit();
  Qput(q, e);
  while (!Qempty(q))
    if (pre[(e = Qget(q)).w] == -1) {
      pre[e.w] = (*time)++;
      st[e.w] = e.v;
      for (v = 0; v < G->V; v++)
        if (G->madj[e.w][v] == 1)
          if (pre[v] == -1)
            Qput(q, EDGEcreate(e.w, v));
    }
  Qfree(q);
}

int GRAPGv(Graph G){
    return G->V;
}

int check(Graph G,int* k,int n){
    UFinit(G->V);
    for(int i=0;i<n;i++) //per ogni vertice del kernel
        for(int j=0;j<n;j++){
            if(i==j) continue; // faccio confronto con tutti gli altri vertici del kernel
            for(int x=0;x<G->V;x++){
                if(G->madjno[k[i]][x]==0) continue; // se non è adicente salto l'iter
                if(G->madjno[k[i]][x]!=0 && x==k[j]) return 0; // se è adiacente ad un altro vertice del kernel (condizione 1)
                else if(!UFfind(k[i],x)) UFunion(k[i],x); // se è adiacente con un vertice nn appartenente al kernel
                //lo aggiungo nella UF
            }
        }
    int c,i;
    for(c=0,i=0;i<G->V;i++) // controllo se tutti i vertici sono nella stessa cc
        if(UFfind(0,i)) c++; //funziona solo con una cc;
    UFfree();
    if(c!=i) return 0; //se qualche vertice non fa parte della stessa cc ritorno 0 (condizione 2)
    return 1;
}

static int powerset(Graph G,int* curr_sol,int *b_sol,int k,int pos,int start){
    if(pos>=k){
        if(check(G,curr_sol,k)){
            for(int i=0;i<G->V;i++)
                b_sol[i]=curr_sol[i];
            return 1;
        }
        return 0;
    }

    for(int i=start;i<G->V;i++){
        curr_sol[pos]=i;
        if(powerset(G,curr_sol,b_sol,k,pos+1,i+1))
            return 1;
        curr_sol[pos]=-1;
    }
    return 0;
}

static void KERNELstorage(Graph G,int *v,FILE *fo,int n){
    for(int i=0;i<n;i++)
        fprintf(fo,"%s ",STsearchByIndex(G->tab,v[i]));
}

int* KERNELmin(Graph G,FILE *fo,int *n){
    int *curr_sol,*b_sol,i;

    curr_sol=malloc(sizeof(int)*G->V);
    b_sol=malloc(sizeof(int)*G->V);
    for(i=0;i<G->V;i++)
        curr_sol[i]=b_sol[i]=-1;

    for(i=0;i<G->V;i++){
        if(powerset(G,curr_sol,b_sol,i,0,0)){
            KERNELstorage(G,b_sol,fo,i);
            break;
        }
    }
    *n=i;
    return b_sol;
}

static int appK(int v,int *K,int n){
    for(int i=0;i<n;i++)
        if(K[i]==v) return 1;
    return 0;
}

static void LpathSemplR(Graph G,int v,int *K,int time,int *pre,int *l,int *b_l,int nk){
    pre[v]=time;
    if(appK(v,K,nk))
        if(*l>*b_l)
            *b_l=*l;
    for(int i=0;i<G->V;i++)
        if(G->madj[v][i]!=0 && pre[i]==-1){
            (*l)++;
            LpathSemplR(G,i,K,time++,pre,l,b_l,nk);
            (*l)--;
        }
    pre[v]=-1;
}

int LpathSempl(Graph G,int *K,int nk){
    int *pre,l=0,b_l=0;
    pre=malloc(sizeof(int)*G->V);
    for(int i=0;i<G->V;i++)
        pre[i]=-1;
    for(int i=0;i<nk;i++)
        LpathSemplR(G,K[i],K,0,pre,&l,&b_l,nk);
    return b_l;
}

int* KERNELload(Graph G,FILE *fp,int *n){
    int *K;
    char label[MAXC];
    K=malloc(sizeof(int)*G->V);
    for(int i=0;i<G->V;i++)
        K[i]=-1;
    while (fscanf(fp,"%s",label)==1)
        K[(*n)++]=STsearch(G->tab, label);
    return K;
}
