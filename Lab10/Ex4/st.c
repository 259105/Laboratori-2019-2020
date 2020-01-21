//
// Created by s259105 on 08/01/2020.
//
#include "st.h"
#include <stdlib.h>

struct symbltab{
    Item *tab;
    int maxN;
    int size;
};

ST STinit(int v){
    ST st;
    st=malloc(sizeof(*st));
    if(st==NULL){
        fprintf(stderr,"Errore allocazione tabella.\n");
        exit(1);
    }
    st->tab=malloc(v* sizeof(Item));
    for(int i=0;i<v;i++)
        st->tab[i]=ITEMnew();
    st->maxN=v;
    st->size=0;
    return st;
}
void STfree(ST st){
    for(int i=0;i<st->maxN;i++)
        ITEMfree(st->tab[i]);
    free(st->tab);
    free(st);
}
int STcount(ST st){
    return st->size;
}
void STinsert(ST st,Item val){
    if(st->size==st->maxN) return;//la tabella è piena
    int i;
    for(i=st->size;i>0 && ITEMcompare(val,st->tab[i-1])<0;i--){
        st->tab[i]=st->tab[i-1];
    }
    st->tab[i]=val;
    st->size++;
    //if(STsearch(st,KEYget(val))==st->size) return; // se è gia dentro la tabella // ho gia controllato fuori
    //st->tab[st->size++]=val;
}
int STsearch(ST st,key val){
    int i;
    for(i=0;i<st->size && KEYcompare(KEYget(st->tab[i]),val)!=0;i++);
    return i;
}
key STsearchByIndex(ST st,int n){
    return KEYget(st->tab[n]);
}
/*void STsort(ST st,int n){
    int i,j,l=0,r=n-1;
    Item x;
    for(i=l+1;i<=r;i++){
        x=st->tab[i];
        j=i-1;
        while(j>=l && ITEMcompare(x,st->tab[j])<0){
            st->tab[j+1]=st->tab[j];
            j--;
        }
        st->tab[j+1]=x;
    }
}*/
/*void STdelete(ST st,key val){
    int i,j=0;
    i=STsearch(st,val); //cerco elemento da eliminare
    //traslo tutto di una casella
    for(j=i;j<st->size-1;j++)
        st->tab[j]=st->tab[j+1];
    st->size--;
}*/
