//
// Created by s259105 on 19/01/2020.
//
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "st.h"

typedef struct node *link;
struct node{
    int v,wt;
    link next;
};
struct _graph{
    int v,e;
    link *ladj;
    st tab;
    link z;
};

static link NEWnode(int v,int wt,link next){
    link t=malloc(sizeof(*t));
    t->v=v;
    t->wt=wt;
    t->next=next;
    return t;
}
graph GRAPHinit(int n){
    graph t;
    t=malloc(sizeof(*t));
    t->ladj=malloc(n*sizeof(link));
    t->z=NEWnode(0,0,NULL);
    for(int i=0;i<n;i++)
        t->ladj[i]=t->z;
    t->tab=STinit(n);
    t->v=n;
    t->e=0;
    return t;
}

static void LISTfree(link h,link z){
    if(h==z) return;
    LISTfree(h->next,z);
    free(h);
}
void GRAPHfree(graph G){
    STfree(G->tab);
    for(int i=0;i<G->v;i++)
        LISTfree(G->ladj[i],G->z);
    free(G->z);
    free(G->ladj);
    free(G);
}

edge EDGEcreate(int v,int w,int wt){
    edge e;
    e.v=v; e.w=w; e.wt=wt;
    return e;
}
static void insertE(graph G,edge e){
    int v=e.v,w=e.w,wt=e.wt;
    G->ladj[v]=NEWnode(w,wt,G->ladj[v]);//inserimento in testa;
    G->e++;
}
void EDGEprint(graph G,edge e){
    printf("(%s, %s) : %d \n",STsearchByIndex(G->tab,e.v),STsearchByIndex(G->tab,e.w),e.wt);
}

graph GRAPHload(FILE *fp){
    graph G;
    int v,wt;
    int id,id1;
    char label[MAXCHAR],label1[MAXCHAR];
    fscanf(fp,"%d",&v);
    G=GRAPHinit(v);
    for(int i=0;i<v;i++){
        fscanf(fp,"%s",label);
        STinsert(G->tab,label);
    }
    while(fscanf(fp,"%s %s %d",label,label1,&wt)==3){
        id=STsearch(G->tab,label);
        id1=STsearch(G->tab,label1);
        if(id1>=0 && id>=0)
            insertE(G,EDGEcreate(id,id1,wt));
    }
    return G;
}

static int dfsR(graph G,edge e,int *time,int *pre,int *post,int *st,int count){
    link t;
    int w=e.w;

    /*if(e.v!=e.w)
        printf("(%s, %s):T\n",STsearchByIndex(G->tab,e.v),STsearchByIndex(G->tab,e.w));
    */
    st[e.w]=e.v;//dico che v è il padre del nodo puntato da v(w)
    pre[w]=(*time)++;

    for(t=G->ladj[w];t!=G->z;t=t->next){

        if(t->wt==0){//se il peso è ==0 considero l'arco inesistente
            t=t->next;//salto e vado al successivo
            if(t==G->z)//se quello successivo è z
                break; //termino l'iterazione
        }

        if(pre[t->v]==-1)//controllo che non sia stato ancora scoperto
            count=dfsR(G,EDGEcreate(w,t->v,t->wt),time,pre,post,st,count); //ricorro
        else{ //se è gia stato scoperto allora è B o F o C;
            if(post[t->v]==-1){//arco tipo B
                //printf("(%s, %s):B\n",STsearchByIndex(G->tab,t->v),STsearchByIndex(G->tab,w));
                count++;
            }
            /*else
                if(pre[t->v]>pre[w])//arco tipo F
                    printf("(%s, %s):F\n",STsearchByIndex(G->tab,t->v),STsearchByIndex(G->tab,w));
                else
                    printf("(%s, %s):C\n",STsearchByIndex(G->tab,t->v),STsearchByIndex(G->tab,w));
        */}
    }

    post[w]=(*time)++;
    return count;
}
int GRAPHdfs(graph G,int id){
    int v,time=0,*pre,*post,*st; //pre:=inizio elaborazione; post:=fine elaborazione
    int count=0;  //conta gli archi back
    pre=malloc(G->v* sizeof(int));
    post=malloc(G->v* sizeof(int));
    st=malloc(G->v* sizeof(int));
    for(v=0;v<G->v;v++){
        pre[v]=-1; post[v]=-1; st[v]=-1;
    }
    count=dfsR(G,EDGEcreate(id,id,0),&time,pre,post,st,count);//primo albero
    for(v=0;v<G->v;v++)
        if(pre[v]==-1)
            count=dfsR(G,EDGEcreate(v,v,0),&time,pre,post,st,count);
    free(pre);
    free(post);
    free(st);
    return count;
}

static void LISTprint(int v,link h,link z,st tab){
    if(h==z) return;
    printf("(%s, %s) == (%d, %d) -> %d \n",STsearchByIndex(tab,v),STsearchByIndex(tab,h->v),v,h->v,h->wt);
    LISTprint(v,h->next,z,tab);
}
void GRAPHprintLadj(graph G){
    for(int i=0;i<G->v;i++)
        LISTprint(i,G->ladj[i],G->z,G->tab);
}

void GRAPHedgesR(int v,link h,edge *e,int *j,link z){
    if(h==z) return;
    GRAPHedgesR(v,h->next,e,j,z);
    e[(*j)++]=EDGEcreate(v,h->v,h->wt);
}
edge* GRAPHedges(graph G,edge *e){
    int j=0,i;
    e=malloc(G->e*sizeof(edge));
    for(i=0;i<G->v;i++){
        GRAPHedgesR(i,G->ladj[i],e,&j,G->z);
    }
    return e;
}

static int checkDAG(graph G,edge *e,int c){
    //imposto momentaneamente gli archi trovati nel grafo con peso = 0
    //gli archi a peso ==0 li considero inesistenti
    //allora desso controllo se il grafo ottenuto è DAG7
    link t;
    int result=0;//non è un DAG
    for(int i=0;i<c;i++){
        for(t=G->ladj[e[i].v];t->v!=e[i].w;t=t->next);
        // non faccio controllo di fine lista perche sono sicuro che l'arco è presente
        t->wt=0;
    }
    if(!GRAPHdfs(G,0)) result=1;
    //reimposto tutto come era prima
    for(int i=0;i<c;i++){
        for(t=G->ladj[e[i].v];t->v!=e[i].w;t=t->next);
        t->wt=e[i].wt;
    }
    return result;
}
static edge* UPDATEmax(edge *sol,int card){
    edge *e;
    e=malloc(card*sizeof(*e));
    for(int i=0;i<card;i++){
        e[i]=EDGEcreate(sol[i].v,sol[i].w,sol[i].wt);
    }
    return e;
}
static void printEDGES(graph G,edge *sol,int card){
    for(int i=0;i<card;i++)
        EDGEprint(G,EDGEcreate(sol[i].v,sol[i].w,sol[i].wt));
}
static edge* Pwrst_CmbSmpl(graph G,edge *val,int k,edge *sol,edge *b_sol,int *max,int j,int pos,int start){
    int i,sum=0;
    if(pos==j){
        if(checkDAG(G,sol,j)){
            for(i=0;i<j;i++){// controllo se è un insieme di peso massimo
                sum+=sol[i].wt;
            }
            if(sum>*max){ // aggiorno il massimo se la nuova soluzione è maggiore
                *max=sum;
                b_sol=UPDATEmax(sol,j);
            }

            printEDGES(G,sol,j); //stampo l'insieme delle soluzioni
            printf("\n");
        }
        return b_sol;
    }
    for(i=start;i<k;i++){
        sol[pos]=val[i];
        b_sol=Pwrst_CmbSmpl(G,val,k,sol,b_sol,max,j,pos+1,i+1);
    }
    return b_sol;
}
edge* Pwrst_CmbSmpl_W(graph G,edge* b_sol,int *card){
    int k,max=0;
    edge *e_t=NULL;
    edge *sol=malloc(G->e* sizeof(edge));

    e_t=GRAPHedges(G,e_t);//Creo vettore di archi
    for (k=1;k<G->e;k++){//indica la cardinalità
        b_sol=Pwrst_CmbSmpl(G,e_t,G->e,sol,b_sol,&max,k,0,0);
        if(b_sol!=NULL) break;//termino il ciclo se ho trovato un DAG
    }
    free(e_t);
    free(sol);
    *card=k;
    return b_sol;
}

void GraphToDAG(graph G,edge* e,int card){
    //simile al checkDAG
    int i;
    link t,p=NULL;

    for(i=0;i<card;i++)//stampo insieme di archi con peso massimo
        EDGEprint(G,e[i]);
    //rimuovo dal grafo gli archi selezionati
    for(i=0;i<card;i++){
            for(p=NULL,t=G->ladj[e[i].v]; t->v!=e[i].w;p=t,t=t->next);
            if(p==NULL) // se è il primo elemento in lista
                G->ladj[e[i].v]=G->ladj[e[i].v]->next;
            else{ //by-pas
                p->next=t->next;
            }
            free(t);
    }
    G->e--;
}

static void TSdfsR(graph G,int v,int *ts,int *pre,int *time){
    link t;
    pre[v]=0;
    for(t=G->ladj[v];t!=G->z;t=t->next)
        if(pre[t->v]==-1)
            TSdfsR(G,t->v,ts,pre,time);
    ts[(*time)++]=v;
}
static int* DAGrts(graph G){
    int v,time=0,*pre,*ts;
    pre=malloc(G->v*sizeof(int));
    ts=malloc(G->v*sizeof(int));
    for(v=0;v<G->v;v++){ pre[v]=-1; ts[v]=-1;}
    for(v=0;v<G->v;v++)
        if(pre[v]==-1) TSdfsR(G,v,ts,pre,&time);
    free(pre);
    return ts;
}
static int* DAGsearchSources(graph G){
    //funzione che mi trova le sorgenti
    int *S,i;
    link t;
    S=malloc(G->v* sizeof(int));
    for(i=0;i<G->v;i++)
        S[i]=1; //inizializzo tutto a 1,cioè dico che sono tutte sorgenti;
    for(i=0;i<G->v;i++)
        for(t=G->ladj[i];t!=G->z;t=t->next)
            S[t->v]=0; //significa che non è una sorgente, perche è puntata;
    return S; // 1:= è una sorgente 0:= non è una sorgente
}
static void DAGmaxdFromS(graph G,int s,int *top){
    // s indica la sorgente da cui iniziare la ricerca
    link t;
    int *d;
    int *ts;
    int u,k;
    ts=calloc(G->v, sizeof(int));
    d=calloc(G->v, sizeof(int));//inizializzo a 0;

    //ricerco sorgente nell'ordinamento topologico inverso
    for(k=0;top[k]!=s;k++);
    //parto dalla sorgente nell'ordinamento topologico
    //poiche è un ord top inverso, lo scorro al contrario
    for(int i=k;i>=0;i--){//per tutti i vertici
        u=top[i];//percorro ts al contrario per avere un ordinemnto topologico normale
        for(t=G->ladj[u];t!=G->z;t=t->next){//per tutti gli archi del vertice
            if( (d[u]!=0 && i!=k) || (d[u]==0 && i==k) )
                //se la distanza massima di quel vertice è zero vuol dire che il 2 non è collegato con lui da un cammino
                //percio non lo tengo in considerazione
                if(d[t->v]<d[u]+t->wt){ // se e vera questa condizione allora aggiorno
                    d[t->v]=d[u]+t->wt;
                    ts[t->v]=u;
                }
        }
    }
    for(int i=k-1;i>=0;i--)
        if(d[top[i]]!=0)
            EDGEprint(G,EDGEcreate(s,top[i],d[top[i]]));
    free(ts);
    free(d);
}
void DAGmaxD(graph G){
    int *topologico=DAGrts(G); //ordinamento topologico inverso;;
    int *S=DAGsearchSources(G);//cerco le sorgenti del DAG;
    for(int i=0;i<G->v;i++)
        if(S[i]==1) {
            printf("Stampo distanza massima da sorgente %s:\n",STsearchByIndex(G->tab,i));
            DAGmaxdFromS(G, i, topologico);
        }
    free(topologico);
    free(S);
}
