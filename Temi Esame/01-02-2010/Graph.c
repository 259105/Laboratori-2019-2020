#include <stdlib.h>
#include <stdio.h>
#include "ST.h"
#include "Graph.h"

#define MAXC 21

struct graph {int V; int E;int C; int **madj;int **mc; ST tab,tabc; };

static Edge EDGEcreate(int v, int w, int wt);
static int **MATRIXint(int r, int c, int val);
static void  insertE(Graph G, Edge e);

static Edge EDGEcreate(int v, int w, int wt) {
  Edge e;
  e.v = v;
  e.w = w;
  e.wt = wt;
  return e;
}

static int **MATRIXint(int r, int c, int val) {
  int i, j;
  int **t = malloc(r * sizeof(int *));
  if (t == NULL)
    return NULL;
  for (i=0; i < r; i++) {
    t[i] = malloc(c * sizeof(int));
    if (t[i] == NULL)
      return NULL;
  }
  for (i=0; i < r; i++)
    for (j=0; j < c; j++)
      t[i][j] = val;
  return t;
}

Graph GRAPHinit(int V,int C) {
  Graph G = malloc(sizeof *G);
  if (G == NULL)
    return NULL;
  G->V = V;
  G->E = 0;
  G->C=C;
  G->madj = MATRIXint(V, V, 0);
  if (G->madj == NULL)
    return NULL;
  G->mc=MATRIXint(V,C,0);
  if (G->mc == NULL)
      return NULL;
  G->tab = STinit(V);
  if (G->tab == NULL)
    return NULL;
  G->tabc=STinit(C);
  if (G->tabc == NULL)
      return NULL;
  return G;
}

void GRAPHfree(Graph G) {
  int i;

  for (i=0; i<G->V; i++)
    free(G->madj[i]);
  free(G->madj);
  for (i=0; i<G->V; i++)
      free(G->mc[i]);
  free(G->mc);
  STfree(G->tab);
  STfree(G->tabc);
  free(G);
}

Graph GRAPHload(FILE *fin) {
  int V,E,C, i, id1, id2, wt,nc=0;
  char label1[MAXC], label2[MAXC];
  Graph G;

  fscanf(fin, "%d %d %d", &V,&E,&C);
  G = GRAPHinit(V,C);

  for (i=0; i<V; i++) {
    fscanf(fin, "%s", label1);
    STinsertsort(G->tab, label1);
  }
  //poiche sono ordinati nella tab di simboli allora durante la stampa sarà ordinato
  for(i=0;i<E;i++){
      fscanf(fin, "%s %s %d", label1, label2, &wt);
      id1 = STsearch(G->tab, label1);
      id2 = STsearch(G->tab, label2);
      if (id1 >= 0 && id2 >=0)
          GRAPHinsertE(G, id1, id2, wt);
  }
  while(fscanf(fin, "%s %s %d", label1, label2, &wt) == 3) {
    id1 = STsearch(G->tab, label1);
    id2 = STsearch(G->tabc, label2);
    if (id2 <0){ id2=nc++; STinsert(G->tabc,label2,id2);}
    if(id1>=0)
      G->mc[id1][id2]=wt;
  }
  return G;
}

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;

  if (G->madj[v][w] == 0)
    G->E++;
  G->madj[v][w] = wt;
}

void GRAPHstore(Graph G, FILE *fout) {
  for(int i=0;i<G->V;i++)
      for(int j=0;j<G->V;j++)
          if(G->madj[i][j]!=0)
              fprintf(fout,"%s %s\n",STsearchByIndex(G->tab,i),STsearchByIndex(G->tab,j));
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
  insertE(G, EDGEcreate(id1, id2, wt));
}

static void assegnapremi(Graph G,int *premi,int v){
    for(int i=0;i<G->C;i++)
        premi[i]+=G->mc[v][i];
}
static void rimuovipremi(Graph G,int *premi,int v){
    for(int i=0;i<G->C;i++)
        premi[i]-=G->mc[v][i];
}
static int checkpremi(Graph G,int *premi){
    for(int i=0;i<G->C;i++)
        if(!premi[i])
            return 0;
    return 1;
}
static int pathsemplR(Graph G,int v,int* visited,int *premi,int pos,int *sol,int *nv){
    if(checkpremi(G,premi)){
        *nv=pos;
        return 1;
    }
    for(int i=0;i<G->V;i++)
        if(!visited[i] && G->madj[v][i]){
            visited[i]=1;
            assegnapremi(G,premi,i);
            sol[pos]=i;
            if(pathsemplR(G,i,visited,premi,pos+1,sol,nv))
                return 1;
            sol[pos]=-1;
            rimuovipremi(G,premi,i);
            visited[i]=0;
        }
    return 0;
}
void GRAPHpathsempl(Graph G,char* v){
    int s=STsearch(G->tab,v);
    int *visited=calloc(G->V, sizeof(int)), *premi=calloc(G->C, sizeof(int));
    int *sol=malloc(sizeof(int)*G->V),nv=1,f=0;
    for(int i=0;i<G->V;i++) sol[i]=-1;

    sol[0]=s; visited[s]=1;
    assegnapremi(G,premi,s);
    f=pathsemplR(G,s,visited,premi,1,sol,&nv);
    if(!f) printf("Nessun cammino trovato.\n");
    else{
        for(int i=0;i<nv;i++)
            printf("%s ",STsearchByIndex(G->tab,sol[i]));
    }
    printf("\n");
    free(visited); free(premi); free(sol);
}

static void premiinit(Graph G,int *premi){
    for(int i=0;i<G->V;i++)
        for(int j=0;j<G->C;j++)
            if(G->mc[i][j]>0)
                premi[i]++;
}
static void updatescore(Graph G,int *val,int v,int *premi,int *ottenuti,int col){
    premi[v]--;
    if(G->mc[v][col]>0){
        (*val)+=G->mc[v][col];
        G->mc[v][col]=-G->mc[v][col];
        ottenuti[col]++;
    }
}
static void deupdatescore(Graph G,int *val,int v,int *premi,int *ottenuti,int col){
    premi[v]++;
    if(G->mc[v][col]<0 && premi[v]!=0){
        G->mc[v][col]=-G->mc[v][col];
        ottenuti[col]--;
        (*val)-=G->mc[v][col];
    }
}
static int check(Graph G,int *ottenuti){
    for(int i=0;i<G->C;i++)
        if(!ottenuti[i]) return 0;
    return 1;
}
static void bestpathR(Graph G,int *val,int *b_val,int v,int m,int *premi,int* ottenuti){
    int p=0;

    if(check(G,ottenuti)){
        p=1;
        (*val)*=2;
    }
    if(*val>*b_val)
        *b_val=*val;
    if(p)
        (*val)/=2;
    if(m>0)
    for(int i=0;i<G->V;i++)
        if(G->madj[v][i]!=0 && premi[i]>-1){
            (*val)+=G->madj[v][i];
            if(*val>=0){
                for(int j=0;j<G->C;j++){
                    updatescore(G,val,i,premi,ottenuti,j);
                    bestpathR(G,val,b_val,i,m-1,premi,ottenuti);
                    deupdatescore(G,val,i,premi,ottenuti,j);
                }
            }
            (*val)-=G->madj[v][i];
        }
}
void GRAPHbestpath(Graph G,char* v,int m){
    int s=STsearch(G->tab,v);
    int val=0,b_val=0;int *premi=calloc(G->V,sizeof(int)),*ottenuti=calloc(G->C,sizeof(int));
    //uso direttamente la matrice mc come mark poiche è un problema di ottimizzazione
    premiinit(G,premi);
    for(int i=0;i<G->C;i++){
        updatescore(G,&val,s,premi,ottenuti,i);
        bestpathR(G,&val,&b_val,s,m,premi,ottenuti);
        deupdatescore(G,&val,s,premi,ottenuti,i);
    }
    printf("%d",b_val);
}
