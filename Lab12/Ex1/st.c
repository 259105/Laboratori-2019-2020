//
// Created by s259105 on 19/01/2020.
//

#include "st.h"
#include <stdlib.h>
#include <string.h>
struct _st{
    char **id;
    int max;
    int n;
};

st STinit(int n){
    st t=malloc(sizeof(*t));
    t->id=(char**)malloc(n*sizeof(char*));
    t->max=n;
    t->n=0;
    return t;
}
void STfree(st t){
    for(int i=0;i<t->max;i++)
        free(t->id[i]);
    free(t->id);
    free(t);
}

void STinsert(st t,char *s){
    //faccio un inserimento in coda;
    //non faccio il controllo del max perche sappiamo gia il numero di vertici;
    t->id[t->n++]=strdup(s);
}

int STsearch(st t,char *s){
    for(int i=0;i<t->n;i++)
        if(strcmp(s,t->id[i])==0)
            return i; //restituisco indice
    return -1;//non è stato trovato niente
}
char* STsearchByIndex(st t,int i){
    return t->id[i];
}
