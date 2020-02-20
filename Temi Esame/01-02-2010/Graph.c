#include <stdlib.h>
#include <stdio.h>
#include "ST.h"
#include "Graph.h"

struct graph {int V; int E; int **madj; ST tab; };

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
  int V=0, id1, id2, wt;
  char label1[MAXC], label2[MAXC];
  Graph G;
  ST pretab=STinit(1);

  while (fscanf(fin,"%s %*d %s",label1,label2)==2){
      id1 = STsearch(pretab, label1);
      if(id1<0) STinsert(pretab,label1,V++);
      id2 = STsearch(pretab, label2);
      if(id2<0) STinsert(pretab,label2,V++);
  }
  G=GRAPHinit(V); V=0;
  STfree(pretab); rewind(fin);

  while(fscanf(fin, "%s %d %s", label1,&wt, label2 ) == 3) {
      id1 = STsearch(G->tab, label1);
      if(id1<0) {id1=V++; STinsert(G->tab,label1,id1);}
      id2 = STsearch(G->tab, label2);
      if(id2<0) {id2=V++; STinsert(G->tab,label2,id2);}
      GRAPHinsertE(G, id1, id2, wt);
  }
  return G;
}

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;

  if (G->madj[v][w] == 0)
    G->E++;
  G->madj[v][w] = wt;
}
void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
  insertE(G, EDGEcreate(id1, id2, wt));
}

int GRAPHcheckregolarita(Graph G){
    int **degree=MATRIXint(G->V,2,0); //0:=out 1:=in
    for(int i=0;i<G->V;i++)
        for(int j=0;j<G->V;j++)
            if(G->madj[i][j]>0){
                degree[i][0]++; //arco uscente dal vertice i
                degree[j][1]++; //arco entrante dal vertice j
            }
    int g=degree[0][0];//grado di riferiemento
    for(int i=0;i<G->V;i++){
        if(degree[i][0]!=degree[i][1]) return 0;
        if(degree[i][0]!=g) return 0;
    }
    return 1;
}

static void pathmaxR(Graph G,Edge *sol,Edge *b_sol,int *val,int *b_val,int pos,int *visited,Edge e,int *N){
    int w=e.w,f=0;
    for(int i=0;i<G->V;i++)
        if(G->madj[w][i]>0 && !visited[i]){
            f=1;
            visited[i]=1;
            (*val)+=G->madj[w][i];
            sol[pos]=EDGEcreate(w,i,G->madj[w][i]);
            pathmaxR(G,sol,b_sol,val,b_val,pos+1,visited,sol[pos],N);
            sol[pos]=EDGEcreate(-1,-1,-1);
            (*val)-=G->madj[w][i];
            visited[i]=0;
        }
    if(!f){
        if(*val>*b_val){
            *b_val=*val;
            *N=pos;
            for(int i=0;i<pos;i++)
                b_sol[i]=sol[i];
        }
    }
}
void GRAPHpathmax(Graph G,char *S){
    int s=STsearch(G->tab,S);
    if(s<0){ printf("Sorgente non trovata.\n"); return;}
    //alloco sol e b_sol con dimensione V-1 perche sono cammini semplici,quindi senza cicli
    Edge *sol=malloc(sizeof(Edge)*(G->V-1)),*b_sol=malloc(sizeof(Edge)*(G->V-1));
    int val=0,b_val=0,ne=0;
    int *visited=calloc(G->V, sizeof(int));

    visited[s]=1; //la sorgente è gia visitata
    pathmaxR(G,sol,b_sol,&val,&b_val,0,visited,EDGEcreate(s,s,0),&ne);
    b_sol=realloc(b_sol, sizeof(Edge)*ne);
    if(ne==0) printf("Il vertice inserito non ha archi uscenti.\n");
    for(int i=0;i<ne;i++)
        printf("%s %d %s\n",STsearchByIndex(G->tab,b_sol[i].v),
                b_sol[i].wt,
                STsearchByIndex(G->tab,b_sol[i].w));
    free(b_sol); free(sol); free(visited);
}
