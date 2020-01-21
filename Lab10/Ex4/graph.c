//
// Created by s259105 on 08/01/2020.
//
#include "graph.h"
#include <stdlib.h>
typedef struct node *link;
struct node{
    int v,wt;
    link next;
};
struct graph{
    int v;
    int e;
    int **madj;
    link *ladj;
    ST tab;
    link z;
};

static link NEW(int v,int wt,link next){
    link x;
    x=malloc(sizeof(*x));
    x->v=v;
    x->wt=wt;
    x->next=next;
    return x;
}
static Edge EDGEcreate(int v,int w,int wt){
    Edge e;
    e.v=v; e.w=w; e.wt=wt;
    return e;
}
static int **matrixinit(int r,int c,int val){
    int j,i;
    int **m=NULL;
    m=malloc(r*sizeof(int*));
    for(i=0;i<r;i++)
        m[i]=malloc(c*sizeof(int));
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            m[i][j]=val;
    return m;
}
static void freematrix(int **m,int r){
    for(int i=0;i<r;i++)
        free(m[i]);
    free(m);
}
/*static void printmatrix(int **m,int r,FILE *fp){
    for(int i=0;i<r;i++){
        for(int j=0;j<r;j++)
            fprintf(fp,"%3d ",m[i][j]);
        fprintf(fp,"\n");
    }
}*/
static void insertE(Graph G,Edge e){
    int v=e.v,w=e.w,wt=e.wt;
    if(G->madj[v][w]==0)//se è vuoto aggiungo l'arco
        G->e++;
    G->madj[v][w]=wt;
    G->madj[w][v]=wt;
}
/*static int** reallocmatrix(int **m,int v){
    int i;
    for(i=0;i<v;i++)
        m[i]=realloc(m[i],v);
    m=realloc(m,v);
    return m;
}*/
static void printEInst(Graph G,int v,FILE *fp){
    int i;
    for(i=0;i<G->v;i++){
        if(G->madj[v][i]!=0)
            fprintf(fp,"%s ",STsearchByIndex(G->tab,i));
    }
}
static void printST(Graph G,FILE *fp){
    for(int i=0;i<G->v;i++){
        fprintf(fp,"%d: %s\n",i,STsearchByIndex(G->tab,i));
        fprintf(fp,"\t");
        printEInst(G,i,fp);
        fprintf(fp,"\n");
    }
}

Graph GRAPHinit(int v){
    Graph G;
    G=malloc(sizeof(*G));
    G->v=v;
    G->e=0;
    G->z=NEW(-1,-1,NULL);
    G->tab=STinit(v);
    G->madj=matrixinit(v,v,0);
    G->ladj=malloc(G->v* sizeof(link));
    for(v=0;v<G->v;v++)
        G->ladj[v]=G->z;
    return G;
}
void GRAPHfree(Graph G){
    link t,next;
    freematrix(G->madj,G->v);
    for(int i=0;i<G->v;i++){
        for(t=G->ladj[i];t!=G->z;t=next){
            next=t->next;
            free(t);
        }
    }
    STfree(G->tab);
    free(G->ladj);
    free(G->z);
    free(G);
}
Graph GRAPHload(FILE *fin,int v){
    Graph G;
    Item t1,t2;
    int wt,id1,id2;
    char id_e1[30],id_r1[30],id_e2[30],id_r2[30];
    G=GRAPHinit(v);
    while(fscanf(fin,"%s %s %s %s %d",id_e1,id_r1,id_e2,id_r2,&wt)==5){//in questo while acquisisco i vertici li salvo
                                                                        //in ordine crescente
        t1=ITEMload(id_e1,id_r1);
        t2=ITEMload(id_e2,id_r2);
        if((id1=STsearch(G->tab,id_e1))==STcount(G->tab))//se l'elemento non è ancora stato aggiunto
            STinsert(G->tab,t1);
        if((id2=STsearch(G->tab,id_e2))==STcount(G->tab))//se l'elemento non è ancora stato aggiunto
            STinsert(G->tab,t2);
    }
    G->v=STcount(G->tab);
    rewind(fin);
    while(fscanf(fin,"%s %s %s %s %d",id_e1,id_r1,id_e2,id_r2,&wt)==5){ //in questo while metto i vertici ordinati
                                                                        // nella matrice delle adiacenze
        id1=STsearch(G->tab,id_e1);
        id2=STsearch(G->tab,id_e2);
        GRAPHinsertE(G,id1,id2,wt);
    }
    GRAPHstore(G,stdout);
    return G;
}
void GRAPHinsertE(Graph G,int id1,int id2,int wt){
    insertE(G,EDGEcreate(id1,id2,wt));
}

void GRAPHstore(Graph G,FILE *fp){
    //printmatrix(G->madj,G->v,fp);
    printST(G,fp);
}
void GRAPHladj(Graph G){
    int i,j;
    if(G->ladj[0]!=G->z){
        printf("Lista delle adiacenze gia' creata.\n");
        return;
    }
    for(i=0;i<G->v;i++)
        for(j=0;j<G->v;j++){
            if(G->madj[i][j]!=0){
                G->ladj[i]=NEW(j,G->madj[i][j],G->ladj[i]);
            }
        }
    printf("Lista delle adiacenze creata.\n");
}
int GRAPHverifiaLadj(Graph G){
    return (G->ladj[0]!=G->z);
}
int GRAPHadiacentiMadj(Graph G){
    char id1[30],id2[30],id3[30];
    int v1,v2,v3;
    fprintf(stdout,"Inserisci vertici da controllare: <nome1> <nome2> <nome3>\n");
    fscanf(stdin,"%s %s %s",id1,id2,id3);
    v1=STsearch(G->tab,id1);
    v2=STsearch(G->tab,id2);
    v3=STsearch(G->tab,id3);
    if(G->madj[v1][v2]!=0 && G->madj[v2][v3]!=0 && G->madj[v3][v1]!=0)
        return 1;
    return 0;
}
static int adiacentilistaR(link x,int v){
    if(x==NULL) return 0;
    if(x->v==v) return 1;
    return adiacentilistaR(x->next,v);
}
int GRAPHadiacentiLadj(Graph G){
    char id1[30],id2[30],id3[30];
    int v1,v2,v3;
    fprintf(stdout,"Inserisci vertici da controllare: <nome1> <nome2> <nome3>\n");
    fscanf(stdin,"%s %s %s",id1,id2,id3);
    v1=STsearch(G->tab,id1);
    v2=STsearch(G->tab,id2);
    v3=STsearch(G->tab,id3);
    if(adiacentilistaR(G->ladj[v1],v2) && adiacentilistaR(G->ladj[v2],v3) && adiacentilistaR(G->ladj[v3],v1))
        return 1;
    return 0;
}
/*Graph GRAPHsortST(Graph G){
    ST newst;
    newst=STinit(STcount(G->tab));

    STsort(newst,STcount(G->tab));
    return G;
}*/
/*Graph GRAPHfix(Graph G){
    G->v=STcount(G->tab);
    G->madj=reallocmatrix(G->madj,G->v);
    //G->ladj=realloc(G->ladj,G->v);
    return G;
}*/
