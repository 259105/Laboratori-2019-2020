//
// Created by s259105 on 08/01/2020.
//
#include "item.h"
#include "mylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct item{
    char id_e[30];
    char id_r[30];
};

key KEYget(Item val){
    return val->id_e;
}
int KEYcompare(key k1,key k2){
    return confronta_stringhe(k1,k2);
}

Item ITEMnew(void){
    Item val;
    val=(Item)malloc(sizeof(struct item));
    if(val==NULL){
        fprintf(stderr,"Errore allocazione item.\n");
        exit(1);
    }
    val->id_e[0]='\0';
    val->id_r[0]='\0';
    return val;
}
void ITEMfree(Item val){
    free(val);
}
Item ITEMload(char *id_e,char *id_r){
    Item val;
    val=ITEMnew();
    strcpy(val->id_e,id_e);
    strcpy(val->id_r,id_r);
    return val;
}
Item ITEMsetvoid(Item val){
    val->id_e[0]='\0';
    val->id_r[0]='\0';
    return val;
}
void ITEMshow(Item val){
    printf("%s %s",val->id_e,val->id_r);
}
int ITEMcompare(Item val1,Item val2){
    return KEYcompare(KEYget(val1),KEYget(val2));
}
