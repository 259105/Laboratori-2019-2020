//
// Created by s259105 on 19/01/2020.
//
#include <stdlib.h>
#include <string.h>
#include "quotazioni.h"
#include "titolo.h"

struct _titolo{
    char cod[maxchar+1];
    quotazioni q;
};

titolo TITOLOinit(char *cod){
    titolo t=malloc(sizeof *t);
    strcpy(t->cod,cod);
    t->q=QUOTAZIONIinit();
    return t;
}
void TITOLOfree(titolo t){
    if (t==NULL) return;
    QUOTAZIONIfree(t->q);
    free(t);
}
void TITOLOinsert(titolo t,quotazione q){
    QUOTAZIONIinsert(t->q,q);
}
quotazioni QbyT(titolo t){
    return t->q;
}
char* CodbyT(titolo t){
    return t->cod;
}
