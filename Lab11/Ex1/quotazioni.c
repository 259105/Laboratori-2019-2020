//
// Created by s259105 on 19/01/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "quotazioni.h"
#include "data.h"

typedef struct node *link;
struct node{
    quotazione Q;
    int size;
    link l,r;
};
struct _quotazioni{
    link root;
    link z;
    int n;
};

float QUOTAZIONE(quotazione q){
    return (float)q.valtot/(float)q.n;
}
quotazione quotazioneSetNULL(){
    quotazione q;
    q.valtot=0;
    q.n=0;
    q.d=dataSetNULL();
    return q;
}

static link NEWnode(quotazione val,link l,link r,int n){
    link t;
    t=malloc(sizeof(*t));
    t->size=n;
    t->l=l;
    t->r=r;
    t->Q=val;
    return t;
}

quotazioni QUOTAZIONIinit(){
    quotazioni t;
    t=malloc(sizeof(*t));
    t->n=0;
    t->root=(t->z=NEWnode(quotazioneSetNULL(),NULL,NULL,0));
    return t;
}
quotazione QUOTAZIONEinit(int val,int n,data d){
    quotazione q;
    q.valtot=val*n;
    q.n=n;
    q.d=d;
    return q;
}

static void treefree(link h,link z){
    if(h==z) return;
    treefree(h->l,z);
    treefree(h->r,z);
    free(h);
}
void QUOTAZIONIfree(quotazioni q){
    if (q==NULL)
        return;
    treefree(q->root,q->z);
    free(q->z);
    free(q);
}

static quotazione QUOTAZIONEincrease(quotazione q,quotazione t){
    q.valtot+=t.valtot; // t è la quotazione temporanea la uso per l'inserimento
    q.n+=t.n;
    q.d=t.d;
    return q;
}
static link insertR(link h,quotazione q,link z,int f){
    // f==1 => ho aggiunto un nodo;
    // f==0 => ho aggiornato un nodo;
    if (h==z) return NEWnode(q,z,z,1);
    if(DATAcmp(q.d,h->Q.d)==0){
        h->Q=QUOTAZIONEincrease(h->Q,q);
        f=0;
        return h;
    }
    if(DATAcmp(q.d,h->Q.d)<0)
        h->l=insertR(h->l,q,z,f);
    else
        h->r=insertR(h->r,q,z,f);
    if(f==1)
        h->size++;
    return h;
}
void QUOTAZIONIinsert(quotazioni Q,quotazione q){
    Q->root=insertR(Q->root,q,Q->z,1);
}

static quotazione search(link h,data d,link z){
    quotazione trovato=quotazioneSetNULL();
    if(h==z)
        return trovato;
    if(DATAcmp(d,h->Q.d)==0)
        return h->Q;
    if(DATAcmp(d,h->Q.d)<0)
        return search(h->l,d,z);
    return search(h->r,d,z);
    }
quotazione QUOTAZIONIsearch(quotazioni Q,data d){
    return search(Q->root,d,Q->z);
}
static data QUOTAZIONImaxdata(link node,link z){
    if(node==z) return dataSetNULL();
    if(node->r==z) return node->Q.d;
    return QUOTAZIONImaxdata(node->r,z);
}
data QUOTAZIONImaxdataW(quotazioni Q){
    return QUOTAZIONImaxdata(Q->root,Q->z);
}
static void visitinORDER(link node,data d1,data d2,float *max,float *min,link z){
    float t;
    if(node==z) return;
    if(DATAcmp(d1,node->Q.d)<=0)
        visitinORDER(node->l,d1,d2,max,min,z);
    if(DATAcmp(d1,node->Q.d)<=0 && DATAcmp(node->Q.d,d2)<=0){//in teoria questo if non serve, ma lo metto per sicurezza
        if((t=QUOTAZIONE(node->Q))>*max) *max=t;
        if(t<*min || *min==-1) *min=t;
    }
    if(DATAcmp(node->Q.d,d2)<=0)
        visitinORDER(node->r,d1,d2,max,min,z);
}
void QUOTAZIONIsearchIntervalPrintMaxMin(quotazioni Q,data d1,data d2,FILE *fp){
    float max=0,min=-1;
    visitinORDER(Q->root,d1,d2,&max,&min,Q->z);
    if(min==-1){
        fprintf(stderr,"Errore intervallo inserito non trovato.\n");
        return;
    }
    fprintf(fp,"Quotazione MAX: %.4f e MIN: %.4f\n\n",max,min);
}

void QUOTAZIONEprint(FILE *fp,quotazione q){
    fprintf(fp,"%.4f %d/%d/%d %.2d:%.2d\n",QUOTAZIONE(q),q.d.giorno,q.d.mese,q.d.anno,q.d.ore,q.d.minuti);
}
/*static void tree_print(link h, link z, FILE *fp) {
    if (h==z) return;
    tree_print(h->l, z, fp);
    QUOTAZIONEprint(fp, h->Q);
    tree_print(h->r, z, fp);
}
void QUOTAZIONIprint(quotazioni bst, FILE *fp) {
    tree_print(bst->root, bst->z, fp);
}*/
//funzioni di bilanciamento
static link rotR(link h){
    link x=h->l;
    h->l=x->r;
    x->r=h;
    x->size=h->size;
    h->size=1;
    h->size+=(h->l)?h->l->size:0;
    h->size+=(h->r)?h->r->size:0;
    return x;
}
static link rotL(link h){
    link x=h->r;
    h->r=x->l;
    x->l=h;
    x->size=h->size;
    h->size=1;
    h->size+=(h->l)?h->l->size:0;
    h->size+=(h->r)?h->r->size:0;
    return x;
}
static link partR(link h,int r,link z){
    if(h==z) return h;
    int t=h->l->size;
    if(t>r){
        h->l=partR(h->l,r,z);
        h=rotR(h);
    }
    if(t<r){
        h->r=partR(h->r,r-t-1,z);
        h=rotL(h);
    }
    return h;
}
static link balanceR(link h,link z) {
    int r;
    if(h==z) return z;
    r=(h->size+1)/2-1; //cerco la metà
    h=partR(h,r,z);
    h->l=balanceR(h->l,z);
    h->r=balanceR(h->r,z);
    return h;
}
static void BSTbalance(quotazioni bst){
    bst->root=balanceR(bst->root,bst->z);
}
//cammini minimi e massimi albero
static int camminomin(link h,link z,int min){
    if(h==z) return 0;
    if(h->l->size<h->r->size) min=camminomin(h->l,z,min);
    else min=camminomin(h->r,z,min);
    return min+1;
}
static int camminomax(link h,link z,int max){
    if(h==z) return 0;
    if(h->l->size>h->r->size) max=camminomax(h->l,z,max);
    else max=camminomax(h->r,z,max);
    return max+1;
}
int BilanciamentoSoglia(quotazioni bst,int soglia){
    if((camminomax(bst->root,bst->z,0)-camminomin(bst->root,bst->z,0))>soglia){
        BSTbalance(bst);
        return 1; //bilanciamnto avvenuto
    }
    return 0; // bilanciamento non eseguito
}
