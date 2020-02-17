#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "Graph.h"

#define MAXC 21
#define maxWT INT_MAX

typedef struct node *link;
struct node { int v; int wt; link next; } ;
struct graph { int V; int E; link *ladj; ST tab; link z;int *vcol; } ;

static Edge  EDGEcreate(int v, int w, int wt);
static link  NEW(int v, int wt, link next);
static void  insertE(Graph G, Edge e);
static int insertCOL(Graph G,int v,char* col);
static void pathsemplmaxR(Graph G,int *sol,int *b_sol,int *val,int *b_val,int pos,int *pre,int v,int *n);
static int checkCOL(Graph G,int v,int w);
static void vincoliR(Graph G,int *sol,int *b_sol,int *b_val,int *v,int pos,int start,int k);
static void dfsR(Graph G, Edge e, int *time, int *visited);
static int checknumCOL(Graph G,int *sol,int n);


static Edge EDGEcreate(int v, int w, int wt) {
  Edge e;
  e.v = v;
  e.w = w;
  e.wt = wt;
  return e;
}

static link NEW(int v, int wt, link next) {
  link x = malloc(sizeof *x);
  if (x == NULL)
    return NULL;
  x->v = v;
  x->wt = wt;
  x->next = next;
  return x;
}

Graph GRAPHinit(int V) {
  int v;
  Graph G = malloc(sizeof *G);
  if (G == NULL)
    return NULL;

  G->V = V;
  G->E = 0;
  G->z = NEW(-1, 0, NULL);
  if (G->z == NULL)
    return NULL;
  G->ladj = malloc(G->V*sizeof(link));
  if (G->ladj == NULL)
    return NULL;
  for (v = 0; v < G->V; v++)
    G->ladj[v] = G->z;
  G->tab = STinit(V);
  if (G->tab == NULL)
    return NULL;
  G->vcol=calloc(G->V,sizeof(int));
  return G;
}

void GRAPHfree(Graph G) {
  int v;
  link t, next;
  for (v=0; v < G->V; v++)
    for (t=G->ladj[v]; t != G->z; t = next) {
      next = t->next;
      free(t);
    }
  STfree(G->tab);
  free(G->vcol);
  free(G->ladj);
  free(G->z);
  free(G);
}

Graph GRAPHload(FILE *fin) {
  int V=0, id1, id2, wt;
  char label1[MAXC], label2[MAXC],col1[6],col2[6];
  Graph G;
  ST pretab=STinit(1);

  while (fscanf(fin,"%s %*s %*d %s %*s",label1,label2)==2){
      id1=STsearch(pretab,label1);
      if(id1<0) STinsert(pretab,label1,V++);
      id2=STsearch(pretab,label2);
      if(id2<0) STinsert(pretab,label2,V++);
  }
  STfree(pretab);
  rewind(fin);
  G = GRAPHinit(V);
  V=0;
  while(fscanf(fin,"%s %s %d %s %s",label1,col1,&wt,label2,col2)==5) {
    id1 = STsearch(G->tab, label1);
    if(id1<0){id1=V++; STinsert(G->tab,label1,id1);}
    id2 = STsearch(G->tab, label2);
    if(id2<0){id2=V++; STinsert(G->tab,label2,id2);}
    GRAPHinsertE(G, id1, id2, wt);
    if(!insertCOL(G,id1,col1)){ GRAPHfree(G); exit(3);}
    if(!insertCOL(G,id2,col2)){ GRAPHfree(G); exit(3);}
  }
  return G;
}

static int insertCOL(Graph G,int v,char* col){
    //1:=nero 2:=rosso
    if(strcmp(col,"ROSSO")==0){
        if(G->vcol[v]==1) return 0;
        G->vcol[v]=2;
    }
    else if(strcmp(col,"NERO")==0){
        if(G->vcol[v]==2) return 0;
        G->vcol[v]=1;
    }
    return 1;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
  insertE(G, EDGEcreate(id1, id2, wt));
}

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;

  G->ladj[v] = NEW(w, wt, G->ladj[v]);
  G->ladj[w] = NEW(v, wt, G->ladj[w]);
  G->E++;
}

void Gpathsemplmax(Graph G,FILE *fout)  {
    int *pre=calloc(G->V, sizeof(int)),*sol=malloc(sizeof(int)*G->V),*b_sol=malloc(sizeof(int)*G->V),val=0,b_val=0,n=0;
    for(int i=0;i<G->V;i++){ sol[i]=-1;b_sol[i]=-1;}
    for(int i=0;i<G->V;i++){
        sol[0]=i; pre[i]=1;
        pathsemplmaxR(G,sol,b_sol,&val,&b_val,1,pre,i,&n);
    }
    for(int i=0;i<n;i++)
        fprintf(fout,"%s ",STsearchByIndex(G->tab,b_sol[i]));
    fprintf(fout,"\n");
}

static void pathsemplmaxR(Graph G,int *sol,int *b_sol,int *val,int *b_val,int pos,int *pre,int v,int *n){
    int f=0; //non ho trovato vertici adiacenti diposnibili
    link t;

    for(t=G->ladj[v];t!=G->z;t=t->next)
        if(pre[t->v]==0 && checkCOL(G,v,t->v)){
            f=1;
            sol[pos]=t->v; (*val)+=t->wt; pre[t->v]=1;
            pathsemplmaxR(G,sol,b_sol,val,b_val,pos+1,pre,t->v,n);
            sol[pos]=-1; (*val)-=t->wt; pre[t->v]=0;
        }
    if(!f)
        if(*val>*b_val){
            *b_val=*val;
            *n=pos;
            for(int i=0;i<*n;i++)
                b_sol[i]=sol[i];

        }
}

static int checkCOL(Graph G,int v,int w){
    if(G->vcol[v]==2 && G->vcol[w]==2) return 0;
    return 1;
}

void GRAPHvincoli(Graph G,FILE *fout){
    int *sol,*b_sol;
    int v,best_val=0;
    sol=malloc(sizeof(int)*G->V);
    b_sol=malloc(sizeof(int)*G->V);
    for(int i=0;i<G->V;i++) {sol[i]=-1;b_sol[i]=-1;}
    for(int i=G->V;i>0;i--)
        vincoliR(G,sol,b_sol,&best_val,&v,0,0,i);
    for(int i=0;i<v;i++)
        fprintf(fout,"%s ",STsearchByIndex(G->tab,b_sol[i]));
    fprintf(fout,"\n");
}
static void vincoliR(Graph G,int *sol,int *b_sol,int *b_val,int *v,int pos,int start,int k){
    int val=0;
    if(pos==k){
        if((val=GRAPHcc(G,sol,k))!=0 && checknumCOL(G,sol,k) && val>*b_val){
            *b_val=val;
            *v=k;
            for(int i=0;i<G->V;i++)
                b_sol[i]=sol[i];
        }
        return;
    }
    for(int i=start;i<G->V;i++){
        sol[pos]=i;
        vincoliR(G,sol,b_sol,b_val,v,pos+1,i+1,k);
        sol[pos]=-1;
    }
}

int GRAPHcc(Graph G,int *sol,int n){
    link t;
    int *visited=malloc(sizeof(int)*G->V),val=0,time=0;
    for(int i=0;i<G->V;i++) {
        for(int j=0;j<n;j++){
            if(i==sol[j]) {visited[i]=-1;break;}
            else visited[i]=0;
        }
    }
    dfsR(G,EDGEcreate(sol[0],sol[0],0),&time,visited);
    for(int i=0;i<n;i++)
        if(visited[sol[i]]==-1) return 0;

    for(int i=0;i<n;i++)
        for(t=G->ladj[sol[i]];t!=G->z;t=t->next)
            for(int j=0;j<n;j++)
                if(sol[j]==t->v)
                    val+=t->wt;
    return val/2;
}
static void dfsR(Graph G, Edge e, int *time, int *visited) {
    link t; int w = e.w;
    visited[w] = (*time)++;
    for (t = G->ladj[w]; t != G->z; t = t->next)
        if (visited[t->v] == -1)
            dfsR(G, EDGEcreate(w, t->v,t->wt), time, visited);
}
static int checknumCOL(Graph G,int *sol,int n){
    int Col[2]={0,0};
    for(int i=0;i<n;i++)
        if(G->vcol[sol[i]]==1) Col[0]++; //incremento il colore nero
        else Col[1]++; //incremento il colore rosso
    if(sqrt((Col[1]-Col[0])*(Col[1]-Col[0]))>2) return 0;
    return 1;
}
