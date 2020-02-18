#include <stdlib.h>
#include <stdio.h>
#include "ST.h"
#include "Graph.h"

#define MAXC 21

struct graph {int V; int E; int **madj; ST tab; };

static       Edge EDGEcreate(int v, int w, int wt);
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

  while(fscanf(fin,"%s %*d %s",label1,label2)==2){
      id1=STsearch(pretab,label1);
      if(id1<0) STinsert(pretab,label1,V++);
      id2=STsearch(pretab,label2);
      if(id2<0) STinsert(pretab,label2,V++);
  }
  STfree(pretab); rewind(fin);
  G=GRAPHinit(V); V=0;

  while(fscanf(fin, "%s %d %s", label1, &wt,label2) == 3) {
    id1 = STsearch(G->tab, label1);
    if(id1<0){ id1=V++; STinsert(G->tab,label1,id1);}
    id2 = STsearch(G->tab, label2);
    if(id2<0){ id2=V++; STinsert(G->tab,label2,id2);}
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

static int appartenenza(int V[], int v, int val) {
    int i;

    for(i=0;i<v;i++) {
        if (V[i] == val)
            return 1;
    }
    return 0;
}
int* intersezione(Graph G,int V1[], int V2[], int v1, int v2, int *ni) {
    int i, k = 0;
    int *I=malloc(sizeof(int)*G->V);
    for(i=0;i<v1;i++) {
        if (!appartenenza(I, k, V1[i]) && appartenenza(V2, v2, V1[i]))
            I[k++] = V1[i];
    }
    for(i=0;i<v2;i++) {
        if (!appartenenza(I, k, V2[i]) && appartenenza(V1, v1, V2[i]))
            I[k++] = V2[i];
    }
    I=realloc(I, sizeof(int)*k);
    *ni=k;
    return I;
}
int** GRAPHsolLoad(Graph G,FILE *fs,int *ns){
    char label1[MAXC];
    int **M;
    M=malloc(sizeof(int*)*2);
    for(int i=0;i<2;i++){
        fscanf(fs,"%d",&ns[i]);
        ns[i]++;
        M[i]=malloc(sizeof(int)*ns[i]);
        for(int j=0;j<ns[i];j++){
            fscanf(fs,"%s",label1);
            M[i][j]=STsearch(G->tab,label1);
        }
    }
    return M;
}
void Gpathstoreintersection(Graph G,FILE *fout,int **M,int *I,int ni,int *nv){
    int s,k=0,c=0,j=1,f;
    fprintf(fout,"I vertici in comune sono:\n");
    for(int i=0;i<ni;i++) fprintf(fout,"%s\n",STsearchByIndex(G->tab,I[i]));
    for(int i=0;i<2;i++){
        if(I[0]==M[i][0] || I[ni-1]==M[i][nv[i]-1]){
            if(I[0]==M[i][0] && I[ni-1]==M[i][nv[i]-1]){
                s=ni-1; c=1;f=0;
            }else{s=ni;
            if(I[0]==M[i][0]) {c=1; f=1;}
            else{c=0;f=0;
            }}
        } else{ s=ni+1;c=0; f=1;}
        fprintf(fout,"Il cammino %d si decompone in %d sottocammini:\n",i,s);
        j=1;k=0;
        while ((j-1)!=s && c<ni){
            fprintf(fout,"sottocammino %d.%d: ",i+1,j);
                while (M[i][k]!=I[c]){
                    fprintf(fout,"%s, ",STsearchByIndex(G->tab,M[i][k]));
                    k++;
                }
                fprintf(fout,"%s, ",STsearchByIndex(G->tab,M[i][k]));
            c++; j++;
            fprintf(fout,"\n");
        }
        if(f){
            fprintf(fout,"sottocammino %d.%d: ",i+1,j);
            while (M[i][k-1]!=I[ni-1]){
                fprintf(fout,"%s, ",STsearchByIndex(G->tab,M[i][k]));
                k++;
            }
            fprintf(fout,"%s, ",STsearchByIndex(G->tab,M[i][k]));
        }
        fprintf(fout,"\n\n");
    }
}

static int checkriattraversamenti(Graph G,int *K,int k,int p){
    int c=0;
    for(int i=0;i<G->V;i++){
        if(p<=0) return 0;
        if(K[i]>1){ p-=(K[i]-1); c++; }
    }
    if(c>k) return 0;
    return 1;
}
static void vincoledR(Graph G,int s,int w,int d,int *sol,int *b_sol,int *val,int *b_val,int *K,int k,int p,int pos,int *n){
    if(w==d){
        if(*val>*b_val){
            *b_val=*val;
            *n=pos-1;//numero di vertici contenuti nella soluzione
            for(int i=0;i<(*n);i++)
                b_sol[i]=sol[i];
        }
        return;
    }
    for(int i=0;i<G->V;i++)
        if(G->madj[w][i]>0){//per tutti i vertici adiacenti al vertice corrente w
            K[i]++; //segno che è stato visitato
            if(checkriattraversamenti(G,K,k,p)){//faccio controllo pruning dei triattraversamenti dei vertici
                sol[pos]=i; (*val)+=G->madj[w][i];
                vincoledR(G,s,i,d,sol,b_sol,val,b_val,K,k,p,pos+1,n);
                sol[pos]=-1; (*val)-=G->madj[w][i];
            }
            K[i]--;
        }
}
void GRAPHpathvincoled(Graph G,FILE *fout,int k,int p,char* lab1,char *lab2){
    int s=STsearch(G->tab,lab1),d=STsearch(G->tab,lab2);
    int *K=calloc(G->V, sizeof(int)),*sol=malloc(sizeof(int)*(G->V+p)),*b_sol=malloc(sizeof(int)*(G->V+p));
    int ns,val=0,b_val=0;
    for(int i=0;i<G->V;i++) sol[i]=-1;

    K[s]++;//funge da vettore visited (la sorgente è gia visitata)
    sol[0]=s;
    vincoledR(G,s,s,d,sol,b_sol,&val,&b_val,K,k,p,1,&ns);
    if(ns>0){
        fprintf(fout,"Valore massimo : %d\n",b_val);
        for(int i=0;i<ns;i++)
            fprintf(fout,"%s ",STsearchByIndex(G->tab,b_sol[i]));
        fprintf(fout,"%s ",STsearchByIndex(G->tab,d));
    }
    free(K);free(sol);free(b_sol);
}
