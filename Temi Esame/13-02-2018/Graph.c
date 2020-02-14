#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "Graph.h"
#include "PQ.h"
#include "COORD.h"

#define MAXC 10
#define maxWT INT_MAX

struct graph {int V; int E; int **madj;Coord *tabP; ST tab; };
static Edge  EDGEcreate(int v, int w);
static int **MATRIXint(int r, int c, int val);
static void  insertE(Graph G, Edge e);


static Edge EDGEcreate(int v, int w) {
  Edge e;
  e.v = v;
  e.w = w;
  return e;
}

int **MATRIXint(int r, int c, int val) {
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
  G->tabP=malloc(sizeof(Coord)*G->V);
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
  free(G->tabP);
  STfree(G->tab);
  free(G);
}

Graph GRAPHload(FILE *fin) {
  int V, i, id1, id2,x,y;
  char label1[MAXC], label2[MAXC];
  Graph G;

  fscanf(fin, "%d", &V);
  G = GRAPHinit(V);

  for (i=0; i<V; i++) {
    fscanf(fin, "%s %d %d", label1,&x,&y);
    STinsert(G->tab, label1, i);
    id1 = STsearch(G->tab, label1);
    G->tabP[id1]=COORDcreate(x,y);
  }

  while(fscanf(fin, "%s %s", label1, label2) == 2) {
    id1 = STsearch(G->tab, label1);
    id2 = STsearch(G->tab, label2);
    if (id1 >= 0 && id2 >=0){
        GRAPHinsertE(G, id1, id2);
        G->madj[id1][id2]=COORDdist(G->tabP[id1],G->tabP[id2]);
        G->madj[id2][id1]=COORDdist(G->tabP[id1],G->tabP[id2]);
    }

  }
  return G;
}

void GRAPHinsertE(Graph G, int id1, int id2) {
  insertE(G, EDGEcreate(id1, id2));
}

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;
  if (G->madj[v][w] == 0)
    G->E++;
  G->madj[v][w] = wt;
  G->madj[w][v] = wt;
}

int GRAPHdiametro(Graph G){
    int d_max=0;
    int *d;
    for(int i=0;i<G->V;i++){
        d=GRAPHspD(G,i);
        for(int j=0;j<G->V;j++)
            if(d[j]>d_max && j!=i && d[j]!= maxWT) d_max=d[j];
        free(d);
    }
    return d_max;
}

int* GRAPHspD(Graph G, int id) {
    int v;
    PQ pq = PQinit(G->V);
    int *st, *mindist;
    st = malloc(G->V*sizeof(int));
    mindist = malloc(G->V*sizeof(int));
    if ((st == NULL) || (mindist == NULL))
        return NULL;

    for (v = 0; v < G->V; v++){
        st[v] = -1;
        mindist[v] = maxWT;
        PQinsert(pq, mindist, v);
    }

    mindist[id] = 0;
    st[id] = id;
    PQchange(pq, mindist, id);

    while (!PQempty(pq)) {
        if (mindist[v = PQextractMin(pq, mindist)] != maxWT) {
            for (int i=0; i<G->V ; i++)
                if (mindist[v] + G->madj[v][i] < mindist[i] && G->madj[v][i]!=0) {
                    mindist[i] = mindist[v] + G->madj[v][i];
                    PQchange(pq, mindist, i);
                    st[i] = v;
                }
        }
    }
    free(st);
    PQfree(pq);
    return mindist;
}

static void dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st,int *CC,int cc) {
    int w = e.w;
    CC[e.w]=cc;
    st[e.w] = e.v;
    pre[w] = (*time)++;
    for (int i=0;i<G->V;i++)
        if (pre[i] == -1 && G->madj[w][i]!=0)
            dfsR(G, EDGEcreate(w, i), time, pre, post, st,CC,cc);
    post[w] = (*time)++;
}

int* GRAPHcc(Graph G, int id) {
    int v, time=0, *pre, *post, *st,*cc;
    pre = malloc(G->V * sizeof(int));
    post = malloc(G->V * sizeof(int));
    st = malloc(G->V * sizeof(int));
    cc= malloc(G->V * sizeof(int));
    int ncc=1;
    if ((pre == NULL) || (post == NULL) || (st == NULL))
        return 0;

    for (v=0; v < G->V; v++) {
        pre[v] = -1;
        post[v] = -1;
        st[v] =  -1;
    }
    cc[id]=ncc;
    dfsR(G, EDGEcreate(id,id), &time, pre, post, st,cc,ncc);

    for (v=0; v < G->V; v++)
        if (pre[v]== -1){
            ncc++;
            cc[v]=ncc;
            dfsR(G, EDGEcreate(v,v), &time, pre, post, st,cc,ncc);
        }
    return cc;
}

static int check(Graph G,Edge *E,int ne){
    int no=0,d,*cc;
    for(int i=0;i<ne;i++)
        G->madj[E[i].v][E[i].w]=G->madj[E[i].w][E[i].v]=COORDdist(G->tabP[E[i].v],G->tabP[E[i].w]);
    cc=GRAPHcc(G,0);
    for(int i=1;i<G->V;i++)
        if(cc[i]!=cc[i-1])
            no=1;
    if(!no) d=GRAPHdiametro(G);
    for(int i=0;i<ne;i++)
        G->madj[E[i].v][E[i].w]=G->madj[E[i].w][E[i].v]=0;
    if(no) return 0;
    free(cc);
    return d;
}

Edge* EDGEload(Graph G, FILE *fp,int *ne){
    int v,w,n_max=1;
    char label1[MAXC],label2[MAXC];
    Edge *E=malloc(sizeof(Edge));
    *ne=0;
    while (fscanf(fp,"%s %s",label1,label2)==2){
        v=STsearch(G->tab,label1);
        w=STsearch(G->tab,label2);
        if(*ne==n_max){
            n_max*=2;
            E=realloc(E,n_max* sizeof(Edge));
        }
        E[(*ne)++]=EDGEcreate(v,w);
    }
    return E;
}

int   confrontoD(Graph G,Edge *E1,Edge *E2,int ne1,int ne2){
    int d1,d2;
    d1=check(G,E1,ne1); d2=check(G,E2,ne2);
    if(d1==d2) return 0;
    if(d1<d2) return -1;
    return 1;
}

static Edge EDGEsetNULL(){
    Edge e;
    e.v=e.w=e.wt=-1;
    return e;
}

static int EDGEbestR(Graph G,Edge *curr_sol,Edge *b_sol,int *b_d,int pos,int k,int start1,int t,int* CC){
    int d;
    if(pos==k){
        if((d=check(G,curr_sol,k)))
            if(d<*b_d){
                *b_d=d;
                for(int i=0;i<k;i++)
                    b_sol[i]=curr_sol[i];
                t=1;
            }
        return t;
    }
    for(int i=start1;i<G->V;i++)
        for(int j=i+1;j<G->V;j++)
            if(G->madj[i][j]==0 && CC[i]!=CC[j]){
                curr_sol[pos]=EDGEcreate(i,j);
                t=EDGEbestR(G,curr_sol,b_sol,b_d,pos+1,k,start1,t,CC);
                curr_sol[pos]=EDGEsetNULL();
                start1++;
            }
    return t;
}

Edge* EDGEbest(Graph G,int *ne){
    int b_d,t=0,i,*cc;
    Edge *curr_sol,*b_sol;
    curr_sol=malloc(sizeof(Edge));
    b_sol=malloc(sizeof(Edge));
    cc=GRAPHcc(G,0);

    for(i=1;i<(G->V*(G->V-1))/2-G->E;i++){
        if(EDGEbestR(G,curr_sol,b_sol,&b_d,0,i,0,t,cc))
            break;
        curr_sol=realloc(curr_sol,(i+1)* sizeof(Edge));
        b_sol=realloc(b_sol,(i+1)* sizeof(Edge));
    }
    free(cc);
    free(curr_sol);
    (*ne)=i;
    return b_sol;
}

void EDGEstore(Graph G,Edge *E,FILE *fo,int n){
    for(int j=0;j<n;j++)
        fprintf(fo,"%s %s\n",STsearchByIndex(G->tab,E[j].v),STsearchByIndex(G->tab,E[j].w));

}
