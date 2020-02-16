#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "Graph.h"
#include "List.h"

#define MAXC 10
#define maxWT INT_MAX

struct graph {int V; int E; int **madj; ST tab; };
static Edge  EDGEcreate(int v, int w, int wt);
static int **MATRIXint(int r, int c, int val);
static void  insertE(Graph G, Edge e);

static Edge EDGEcreate(int v, int w, int wt) {
  Edge e;
  e.v = v;
  e.w = w;
  e.wt = wt;
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
  int V=0, i, id1, id2, wt;
  char label1[MAXC], label2[MAXC];
  Graph G;
  ST pretab;

  pretab=STinit(1);
  while(fscanf(fin, "%s %s %d", label1, label2, &wt) == 3) {
      id1=STsearch(pretab,label1);
      if(id1<0)
        STinsert(pretab,label1,V++);
      id2=STsearch(pretab,label2);
      if(id2<0)
          STinsert(pretab,label2,V++);
  }
  STfree(pretab);
  rewind(fin);

  G = GRAPHinit(V);

  i=0;
  while(fscanf(fin, "%s %s %d", label1, label2, &wt) == 3) {
    id1 = STsearch(G->tab, label1);
    id2 = STsearch(G->tab, label2);
    if(id1<0){
        id1=i;
        STinsert(G->tab,label1,i++);
    }
    if(id2<0){
        id2=i;
        STinsert(G->tab,label2,i++);
    }
    GRAPHinsertE(G, id1, id2, wt);
  }
  return G;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
  insertE(G, EDGEcreate(id1, id2, wt));
}

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;
  if (G->madj[v][w] == 0)
    G->E++;
  G->madj[v][w] = wt;
  G->madj[w][v] = wt;
}

int GRAPHv(Graph G){
    return G->V;
}

int checkcriccamassimale(Graph G,Lista l){
    int n=l.n;
    link t,z=l.z;
    int *vc=calloc(G->V, sizeof(int));
    for(t=l.h;t!=z;t=t->next)
        for(int i=0;i<G->V;i++)
            if(G->madj[t->v][i]>0)
                vc[i]++;
    for(int i=0;i<G->V;i++){
        if(vc[i]>n-1) return 0;//non è una cricca massimale
        for(t=l.h;t!=z;t=t->next)
            if(i==t->v && vc[i]!=n-1) return 0;//non è una cricca
    }
    return 1;
}
int checkcricca(Graph G,Lista l){
    int n=l.n;
    link t,z=l.z;
    int *vc=calloc(G->V, sizeof(int));
    for(t=l.h;t!=z;t=t->next)
        for(int i=0;i<G->V;i++)
            if(G->madj[t->v][i]>0)
                vc[i]++;
    for(int i=0;i<G->V;i++)
        for(t=l.h;t!=z;t=t->next)
            if(i==t->v && vc[i]!=n-1) return 0;//non è una cricca
    return 1;
}
static int cricchemassimaliR(Graph G,Lista *sol,Lista* b_sol,int k,int pos,int start,int n_sol){
    if(pos==k){
        for(int j=0;j<n_sol;j++)
            if(LISTAcmp(sol[j],*b_sol)==0) return 0;
        if(checkcriccamassimale(G,*b_sol))
            return 1;
        return 0;
    }
    for(int i=start;i<G->V;i++){
        *b_sol=LISTAinsert(*b_sol,i);
        if(checkcricca(G,*b_sol))
            if(cricchemassimaliR(G,sol,b_sol,k,pos+1,i+1,n_sol))
                return 1;
        *b_sol=LISTAremove(*b_sol);
    }
    return 0;
}
Lista* cricchemassimali(Graph G,int *ns){
    Lista b_sol=LISTAinit(),*sol=malloc(sizeof(Lista)*G->V);//sol viene inizializzato nella dup
    int k=0;

    for(int i=G->V-1;i>0;i--){
        if(cricchemassimaliR(G,sol,&b_sol,i,0,0,k)){
            sol[k]=LISTAdup(sol[k],b_sol);
            k++;
            i++; //impedisco di far decrescere
            LISTAfree(b_sol);
            b_sol=LISTAinit();
        }
    }
    LISTAfree(b_sol);
    *ns=k;
    return sol;
}

static void pathHR(Graph G,Lista l,int* pre,int* curr_sol,int* b_sol,int* b_val,int*val,int pos,int v_i,int v_c,int d){
    link t;
    if(v_c==v_i){
       if(d==0 && *val>*b_val){
           *b_val=*val;
           for(int i=0;i<l.n;i++)
               b_sol[i]=curr_sol[i];
       }

        return;
    }
    pre[v_c]=1;//segno che ho visitato il vertice
    //per tutti i vertici adiacenti
    for(t=l.h;t!=l.z;t=t->next){
        if(pre[t->v]==0){
            (*val)+=G->madj[v_c][t->v];
            curr_sol[pos]=t->v;
            pathHR(G,l,pre,curr_sol,b_sol,b_val,val,pos+1,v_i,t->v,d-1);
            (*val)-=G->madj[v_c][t->v];
        }
    }
    pre[v_c]=0; //backtrak
}
void pathH(Graph G,Lista l){
    link t;
    int *pre=calloc(G->V,sizeof(int));//vettore visitati
    int *b_sol=malloc(sizeof(int)*l.n);
    int *curr_sol=malloc(sizeof(int)*l.n);
    int b_val=0,val=0;
    for(int i=0;i<l.n;i++){
        b_sol[i]=-1;curr_sol[i]=-1;
    }
    for(t=l.h;t!=l.z;t=t->next){
        curr_sol[0]=t->v;
        val+=G->madj[l.h->v][t->v];
        pathHR(G,l,pre,curr_sol,b_sol,&b_val,&val,1,l.h->v,t->v,l.n-1);
        for(int i=0;i<G->V;i++)
            pre[i]=0;
        val-=G->madj[l.h->v][t->v];
    }
    printf("Cammino di Hamilton con peso massimo: ");
    for(int i=0;i<l.n;i++)
        printf("%d ",b_sol[i]);
    printf("\n\n");
}

Lista LISTAload(Graph G,FILE *fp){
    char id[21]; int v;
    Lista l=LISTAinit();
    while (fscanf(fp,"%s",id)==1){
        v=STsearch(G->tab,id);
        l=LISTAinsert(l,v);
        l.n++;
    }
    return l;
}

